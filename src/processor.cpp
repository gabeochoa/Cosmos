#include "processor.hpp"


Processor::Processor()
{
}

void Processor::run(Database& database, std::vector<std::string> strToProc)
{
    for(std::string s : strToProc)
        std::cout << s << std::endl;
    std::string cmd = strToProc[1];

    std::string dealer = "N/A";
    std::string side = "N/A";
    std::string commodity = "N/A"; 
    int orderid =-1, amount=-1;
    double price = -1;

    if(cmd == "POST")
    {
        dealer = strToProc[0];
        side = strToProc[2];
        commodity =  strToProc[3]; 
        orderid = database.getOrderID();
        amount=stoi(strToProc[4]);
        price =stof(strToProc[5]);
        Order o(dealer, side, commodity, orderid, amount, price);
        database.addData(o);
    }else if(cmd == "REVOKE" || cmd == "CHECK"){

    }else if(cmd == "LIST"){
    }else if(cmd == "AGRESS"){
    }


    //Order(std::string dealer_in, std::string side_in, std::string commodity_in, 
    // int orderid_in, int amount_in, double price_in)
    
        
}

