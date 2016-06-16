#include "gtest/gtest.h"


/*
TODO: Fix this. 
    Maybe it would be better to have getters public only during tests?

class A{

    #ifndef TEST
    private:
    #else
    public:
    #endif
        int getInt(){};
    
    private:
        //private members
    public:
        //public members
};

    Or to use a public const getter?
*/

#define TEST_FRIENDS \
    friend class DatabaseTest_DatabaseMaster_Test; 

#include "database.hpp"

#include <string>
#include <sstream>
#include <vector>

class DatabaseTest : public ::testing::Test {
    protected:
    // You can remove any or all of the following functions if its body
    // is empty.
    std::vector<Order> sample_orders;
    DatabaseTest() {
    // You can do set-up work for each test here.

    }

    virtual ~DatabaseTest() {
    // You can do clean-up work that doesn't throw exceptions here.
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    virtual void SetUp() {
    // Code here will be called immediately after the constructor (right
    // before each test).
        Order a = Order::createOrder("DB", "BUY", "GOLD", 0, 130, 12.35);
        Order b = Order::createOrder("JPM", "SELL", "SILV", 1, 134, 23.4);
        Order c = Order::createOrder("HSBC", "BUY", "PORK", 2, 543, 2.34);
        Order d = Order::createOrder("JPM", "SELL", "OIL", 3, 624, 24.63);
        Order e = Order::createOrder("BOFA", "BUY", "RICE", 4, 837, 36.4);
        Order f = Order::createOrder("DB", "SELL", "OIL", 5, 235, 457.8);
        Order g = Order::createOrder("HSBC", "BUY", "PORK", 6, 343, 43.52);
        Order h = Order::createOrder("BOFA", "SELL", "SILV", 7, 345, 9600);
        Order i = Order::createOrder("JPM", "BUY", "GOLD", 8, 115, 3.90);
        Order j = Order::createOrder("HSBC", "SELL", "GOLD", 9, 320, 20.39);
        sample_orders.push_back(a);
        sample_orders.push_back(b);
        sample_orders.push_back(c);
        sample_orders.push_back(d);
        sample_orders.push_back(e);
        sample_orders.push_back(f);
        sample_orders.push_back(g);
        sample_orders.push_back(h);
        sample_orders.push_back(i);
        sample_orders.push_back(j);
    }

    virtual void TearDown() {
    // Code here will be called immediately after each test (right
    // before the destructor).
        sample_orders.clear();
    }

};

 
TEST_F(DatabaseTest, DatabaseConstruct) {
    Database database;
}
 
TEST_F(DatabaseTest, DatabaseMaster) {
    // Database database;
    // int next = 0;
    // for(int i=0; i<10; i++)
    // {
    //     database.addData(sample_orders[next]);
    //     ASSERT_EQ(database.mydata[next], sample_orders[randomIndex]);
    //     int randomIndex = rand() % sample_orders.size();
    //     database.removeData(sample_orders[next]);
    //     ASSERT_EQ(database.mydata[next], sample_orders[randomIndex]);
    //     next++;
    // }
}











