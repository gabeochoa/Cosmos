#include "../src/parser.hpp"

#include "gtest/gtest.h"
#include <string>
#include <sstream>

class FooTest : public ::testing::Test {
 protected:
  // You can remove any or all of the following functions if its body
  // is empty.

  FooTest() {
    // You can do set-up work for each test here.
  }

  virtual ~FooTest() {
    // You can do clean-up work that doesn't throw exceptions here.
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  virtual void SetUp() {
    // Code here will be called immediately after the constructor (right
    // before each test).
  }

  virtual void TearDown() {
    // Code here will be called immediately after each test (right
    // before the destructor).
  }

  // Objects declared here can be used by all tests in the test case for Foo.
};



TEST(FooTest, MethodBarDoesAbc) {
    std::stringstream ss1("DB POST SELL OIL k 1 10.5");
    std::stringstream ss2("DB REVOKE k 1");
    std::stringstream ss3("DB CHECK + 1");
    std::stringstream ss4("DB AGGRESS + 1 10");
    std::stringstream ss5("DB AGGRESS 1");
    std::stringstream ss6("DB REVOKE");
    std::stringstream ss7("");
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}