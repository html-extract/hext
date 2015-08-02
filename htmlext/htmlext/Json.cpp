#include "htmlext/Json.h"


namespace htmlext {


void PrintJson(const hext::Result result, JsonOption opt, std::ostream& out)
{
  rapidjson::Document doc;
  doc.SetArray();
  auto& alloc = doc.GetAllocator();

  for(const auto& group : result)
  {
    rapidjson::Value obj(rapidjson::kObjectType);

    for(const auto& p : group)
    {
      rapidjson::Value name(p.first.c_str(), alloc);
      rapidjson::Value value(p.second.c_str(), alloc);
      // If the key is already taken, transform the value into an array
      if( obj.HasMember(name) )
      {
        if( obj[name].IsArray() )
        {
          obj[name].PushBack(value, alloc);
        }
        else
        {
          rapidjson::Value array(rapidjson::kArrayType);
          array.PushBack(obj[name], alloc);
          array.PushBack(value, alloc);
          obj[name] = array;
        }
      }
      else
      {
        obj.AddMember(name, value, alloc);
      }
    }

    doc.PushBack(obj, alloc);
  }

  if( ( opt & JsonOption::ArrayEnvelope ) == JsonOption::ArrayEnvelope )
  {
    if( !doc.Empty() )
    {
      PrintJsonValue(doc, opt, out);
      out << "\n";
    }
  }
  else
  {
    // Print each child object on a seperate line
    rapidjson::Value::ConstValueIterator it = doc.Begin();
    for(; it != doc.End(); ++it)
    {
      assert(it->IsObject());
      PrintJsonValue(*it, opt, out);
      out << "\n";
    }
  }
}


void PrintJsonValue(const rapidjson::Value& value,
                    JsonOption              opt,
                    std::ostream&           out)
{
  rapidjson::StringBuffer buffer;
  if( (opt & JsonOption::PrettyPrint) == JsonOption::PrettyPrint )
  {
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    value.Accept(writer);
  }
  else
  {
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    value.Accept(writer);
  }

  out << buffer.GetString();
}


} // namespace htmlext

