#include "htmlext/json.h"


namespace htmlext {


void PrintJson(
  const std::multimap<std::string, std::string>& values,
  std::ostream& out
)
{
  rapidjson::Document json;
  json.SetObject();
  rapidjson::Document::AllocatorType& allocator = json.GetAllocator();
  for(const auto& p : values)
  {
    rapidjson::Value name(p.first.c_str(), allocator);
    rapidjson::Value value(p.second.c_str(), allocator);
    // If the key is already taken, transform the value into an array
    if( json.HasMember(name) )
    {
      if( json[name].IsArray() )
      {
        json[name].PushBack(value, allocator);
      }
      else
      {
        rapidjson::Value array(rapidjson::kArrayType);
        array.PushBack(json[name], allocator);
        array.PushBack(value, allocator);
        json[name] = array;
      }
    }
    else
    {
      json.AddMember(name, value, allocator);
    }
  }

  rapidjson::StringBuffer buffer;
  rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
  json.Accept(writer);
  out << buffer.GetString() << "\n";
}


} // namespace htmlext

