#include "parser.hpp"

#include "gtest/gtest.h"
#include <string>
#include <sstream>

class ParserTest : public ::testing::Test {
    protected:
    // You can remove any or all of the following functions if its body
    // is empty.
    std::string errstr;
    std::string inputstr;
    std::vector<std::string> outputvec;

    ParserTest() {
    // You can do set-up work for each test here.

    }

    virtual ~ParserTest() {
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
        errstr.clear();
        inputstr.clear();
        outputvec.clear();
    }

};


//bool isValid(std::string&, std::string&, std::vector<std::string>&);  
TEST_F(ParserTest, FalseOnBadDealer) {
    Parser parser;
    inputstr = "BADDEALER POST BUY GOLD 12 34.56";
    bool outcome = parser.isValid(errstr, inputstr, outputvec);
    ASSERT_FALSE(outcome) << "output string = " << ::testing::PrintToString(outputvec);
}
TEST_F(ParserTest, FalseOnBadCommand) {
    Parser parser;
    inputstr = "DB BADCOMMAND BUY GOLD 12 34.56";
    bool outcome = parser.isValid(errstr, inputstr, outputvec);
    ASSERT_FALSE(outcome) << "output string = " << ::testing::PrintToString(outputvec);
}
TEST_F(ParserTest, FalseOnBadSide) {
    Parser parser;
    inputstr = "DB POST BADSIDE GOLD 12 34.56";
    bool outcome = parser.isValid(errstr, inputstr, outputvec);
    ASSERT_FALSE(outcome) << "output string = " << ::testing::PrintToString(outputvec);
}
TEST_F(ParserTest, FalseOnBadCommodity) {
    Parser parser;
    inputstr = "DB POST BUY BADCOM 12 34.56";
    bool outcome = parser.isValid(errstr, inputstr, outputvec);
    ASSERT_FALSE(outcome) << "output string = " << ::testing::PrintToString(outputvec);
}
TEST_F(ParserTest, FalseOnBadQuantityNAN) {
    Parser parser;
    inputstr = "DB POST BUY GOLD NAN 34.56";
    bool outcome = parser.isValid(errstr, inputstr, outputvec);
    ASSERT_FALSE(outcome) << "output string = " << ::testing::PrintToString(outputvec);
}
TEST_F(ParserTest, FalseOnBadQuantityNotAnInt) {
    Parser parser;
    inputstr = "DB POST BUY GOLD 12.02 34.56";
    bool outcome = parser.isValid(errstr, inputstr, outputvec);
    ASSERT_FALSE(outcome) << "output string = " << ::testing::PrintToString(outputvec);
}
TEST_F(ParserTest, FalseOnBadPriceNAN) {
    Parser parser;
    inputstr = "DB POST BUY GOLD 12 NAN";
    bool outcome = parser.isValid(errstr, inputstr, outputvec);
    ASSERT_FALSE(outcome) << "output string = " << ::testing::PrintToString(outputvec);
}











