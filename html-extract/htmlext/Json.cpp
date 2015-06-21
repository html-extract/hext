#include "htmlext/Json.h"


namespace htmlext {


void PrintJson(const hext::ResultTree * rt, std::ostream& out)
{
  assert(rt);
  if( !rt )
    return;

  rapidjson::Document doc;
  doc.SetArray();
  auto& alloc = doc.GetAllocator();

  for(const auto& group : rt->children())
  {
    rapidjson::Value obj(rapidjson::kObjectType);
    AppendValuesJson(group.get(), obj, alloc);
    doc.PushBack(obj, alloc);
  }

  rapidjson::StringBuffer buffer;
  rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
  doc.Accept(writer);
  out << buffer.GetString() << "\n";
}

void AppendValuesJson(
  const hext::ResultTree * rt,
  rapidjson::Value& obj,
  rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>& alloc
)
{
  assert(rt);
  assert(obj.IsObject());
  if( !rt || !obj.IsObject() )
    return;

  for(const auto& p : rt->values())
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

  for(const auto& child : rt->children())
  {
    AppendValuesJson(child.get(), obj, alloc);
  }
}


} // namespace htmlext

