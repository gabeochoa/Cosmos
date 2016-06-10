#include "database.hpp"

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

int Database::getOrderID()
{
    return ++orderID;
}

void Database::print()
{
    std::cout << "----DATABASE-----" << std::endl;
       
    for(auto iter = mydata.begin(); iter != mydata.end(); iter++)
    {
        std::cout << "---------" << std::endl;
        std::cout << *iter << std::endl;
        
    }
    std::cout << "----DATABASE END-----" << std::endl; 
}


