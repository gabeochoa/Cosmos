#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;



class ParseException: public std::runtime_error{
    public:
        ParseException():runtime_error("Parse Error"){}
        ParseException(std::string msg):runtime_error(msg.c_str()){}
};

string valid_dealers[] = {"DB","JPM","UBS","RBC","BARX","MS","CITI","BOFA","RBS","HSBC"};
string valid_commodity[] = {"GOLD", "SILV", "PORK", "OIL", "RICE"};

std::vector<std::string> output;
string input = "";
string token; 

/* declarations to allow arbitrary recursion */
void raw(void);
void inputmessage(void);

string side(void);
string price(void);
string amount(void);

string dealerid(void);
void command(void);
string commodity(void);
void post(void);
void revoke_check(void);
void list(void);
void agress(void);

void error(void) { 
    //printf("parse error\n");
    throw new ParseException();
}

void getToken(void) { 
    /* tokens are words */
    size_t startpos = input.find_first_not_of(" \t\n\r");
    if( string::npos != startpos )
    {
            input = input.substr( startpos );
    }
    //cout << "GETTOKEN: input: "  << input << endl;
    startpos = input.find_first_of(" \t\n\r");
    if(string::npos != startpos )
    {
        token = input.substr(0, startpos);
        input = input.substr(startpos);
    }
    else
    {
        token = input;
        input = "";
    }
    //cout << "GETTOKEN: token:"  << token << endl;
}

void raw(void) { 
    inputmessage();
    getToken();
    if (token.size() == 0) {
        return;
    } else {
        //cout << "token " << token << endl;
        error();
    }
}

void inputmessage(void) { 
    output.push_back(dealerid());
    getToken();
    command();
}

string dealerid(void) { 
    string result;
    for(string vd : valid_dealers)
    {
        if(token == vd)
            return vd;
    }
    //std::cout << "ERROR: NO DEALER ID MATCH" << endl;
    error();
    return "";
}

void command(void)
{
    if(token == "POST")
    {
        post();
    }else if(token == "REVOKE" || token == "CHECK"){
        revoke_check();
    }else if(token == "LIST"){
        list();
    }else if(token == "AGRESS"){
        agress();
    }
}

//POST_COMMAND = “POST” SIDE COMMODITY AMOUNT PRICE
void post(void)
{
    output.push_back("POST");
    getToken();
    getToken();
    output.push_back(commodity());
    getToken();
    output.push_back(amount());
    getToken();
    output.push_back(price());
}

//REVOKE_COMMAND = “REVOKE” ORDER_ID
//CHECK_COMMAND = “CHECK” ORDER_ID
void revoke_check(void)
{
    output.push_back(token);
    getToken();   
    //amount is also an int, so for now this is fine
    output.push_back(amount()); 
}
//LIST_COMMAND = “LIST” [ COMMODITY [ DEALER_ID ] ]
void list(void)
{
    output.push_back("LIST");
    getToken();
    //optional 
    if (token.size() == 0) {
        return;
    }
    output.push_back(commodity());
    getToken();
    //optional 
    if (token.size() == 0) {
        return;
    }
    output.push_back(amount()); 
}
//AGGRESS_COMMAND = “AGGRESS” ( ORDER_ID AMOUNT )+
void agress(void)
{
    output.push_back("AGRESS");
    getToken();
    output.push_back(amount()); 
    getToken();
    output.push_back(amount()); 
    //optional extra
    while(true)
    {
        getToken();
        if (token.size() == 0) {
            return;
        }
        output.push_back(amount()); 
        getToken();
        output.push_back(amount()); 
    }
}

string side(void)
{
    if(token == "BUY" || token == "SELL")
        return token;
    error();
    return "";
}

string commodity(void)
{
    for(string comm : valid_commodity)
    {
        if(token == comm)
        {
            return token;
        }
    }
    error();
    return "";
}

string amount(void)
{
    try
    {
        int value = std::stoi(token);
        return token;
    }
    catch(std::exception& e)
    {
        error();
    }
    return "";
}

string price(void)
{
    try
    {
        double value = std::stod(token);
        return token;
    }
    catch(std::exception& e)
    {
        error();
    }
    return "";
}

void parse() { 
    getToken(); /* get the first token */
    try
    {
        raw(); /* call the parsing procedure for the start symbol */
    }catch(ParseException pe)
    {
        throw pe;
    }
}

bool isValid(std::string& myin, std::vector<std::string>& myout)
{
    input = myin;
    bool val = true;
    try
    {
        parse();
    }
    catch(...)
    {
        val = false;
    }
    myout = output;

    token = "";
    input = "";
    output.clear();

    return val;
}

int main()
{
    for (std::string line; std::getline(std::cin, line);) {
        std::vector<std::string> ot;
        bool a = isValid(line, ot);
        if(!a)
        {
            std::cout << "NOT ";
        }
        std::cout << "VALID: " << line << std::endl;
        //std::cout << a << std::endl;
        //for(string s : ot)
        //    std::cout << s << std::endl;
    }
}




