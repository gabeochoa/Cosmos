#ifndef ORDERINFO_H
#define ORDERINFO_H

#include <string> 
#include <iostream>
#include <vector>
#include <cstdlib>
#include "status-enum.hpp"
#include "order.hpp"


class OrderInfo 
{
    private:
        static std::string error()
        {
            return "INVALID USE OF OUTPUT GENERATOR";
        }
    public:
        /*
            OUTPUT_MESSAGE = ORDER_INFO | ORDER_INFO_LIST | TRADE_REPORT | FILLED | ERROR | REVOKED | POST_CONFIRMATION
            ORDER_INFO_LIST = ORDER_INFO ‘\n’ ( ORDER_INFO ‘\n’ )* "END OF LIST"
            ORDER_INFO = ORDER_ID DEALER_ID SIDE COMMODITY AMOUNT PRICE
            TRADE_REPORT = ACTION AMOUNT COMMODITY “@” PRICE “FROM” DEALER_ID
            ACTION = “BOUGHT” | “SOLD”
            FILLED = ORDER_ID “HAS BEEN FILLED”
            REVOKED = ORDER_ID “HAS BEEN REVOKED”
            ERROR = “UNAUTHORIZED” | “UNKNOWN_ORDER” | “UNKOWN_DEALER” | “UNKNOWN_COMMODITY” | “INVALID_MESSAGE”
            POST_CONFIRMATION = ORDER_INFO “HAS BEEN POSTED”
        */
        static std::string GenerateOutput(StatusEnum::ErrorCode status)
        {
            switch(status)
            {
                case StatusEnum::UNAUTHORIZED:
                    return "UNAUTHORIZED";
                case StatusEnum::UNKNOWN_ORDER:
                    return "UNKNOWN_ORDER";
                case StatusEnum::UNKNOWN_COMMODITY:
                    return "UNKNOWN_COMMODITY";
                case StatusEnum::INVALID_MESSAGE:
                    return "INVALID_MESSAGE";
                default:
                    return "INVALID ERROR";
            }
            return error();
        }
        static std::string GenerateOutput(int orderid, StatusEnum::OrderStatus status)
        {
            //Valid for FILLED&REVOKED
            std::stringstream ret;
            ret << orderid;
            ret << " HAS BEEN ";
            if(status == StatusEnum::FILLED)
                ret << "FILLED";
            else if(status == StatusEnum::REVOKED)
                ret << "REVOKED";
            else
            {
                return error();
            }
            return ret.str();
        }
        static std::string GenerateOutput(Order order, StatusEnum::OrderStatus status)
        {
            //Valid for INFO, POST
            if(status != StatusEnum::INFO && status != StatusEnum::POST)
            {
                return error();
            }
            return order.getString() + (status == StatusEnum::POST? " HAS BEEN POSTED" : "");
        }
        static std::string GenerateOutput(std::vector<Order> orders, StatusEnum::OrderStatus status)
        {
           //Valid for INFO_LIST
            if(status != StatusEnum::LIST)
            {
                return error();
            } 
            std::stringstream ret;

            for(std::vector<Order>::iterator iter = orders.begin(); iter != orders.end(); iter++)
                ret << iter->getString() + "\n";
            ret << "END OF LIST";
            return ret.str();
        }
        static std::string GenerateOutput(std::string action, int quant, Order order, StatusEnum::OrderStatus status)
        {
           //Valid for REPORT
            if(status != StatusEnum::REPORT)
            {
                return error();
            } 
            //TODO: fix price to 2 decimal points
            std::stringstream os;
            os << action << " "; 
            os << quant << " "; 
            os << order.getCommodity() << " @ "; 
            os.precision(2);
            os << std::fixed;
            os << order.getPrice() << " FROM ";
            os << order.getDealer();
            return os.str();
        }
};

#endif //ORDERINFO_H










