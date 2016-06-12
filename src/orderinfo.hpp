#ifndef ORDERINFO_H
#define ORDERINFO_H

#include <string> 
#include <iostream>
#include <vector>

class OrderInfo 
{
    public:
        enum OrderStatus {LIST, INFO, REPORT, FILLED, ERROR, REVOKED, POST}; 
        enum ErrorCode {UNAUTHORIZED, UNKNOWN_ORDER, UNKNOWN_COMMODITY, INVALID_MESSAGE}; 
    private:
        Order ord;
        OrderStatus status;
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
        static std::string GenerateOutput(OrderStatus status)
        {
            //VALID FOR:
            //Error
        }
        static std::string GenerateOutput(int orderid, OrderStatus status)
        {
            //Valid for FILLED&REVOKED

        }
        static std::string GenerateOutput(Order order, OrderStatus status)
        {
            //Valid for INFO 
        }
        static std::string GenerateOutput(std::vector<Order> orders, OrderStatus status)
        {

        }
};

#endif //ORDERINFO_H

