#include "hext/token.h"


namespace hext {


std::string token::to_string() const
{
  if( this->begin && this->end && 
      this->begin != this->end )
    return std::string(this->begin, this->end);
  else
    return std::string("");
}


}

