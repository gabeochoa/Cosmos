#ifndef DATABASE_H
#define DATABASE_H

#include <string> 
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include "order.hpp"
#include "orderinfo.hpp"
/*
    This class exists to blackbox
    the process that would be calling a db

    In this case, it is in memory or on disk
    but the api could be extended to use a db
*/

class Database 
{
    private:
        std::vector<Order> mydata;       
        std::vector<Order> filteredData;
        std::map<int, OrderInfo::OrderStatus> info;
        int orderID = 0;
    public:
        Database();
        void addData(Order);
        void removeData(std::string, Order);
        void removeData(std::string, int);
        bool aggress(std::string, int, int);
        std::vector<Order> findData(bool);
        void filterData(std::string, std::string);
        std::vector<Order>::iterator getOrderFromID(int);
        void getStatus(std::string, int);
        int getOrderID();
        void print(std::vector<Order> orders);
        void print(Order orders);
};

#endif //DATABASE_H








