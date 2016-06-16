#ifndef DATABASE_H
#define DATABASE_H

#include <string> 
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include "order.hpp"
#include "orderinfo.hpp"
#include "logger.hpp"
/*
    This class exists to blackbox
    the process that would be calling a db

    In this case, it is in memory or on disk
    but the api could be extended to use a db
*/

class Database 
{
    #ifndef TEST_FRIENDS
    #define TEST_FRIENDS
    #endif
    TEST_FRIENDS;

    private:
        std::vector<Order> mydata;       
        std::vector<Order> filteredData;
        std::map<int, StatusEnum::OrderStatus> info;
        int orderID;
        Logger* logger;
    public:
        Database();
        void addData(Order);
        void removeData(std::string, Order);
        void removeData(std::string, int);
        bool aggress(/*std::string, */int, int);
        std::vector<Order> findData(bool);
        void filterData(std::string, std::string);
        std::vector<Order>::iterator getOrderFromID(int);
        void getStatus(std::string, int);
        int getNextOrderID();
        void print(std::vector<Order> orders);
        void print(Order orders);
        std::string log();
        void clearLog();
};

#endif //DATABASE_H








