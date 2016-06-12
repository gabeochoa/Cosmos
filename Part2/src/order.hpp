#ifndef ORDER_H
#define ORDER_H

#include <string> 
#include <iostream>
#include <vector>
#include <sstream>

class Order 
{
    private:
        std::string dealer;
        std::string side;
        std::string commodity;
        int orderid; 
        int amount;
        double price;

        Order(std::string dealer_in, std::string side_in, std::string commodity_in, 
                int orderid_in, int amount_in, double price_in):
        dealer(dealer_in), side(side_in), commodity(commodity_in), 
                orderid(orderid_in), amount(amount_in), price(price_in)
        {}

    public:
        //TODO: dont allow the processor to get the orderid?
        //      have the order do it?
        static Order createOrder(std::string dealer_in, std::string side_in, std::string commodity_in, 
                int orderid_in, int amount_in, double price_in)
        {
            Order o(dealer_in, side_in, commodity_in, orderid_in, amount_in, price_in);
            return o;
        }
        std::string getDealer() const{return dealer;}
        std::string getSide() const{return side;}
        std::string getCommodity() const{return commodity;}
        int getOrderId() const{return orderid;}
        int getAmount() const{return amount;}
        double getPrice() const{return price;}
        void removeAmount(int quant) {amount -= quant;}
        std::string getString()
        {
            std::stringstream os;
            os << orderid << " ";
            os << dealer << " ";
            os << side << " ";
            os << commodity << " ";
            os << amount << " ";
            os.precision(2);
            os << std::fixed;
            os << price;
            return os.str();
        }
        friend std::ostream& operator<<(std::ostream& os, const Order& ord)
        {
            os << ord.orderid << " ";
            os << ord.dealer << " ";
            os << ord.side << " ";
            os << ord.commodity << " ";
            os << ord.amount << " ";
            os.precision(2);
            os << std::fixed;
            os << ord.price;
            return os;
        }
};


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

inline bool operator== (const Order& lhs, const Order& rhs){ return !(lhs < rhs) && !(lhs>rhs); }
inline bool operator!= (const Order& lhs, const Order& rhs){ return !(rhs == lhs); }




#endif //ORDER_H
