#ifndef DATABASE_H
#define DATABASE_H

#include <string> 
#include <iostream>
#include <algorithm>
#include <vector>
#include "order.hpp"

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
        int orderID = 0;
    public:
        Database();
        void addData(Order);
        void removeData(Order);
        std::vector<Order> findData(bool);
        void filterData(std::string, std::string);
        int getOrderID();
        void print();
};

#endif //DATABASE_H








