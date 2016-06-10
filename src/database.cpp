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
    return useFilter? filteredData : mydata;
}
void Database::filterData(std::string comm,  std::string dealer_ID)
{
    filteredData.clear();
    for(auto iter = mydata.begin(); iter != mydata.end(); iter++)
    {
        if(comm != "" && iter->getCommodity() != comm)
            continue;
        if(dealer_ID != "" && iter->getDealer() != dealer_ID)
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


