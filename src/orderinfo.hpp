#ifndef ORDERINFO_H
#define ORDERINFO_H

#include <string> 
#include <iostream>
#include <vector>
#include "order.hpp"

class OrderInfo 
{
    public:
        enum OrderStatus {LIST, INFO, REPORT, FILLED, REVOKED, POST}; 
        enum ErrorCode {UNAUTHORIZED, UNKNOWN_ORDER, UNKNOWN_COMMODITY, INVALID_MESSAGE}; 
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
        static std::string GenerateOutput(ErrorCode status)
        {
            switch(status)
            {
                case UNAUTHORIZED:
                    return "UNAUTHORIZED";
                case UNKNOWN_ORDER:
                    return "UNKNOWN_ORDER";
                case UNKNOWN_COMMODITY:
                    return "UNKNOWN_COMMODITY";
                case INVALID_MESSAGE:
                    return "INVALID_MESSAGE";
                default:
                    return "INVALID ERROR";
            }
            return error();
        }
        static std::string GenerateOutput(int orderid, OrderStatus status)
        {
            //Valid for FILLED&REVOKED
            std::string ret = "";
            ret += std::to_string(orderid) + " HAS BEEN ";
            if(status == OrderStatus::FILLED)
                ret += "FILLED";
            else if(status == OrderStatus::REVOKED)
                ret += "REVOKED";
            else
            {
                return error();
            }
            return ret;
        }
        static std::string GenerateOutput(Order order, OrderStatus status)
        {
            //Valid for INFO 
            if(status != OrderStatus::INFO)
            {
                return error();
            }
            return "";

        }
        static std::string GenerateOutput(std::vector<Order> orders, OrderStatus status)
        {
           //Valid for INFO_LIST
            if(status != OrderStatus::LIST)
            {
                return error();
            } 
            return "";
        }
};

#endif //ORDERINFO_H










