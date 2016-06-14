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
    bool outcome;

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
    outcome = parser.isValid(errstr, inputstr, outputvec);
    ASSERT_FALSE(outcome) << "output string = " << ::testing::PrintToString(outputvec);
}
TEST_F(ParserTest, FalseOnBadCommand) {
    Parser parser;
    inputstr = "DB BADCOMMAND BUY GOLD 12 34.56";
    outcome = parser.isValid(errstr, inputstr, outputvec);
    ASSERT_FALSE(outcome) << "output string = " << ::testing::PrintToString(outputvec);
}
TEST_F(ParserTest, FalseOnBadSide) {
    Parser parser;
    inputstr = "DB POST BADSIDE GOLD 12 34.56";
    outcome = parser.isValid(errstr, inputstr, outputvec);
    ASSERT_FALSE(outcome) << "output string = " << ::testing::PrintToString(outputvec);
}
TEST_F(ParserTest, FalseOnBadCommodity) {
    Parser parser;
    inputstr = "DB POST BUY BADCOM 12 34.56";
    outcome = parser.isValid(errstr, inputstr, outputvec);
    ASSERT_FALSE(outcome) << "output string = " << ::testing::PrintToString(outputvec);
}
TEST_F(ParserTest, FalseOnBadQuantityNAN) {
    Parser parser;
    inputstr = "DB POST BUY GOLD NAN 34.56";
    outcome = parser.isValid(errstr, inputstr, outputvec);
    ASSERT_FALSE(outcome) << "output string = " << ::testing::PrintToString(outputvec);
}
TEST_F(ParserTest, FalseOnBadQuantityNotAnInt) {
    Parser parser;
    inputstr = "DB POST BUY GOLD 12.02 34.56";
    outcome = parser.isValid(errstr, inputstr, outputvec);
    ASSERT_FALSE(outcome) << "output string = " << ::testing::PrintToString(outputvec);
}
TEST_F(ParserTest, FalseOnBadPriceNAN) {
    Parser parser;
    inputstr = "DB POST BUY GOLD 12 NAN";
    outcome = parser.isValid(errstr, inputstr, outputvec);
    ASSERT_FALSE(outcome) << "output string = " << ::testing::PrintToString(outputvec);
}


TEST_F(ParserTest, TrueOnValidDealers) {
    Parser parser;
    inputstr = "DB POST BUY GOLD 12 34.56";
    outcome = parser.isValid(errstr, inputstr, outputvec);
    ASSERT_TRUE(outcome) << "output string = " << ::testing::PrintToString(outputvec);
    inputstr = "JPM POST BUY GOLD 12 34.56";
    outcome = parser.isValid(errstr, inputstr, outputvec);
    ASSERT_TRUE(outcome) << "output string = " << ::testing::PrintToString(outputvec);
    inputstr = "UBS POST BUY GOLD 12 34.56";
    outcome = parser.isValid(errstr, inputstr, outputvec);
    ASSERT_TRUE(outcome) << "output string = " << ::testing::PrintToString(outputvec);
    inputstr = "RBC POST BUY GOLD 12 34.56";
    outcome = parser.isValid(errstr, inputstr, outputvec);
    ASSERT_TRUE(outcome) << "output string = " << ::testing::PrintToString(outputvec);
    inputstr = "BARX POST BUY GOLD 12 34.56";
    outcome = parser.isValid(errstr, inputstr, outputvec);
    ASSERT_TRUE(outcome) << "output string = " << ::testing::PrintToString(outputvec);
    inputstr = "MS POST BUY GOLD 12 34.56";
    outcome = parser.isValid(errstr, inputstr, outputvec);
    ASSERT_TRUE(outcome) << "output string = " << ::testing::PrintToString(outputvec);
    inputstr = "CITI POST BUY GOLD 12 34.56";
    outcome = parser.isValid(errstr, inputstr, outputvec);
    ASSERT_TRUE(outcome) << "output string = " << ::testing::PrintToString(outputvec);
    inputstr = "BOFA POST BUY GOLD 12 34.56";
    outcome = parser.isValid(errstr, inputstr, outputvec);
    ASSERT_TRUE(outcome) << "output string = " << ::testing::PrintToString(outputvec);
    inputstr = "RBS POST BUY GOLD 12 34.56";
    outcome = parser.isValid(errstr, inputstr, outputvec);
    ASSERT_TRUE(outcome) << "output string = " << ::testing::PrintToString(outputvec);
    inputstr = "HSBC POST BUY GOLD 12 34.56";
    outcome = parser.isValid(errstr, inputstr, outputvec);
    ASSERT_TRUE(outcome) << "output string = " << ::testing::PrintToString(outputvec);
}

