#include "database.hpp"

Database::Database()
{

}

void Database::addData(Order data)
{
    //just add the data in this case
    mydata.push_back(data);
}

void Database::removeData(std::string dealer, Order data)
{
    for(auto iter = mydata.begin(); iter != mydata.end(); iter++)
    {
        if(*iter == data)
            if(data.getDealer() == dealer)
                mydata.erase(iter);
            //else
                //ERROR Cannot remove another dealers order
                //return;
    }
    //else
        //Data not found
}

void Database::removeData(std::string dealer, int id)
{
    for(auto iter = mydata.begin(); iter != mydata.end(); iter++)
    {
        if(iter->getOrderId() == id)
        {
            if(iter->getDealer() == dealer)
            { 
               mydata.erase(iter);
                return;
            }
            else
            {
                std::cout << "ERROR Cannot remove another dealers order" << std::endl;
                return; 
            }
        }
    }
}

bool Database::aggress(std::string dealer, int order_id, int quantity)
{
    std::vector<Order>::iterator x = getOrderFromID(order_id);
    if(x == mydata.end())
        return false;

    if(quantity > x->getAmount())
    {
        return false;
    }
    //TODO literally no other checks?
    x->removeAmount(quantity);

    return true;
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

std::vector<Order>::iterator Database::getOrderFromID(int id)
{
    for(auto iter = mydata.begin(); iter != mydata.end(); iter++)
        if(iter->getOrderId() == id)
            return iter;
    return mydata.end();
}

void Database::getStatus(std::string dealer, int orderid)
{
    //TODO: create some kind of 'info' struct to pass this info
    std::vector<Order>::iterator iter = getOrderFromID(orderid);
    if(iter == mydata.end())
    {
        std::cout << "ERROR: Invalid OrderID" << std::endl;
        return;
    }
    if(iter->getDealer() != dealer)
    {
        std::cout << "ERROR: Can only check status on own Orders" << std::endl;
        return;
    }

    if(iter->getAmount() == 0)
    {
        std::cout << "FILLED: Remaining amount zero" << std::endl;
    }
    else if(iter->getAmount() > 0)
    {
        std::cout << *iter << std::endl;  
    }
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


