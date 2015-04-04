%include "exception.i"

%exception {
  try
  {
    $action
  }
  catch(const ParseError& e)
  {
    SWIG_exception(SWIG_ValueError, e.what());
  }
}

