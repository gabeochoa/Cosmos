#ifndef ORDER_H
#define ORDER_H

#include <string> 
#include <iostream>
#include <vector>

class Order 
{
    private:
        std::string dealer;
        std::string side;
        std::string commodity;
        int orderid; 
        int amount;
        double price;

    public:
        Order(std::string dealer_in, std::string side_in, std::string commodity_in, 
                int orderid_in, int amount_in, double price_in):
        dealer(dealer_in), side(side_in), commodity(commodity_in), 
                orderid(orderid_in), amount(amount_in), price(price_in)
        {}
        std::string getDealer() const{return dealer;}
        std::string getSide() const{return side;}
        std::string getCommodity() const{return commodity;}
        int getOrderId() const{return orderid;}
        int getAmount() const{return amount;}
        double getPrice() const{return price;}
        friend std::ostream& operator<<(std::ostream& os, const Order& ord)
        {
            os << ord.dealer << ", ";
            os << ord.side << ", ";
            os << ord.commodity << ", ";
            os << ord.orderid << ", ";
            os << ord.amount << ", ";
            os << ord.price;
            return os;
        }
};

#endif //ORDER_H

inline bool operator< (const Order& lhs, const Order& rhs)
{
    if(lhs.getDealer() == rhs.getDealer())
    {
        if(lhs.getSide() == rhs.getSide())
        {
            if(lhs.getCommodity() == rhs.getCommodity())
            {
                if(lhs.getOrderId() == rhs.getOrderId())
                { 
                    if(lhs.getAmount() == rhs.getAmount())
                    {
                        return lhs.getPrice() < rhs.getPrice();
                    }
                    return lhs.getAmount() < rhs.getAmount();
                }
                return lhs.getOrderId() < rhs.getOrderId();
            }
            return lhs.getCommodity() < rhs.getCommodity();
        }
        return lhs.getSide() < rhs.getSide();
    }
    return lhs.getDealer() < rhs.getDealer();
}
inline bool operator> (const Order& lhs, const Order& rhs){ return rhs < lhs; }
inline bool operator<=(const Order& lhs, const Order& rhs){ return !(lhs > rhs); }
inline bool operator>=(const Order& lhs, const Order& rhs){ return !(lhs < rhs); }