TEST_F(ParserTest, TrueOnValidSides){
    Parser parser;
    inputstr = "DB POST BUY GOLD 12 34.56";
    outcome = parser.isValid(errstr, inputstr, outputvec);
    ASSERT_TRUE(outcome) << "output string = " << ::testing::PrintToString(outputvec);
    inputstr = "DB POST SELL GOLD 12 34.56";
    outcome = parser.isValid(errstr, inputstr, outputvec);
    ASSERT_TRUE(outcome) << "output string = " << ::testing::PrintToString(outputvec);
}  
TEST_F(ParserTest, FalseOnInvalidSides){
    Parser parser;
    inputstr = "DB POST WRONG GOLD 12 34.56";
    outcome = parser.isValid(errstr, inputstr, outputvec);
    ASSERT_FALSE(outcome) << "output string = " << ::testing::PrintToString(outputvec);
}    

TEST_F(ParserTest, TrueOnValidCommodity){
    Parser parser;
    inputstr = "DB POST BUY GOLD 12 34.56";
    outcome = parser.isValid(errstr, inputstr, outputvec);
    ASSERT_TRUE(outcome) << "output string = " << ::testing::PrintToString(outputvec);
    inputstr = "DB POST BUY SILV 12 34.56";
    outcome = parser.isValid(errstr, inputstr, outputvec);
    ASSERT_TRUE(outcome) << "output string = " << ::testing::PrintToString(outputvec);
    inputstr = "DB POST BUY PORK 12 34.56";
    outcome = parser.isValid(errstr, inputstr, outputvec);
    ASSERT_TRUE(outcome) << "output string = " << ::testing::PrintToString(outputvec);
    inputstr = "DB POST BUY OIL 12 34.56";
    outcome = parser.isValid(errstr, inputstr, outputvec);
    ASSERT_TRUE(outcome) << "output string = " << ::testing::PrintToString(outputvec);
    inputstr = "DB POST BUY RICE 12 34.56";
    outcome = parser.isValid(errstr, inputstr, outputvec);
    ASSERT_TRUE(outcome) << "output string = " << ::testing::PrintToString(outputvec);
}    

TEST_F(ParserTest, FalseOnInvalidCommodity){
    Parser parser;
    inputstr = "DB POST BUY WRONG 12 34.56";
    outcome = parser.isValid(errstr, inputstr, outputvec);
    ASSERT_FALSE(outcome) << "output string = " << ::testing::PrintToString(outputvec);
}   


TEST_F(ParserTest, TrueOnValidPOST) {
    Parser parser;
    inputstr = "DB POST BUY GOLD 12 34.56";
    outcome = parser.isValid(errstr, inputstr, outputvec);
    ASSERT_TRUE(outcome) << "output string = " << ::testing::PrintToString(outputvec);
}

TEST_F(ParserTest, FalseOnInvalidPOST_NumArgs) {
    Parser parser;
    inputstr = "DB POST";
    outcome = parser.isValid(errstr, inputstr, outputvec);
    ASSERT_FALSE(outcome) << "output string = " << ::testing::PrintToString(outputvec);
    inputstr = "DB POST BUY";
    outcome = parser.isValid(errstr, inputstr, outputvec);
    ASSERT_FALSE(outcome) << "output string = " << ::testing::PrintToString(outputvec);
    inputstr = "DB POST BUY GOLD";
    outcome = parser.isValid(errstr, inputstr, outputvec);
    ASSERT_FALSE(outcome) << "output string = " << ::testing::PrintToString(outputvec);
    inputstr = "DB POST BUY GOLD 12";
    outcome = parser.isValid(errstr, inputstr, outputvec);
    ASSERT_FALSE(outcome) << "output string = " << ::testing::PrintToString(outputvec);
    inputstr = "DB POST BUY GOLD 12 13.45 EXTRA";
    outcome = parser.isValid(errstr, inputstr, outputvec);
    ASSERT_FALSE(outcome) << "output string = " << ::testing::PrintToString(outputvec);
}

