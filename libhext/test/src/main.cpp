#include "gtest/gtest.h"

#include "builtins/main.h"
#include "hext/main.h"
#include "node-util/main.h"
#include "option/main.h"
#include "parser/main.h"
#include "pattern/attribute-capture.h"
#include "pattern/attribute-match.h"
#include "pattern/beginswith-test.h"
#include "pattern/builtin-capture.h"
#include "pattern/builtin-match.h"
#include "pattern/childcount-match.h"
#include "pattern/contains-test.h"
#include "pattern/containsword-test.h"
#include "pattern/endswith-test.h"
#include "pattern/isnotliteral-test.h"
#include "pattern/isnotregex-test.h"
#include "pattern/literal-test.h"
#include "pattern/nthchild-match.h"
#include "pattern/regex-test.h"
#include "pattern/value-test.h"
#include "string-util/main.h"
#include "version/main.h"


int main(int argc, char ** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

