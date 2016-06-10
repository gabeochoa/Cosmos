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
    public:
        Database();
        void addData(Order);
        void removeData(Order);
        std::vector<Order> findData(bool);
        void filterData(int, std::string);

};

#endif //DATABASE_H

Database::Database()
{

}

void Database::addData(Order data)
{
    //just add the data in this case
    mydata.push_back(data);
}

void Database::removeData(Order data)
{
    for(auto iter = mydata.begin(); iter != mydata.end(); iter++)
    {
        //if(*iter == data)
        //    mydata.erase(iter);
    }
}
std::vector<Order> Database::findData(bool useFilter=false)
{
    return useFilter? mydata : filteredData;
}
void Database::filterData(int order_id, std::string comm = "")
{
    filteredData.clear();
    for(auto iter = mydata.begin(); iter != mydata.end(); iter++)
    {
        if(iter->getOrderId() != order_id)
            continue;
        if(comm != "" && iter->getCommodity() != comm)
            continue;
        //gotten to this point
        filteredData.push_back(*iter);
    }
}