TEST_F(ParserTest, TrueOnValidRevoke) {
    Parser parser;
    inputstr = "DB REVOKE 12";
    outcome = parser.isValid(errstr, inputstr, outputvec);
    ASSERT_TRUE(outcome) << "output string = " << ::testing::PrintToString(outputvec);
}

TEST_F(ParserTest, FalseOnInvalidRevoke_NumArgs) {
    Parser parser;
    inputstr = "DB REVOKE";
    outcome = parser.isValid(errstr, inputstr, outputvec);
    ASSERT_FALSE(outcome) << "output string = " << ::testing::PrintToString(outputvec);
    inputstr = "DB REVOKE 12 EXTRA";
    outcome = parser.isValid(errstr, inputstr, outputvec);
    ASSERT_FALSE(outcome) << "output string = " << ::testing::PrintToString(outputvec);
}


TEST_F(ParserTest, TrueOnValidCheck) {
    Parser parser;
    inputstr = "DB CHECK 12";
    outcome = parser.isValid(errstr, inputstr, outputvec);
    ASSERT_TRUE(outcome) << "output string = " << ::testing::PrintToString(outputvec);
}

TEST_F(ParserTest, FalseOnInvalidCheck_NumArgs) {
    Parser parser;
    inputstr = "DB CHECK";
    outcome = parser.isValid(errstr, inputstr, outputvec);
    ASSERT_FALSE(outcome) << "output string = " << ::testing::PrintToString(outputvec);
    inputstr = "DB CHECK 12 EXTRA2";
    outcome = parser.isValid(errstr, inputstr, outputvec);
    ASSERT_FALSE(outcome) << "output string = " << ::testing::PrintToString(outputvec);
}



TEST_F(ParserTest, TrueOnValidList) {
    Parser parser;
    inputstr = "DB LIST";
    outcome = parser.isValid(errstr, inputstr, outputvec);
    ASSERT_TRUE(outcome) << "output string = " << ::testing::PrintToString(outputvec);
}

TEST_F(ParserTest, FalseOnInvalidList_NumArgs) {
    Parser parser;
    inputstr = "DB LIST EXTRA1";
    outcome = parser.isValid(errstr, inputstr, outputvec);
    ASSERT_FALSE(outcome) << "output string = " << ::testing::PrintToString(outputvec);
    inputstr = "DB LIST EXTRA1 EXTRA2";
    outcome = parser.isValid(errstr, inputstr, outputvec);
    ASSERT_FALSE(outcome) << "output string = " << ::testing::PrintToString(outputvec);
}



TEST_F(ParserTest, TrueOnValidAggress) {
    Parser parser;
    inputstr = "DB AGGRESS 12 34";
    outcome = parser.isValid(errstr, inputstr, outputvec);
    ASSERT_TRUE(outcome) << "output string = " << ::testing::PrintToString(outputvec);
    inputstr = "DB AGGRESS 12 34 56 78";
    outcome = parser.isValid(errstr, inputstr, outputvec);
    ASSERT_TRUE(outcome) << "output string = " << ::testing::PrintToString(outputvec);
    inputstr = "DB AGGRESS 12 34 56 78 89 10";
    outcome = parser.isValid(errstr, inputstr, outputvec);
    ASSERT_TRUE(outcome) << "output string = " << ::testing::PrintToString(outputvec);
}

TEST_F(ParserTest, FalseOnInvalidAggress_NumArgs) {
    Parser parser;
    inputstr = "DB AGGRESS";
    outcome = parser.isValid(errstr, inputstr, outputvec);
    ASSERT_FALSE(outcome) << "output string = " << ::testing::PrintToString(outputvec);
    inputstr = "DB AGGRESS 12";
    outcome = parser.isValid(errstr, inputstr, outputvec);
    ASSERT_FALSE(outcome) << "output string = " << ::testing::PrintToString(outputvec);
}







