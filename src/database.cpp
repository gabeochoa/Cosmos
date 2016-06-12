#include "database.hpp"

Database::Database()
{

}

void Database::addData(Order data)
{
    //just add the data in this case
    mydata.push_back(data);
}

// void Database::removeData(std::string dealer, Order data)
// {
//     for(auto iter = mydata.begin(); iter != mydata.end(); iter++)
//     {
//         if(*iter == data)
//         {
//             if(data.getDealer() == dealer)
//             {
//                 mydata.erase(iter);
//                 return;
//             }
//             else
//             {
//                 std::cout << OrderInfo::GenerateOutput(OrderInfo::ErrorCode::UNAUTHORIZED) << std::endl;
//                 return;
//             }
//         }
//     }
//     //else
//         //Data not found
// }

void Database::removeData(std::string dealer, int id)
{
    for(auto iter = mydata.begin(); iter != mydata.end(); iter++)
    {
        if(iter->getOrderId() == id)
        {
            if(iter->getDealer() == dealer)
            { 
                mydata.erase(iter);
                info.insert(std::pair<int, OrderInfo::OrderStatus>(id,  OrderInfo::OrderStatus::REVOKED));
                return;
            }
            else
            {
                std::cout << OrderInfo::GenerateOutput(OrderInfo::ErrorCode::UNAUTHORIZED) << std::endl;
                return; 
            }
        }
    }
}

bool Database::aggress(std::string dealer, int order_id, int quantity)
{
    std::vector<Order>::iterator x = getOrderFromID(order_id);
    if(x == mydata.end())
    {
        std::cout << OrderInfo::GenerateOutput(OrderInfo::ErrorCode::UNKNOWN_ORDER) << std::endl;
        return false;
    }
    if(quantity > x->getAmount())
    { 
        //TODO This might need to be changed??
        std::cout << OrderInfo::GenerateOutput(OrderInfo::ErrorCode::INVALID_MESSAGE) << std::endl;
        return false;
    }
    //TODO literally no other checks?
    info.insert(std::pair<int, OrderInfo::OrderStatus>(order_id,  OrderInfo::OrderStatus::FILLED));
    x->removeAmount(quantity);

    //std::cout << OrderInfo::GenerateOutput(OrderInfo::OrderStatus::REPORT) << std::endl;    
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
        if(!info.count(orderid))
        {
            std::cout << OrderInfo::GenerateOutput(OrderInfo::ErrorCode::UNKNOWN_ORDER) << std::endl;
        }
        else
        {
            std::cout << OrderInfo::GenerateOutput(orderid, info[orderid]) << std::endl;
        }
        return;
    }
    if(iter->getDealer() != dealer)
    {
        std::cout << OrderInfo::GenerateOutput(OrderInfo::ErrorCode::UNAUTHORIZED) << std::endl;
        return;
    }

    if(iter->getAmount() == 0)
    {
        std::cout << OrderInfo::GenerateOutput(iter->getOrderId(), OrderInfo::OrderStatus::FILLED) << std::endl;
    }
    else if(iter->getAmount() > 0)
    {
        std::cout << OrderInfo::GenerateOutput(*iter, OrderInfo::OrderStatus::INFO) << std::endl;
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


