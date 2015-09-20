#include "hext/FunctionCapture.h"

#include <cassert>
#include <utility>


namespace hext {


FunctionCapture::FunctionCapture(CaptureFunction             func,
                                 std::string                 result_name,
                                 std::unique_ptr<StringPipe> pipe)
: func_(std::move(func))
, name_(std::move(result_name))
, pipe_(std::move(pipe))
{
}

FunctionCapture::FunctionCapture(const FunctionCapture& other)
: func_(other.func_)
, name_(other.name_)
, pipe_(other.pipe_ ? other.pipe_->clone() : nullptr)
{
}

FunctionCapture& FunctionCapture::operator=(const FunctionCapture& other)
{
  if( this != &other )
  {
    this->func_ = other.func_;
    this->name_ = other.name_;
    this->pipe_.reset(other.pipe_->clone());
  }

  return *this;
}

boost::optional<ResultPair> FunctionCapture::capture(
    const GumboNode * node) const
{
  assert(this->func_);
  if( !this->func_ )
    return {};

  auto str = this->func_(node);

  if( this->pipe_ )
    return ResultPair(
        this->name_,
        this->pipe_->pipe(std::move(str))
    );

  return ResultPair(this->name_, str);
}


} // namespace hext

