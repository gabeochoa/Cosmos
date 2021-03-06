#include "processor.hpp"

Processor* Processor::_instance = NULL;

Processor Processor::getInstance()
{ 
    if (!_instance)
        _instance = new Processor();
    return *_instance; 
}

std::string Processor::run(Database& database, std::vector<std::string> strToProc)
{
    std::string cmd = strToProc[1];
    std::string dealer = strToProc[0];
    std::string side = "N/A";
    std::string commodity = "N/A"; 
    int orderid =-1, amount=-1;
    double price = -1;

    if(cmd == "POST")
    {
        side = strToProc[2];
        commodity =  strToProc[3]; 
        orderid = database.getNextOrderID();
        amount= atoi(strToProc[4].c_str());
        price = atof(strToProc[5].c_str());
        Order o = Order::createOrder(dealer, side, commodity, orderid, amount, price);
        database.addData(o);
    }else if(cmd == "REVOKE"){
        database.removeData(strToProc[0],atoi(strToProc[2].c_str()));
    }else if(cmd == "CHECK"){
        database.getStatus(strToProc[0],atoi(strToProc[2].c_str()));
    }else if(cmd == "LIST"){
        bool useFilter = false;
        //std::cout << strToProc.size() << std::endl;
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
        database.print(found);

    }else if(cmd == "AGGRESS"){
        strToProc.erase(strToProc.begin());//erase dealer
        strToProc.erase(strToProc.begin());//erase cmd
        for(uint i =0; i<strToProc.size(); i+=2)
        {
            database.aggress(/*dealer,*/ atoi(strToProc[i].c_str()), atoi(strToProc[i+1].c_str()));
        }
    }  
    return database.log();   
}

