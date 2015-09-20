#include "hext/StringPipe.h"


namespace hext {


StringPipe::StringPipe()
: next_(nullptr)
{
}

StringPipe::StringPipe(const StringPipe& other)
: next_(other.next_ ? other.next_->clone() : nullptr)
{
}

StringPipe& StringPipe::operator=(const StringPipe& other)
{
  if( this != &other )
  {
    // delete current chain
    this->next_ = nullptr;

    // recursively clone the pipe chain (Cloneable::clone() will call the copy
    // ctor for other.next_).
    if( other.next_ )
      this->next_ = std::move(other.next_->clone());
  }

  return *this;
}

std::string StringPipe::pipe(std::string str) const
{
  str = this->transform(std::move(str));

  if( this->next_ )
    str = this->next_->pipe(std::move(str));

  return str;
}

void StringPipe::append(std::unique_ptr<StringPipe> p)
{
  if( this->next_ )
    // recursively move p to the end of the chain
    this->next_->append(std::move(p));
  else
    this->next_.swap(p);
}


} // namespace hext

