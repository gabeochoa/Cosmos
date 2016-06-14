#include "database.hpp"

Database::Database()
{
    logger = new Logger();
}

void Database::addData(Order data)
{
    //just add the data in this case
    mydata.push_back(data);
    *logger << OrderInfo::GenerateOutput(data, OrderInfo::OrderStatus::POST) << std::endl;       
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
                info.insert(std::pair<int, OrderInfo::OrderStatus>(id,  OrderInfo::OrderStatus::REVOKED));
                *logger << OrderInfo::GenerateOutput(id, OrderInfo::OrderStatus::REVOKED) << std::endl;
                return;
            }
            else
            {
                *logger << OrderInfo::GenerateOutput(OrderInfo::ErrorCode::UNAUTHORIZED) << std::endl;
                return; 
            }
        }
    }
}

bool Database::aggress(/*std::string dealer,*/ int order_id, int quantity)
{
    std::vector<Order>::iterator x = getOrderFromID(order_id);
    if(x == mydata.end())
    {
        *logger << OrderInfo::GenerateOutput(OrderInfo::ErrorCode::UNKNOWN_ORDER) << std::endl;
        return false;
    }
    if(quantity > x->getAmount())
    { 
        //TODO This might need to be changed??
        *logger << OrderInfo::GenerateOutput(OrderInfo::ErrorCode::UNAUTHORIZED) << std::endl;
        return false;
    }
    //TODO literally no other checks?
    info.insert(std::pair<int, OrderInfo::OrderStatus>(order_id,  OrderInfo::OrderStatus::FILLED));
    x->removeAmount(quantity);

    *logger << OrderInfo::GenerateOutput(
        "BOUGHT", 
        quantity, 
        *x,
        OrderInfo::OrderStatus::REPORT) << std::endl;    
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
            *logger << OrderInfo::GenerateOutput(OrderInfo::ErrorCode::UNKNOWN_ORDER) << std::endl;
        }
        else
        {
            *logger << OrderInfo::GenerateOutput(orderid, info[orderid]) << std::endl;
        }
        return;
    }
    if(iter->getDealer() != dealer)
    {
        *logger << OrderInfo::GenerateOutput(OrderInfo::ErrorCode::UNAUTHORIZED) << std::endl;
        return;
    }

    if(iter->getAmount() == 0)
    {
        *logger << OrderInfo::GenerateOutput(iter->getOrderId(), OrderInfo::OrderStatus::FILLED) << std::endl;
    }
    else if(iter->getAmount() > 0)
    {
        *logger << OrderInfo::GenerateOutput(*iter, OrderInfo::OrderStatus::INFO) << std::endl;
    }
}

void Database::print(std::vector<Order> orders)
{
    *logger << OrderInfo::GenerateOutput(orders, OrderInfo::OrderStatus::LIST) << std::endl;
}
void Database::print(Order order)
{
    *logger << OrderInfo::GenerateOutput(order, OrderInfo::OrderStatus::INFO) << std::endl;
}

std::string Database::log()
{
    return logger->str();
}

void Database::clearLog()
{
    delete logger;
    logger = new Logger();
}

