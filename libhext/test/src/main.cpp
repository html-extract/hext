#include "gtest/gtest.h"

#include "string-util/main.h"
#include "builtins/main.h"
#include "node-util/main.h"
#include "parser/main.h"
#include "pattern/attribute-capture.h"
#include "pattern/attribute-match.h"
#include "pattern/builtin-capture.h"
#include "pattern/builtin-match.h"
#include "pattern/childcount-match.h"
#include "pattern/literal-test.h"
#include "pattern/nthchild-match.h"
#include "pattern/regex-test.h"
#include "pattern/value-test.h"


int main(int argc, char ** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

