#include "processor.hpp"


Processor::Processor()
{
}

void Processor::run(Database& database, std::vector<std::string> strToProc)
{
    //for(std::string s : strToProc)
    //    std::cout << s << std::endl;
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
        bool useFilter = false;
        std::cout << strToProc.size() << std::endl;
        if(strToProc.size() == 3 )
        {
            database.filterData(strToProc[2], "");
            useFilter = true;
        }
        else if(strToProc.size() == 4)
        {
            database.filterData(strToProc[2], strToProc[3]);
            useFilter = true;
        }

        std::vector<Order> found = database.findData(useFilter);

        for(Order s : found)
            std::cout <<"\t" <<  s << std::endl;
    }else if(cmd == "AGRESS"){
    }


    //Order(std::string dealer_in, std::string side_in, std::string commodity_in, 
    // int orderid_in, int amount_in, double price_in)
    
        
}

