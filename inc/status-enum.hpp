#ifndef STATUSENUM_HPP
#define STATUSENUM_HPP

namespace StatusEnum{
    enum OrderStatus 
    {   
        LIST, 
        INFO, 
        REPORT, 
        FILLED, 
        REVOKED, 
        POST
    }; 

    enum ErrorCode 
    {
        UNAUTHORIZED, 
        UNKNOWN_ORDER, 
        UNKNOWN_COMMODITY, 
        INVALID_MESSAGE
    }; 
}

#endif //STATUSENUM_HPP