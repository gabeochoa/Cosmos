#include "parser.hpp"

Parser::Parser()
{
    input = "";
}

void Parser::error(void) { 
    errorstr = "INVALID_MESSAGE";
    throw new ParseException();
}

void Parser::getToken(void) { 
    /* tokens are words */
    size_t startpos = input.find_first_not_of(" \t\n\r");
    if( std::string::npos != startpos )
    {
            input = input.substr( startpos );
    }
    //cout << "GETTOKEN: input: "  << input << endl;
    startpos = input.find_first_of(" \t\n\r");
    if(std::string::npos != startpos )
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

void Parser::raw(void) { 
    inputmessage();
    getToken();
    if (token.size() == 0) {
        return;
    } else {
        //cout << "token " << token << endl;
        error();
    }
}

void Parser::inputmessage(void) { 
    output.push_back(dealerid());
    getToken();
    command();
}

std::string Parser::dealerid(void) { 
    std::string result;
    for(int i = 0; i < numdealers; i++) {
        if(token == valid_dealers[i])
            return token;
    }
    //std::cout << "ERROR: NO DEALER ID MATCH" << endl;
    error();
    return "";
}

void Parser::command(void)
{
    if(token == "POST")
    {
        post();
    }else if(token == "REVOKE" || token == "CHECK"){
        revoke_check();
    }else if(token == "LIST"){
        list();
    }else if(token == "AGGRESS"){
        aggress();
    }
}

//POST_COMMAND = “POST” SIDE COMMODITY AMOUNT PRICE
void Parser::post(void)
{
    output.push_back("POST");
    getToken();
    output.push_back(side());
    getToken();
    output.push_back(commodity());
    getToken();
    output.push_back(amount());
    getToken();
    output.push_back(price());
}

//REVOKE_COMMAND = “REVOKE” ORDER_ID
//CHECK_COMMAND = “CHECK” ORDER_ID
void Parser::revoke_check(void)
{
    output.push_back(token);
    getToken();   
    //amount is also an int, so for now this is fine
    output.push_back(amount()); 
}
//LIST_COMMAND = “LIST” [ COMMODITY [ DEALER_ID ] ]
void Parser::list(void)
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
    output.push_back(dealerid()); 
}
//AGGRESS_COMMAND = “AGGRESS” ( ORDER_ID AMOUNT )+
void Parser::aggress(void)
{
    output.push_back("AGGRESS");
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
        if (token.size() == 0) {
            error();
        }
        output.push_back(amount()); 
    }
}

std::string Parser::side(void)
{
    if(token == "BUY" || token == "SELL")
        return token;
    error();
    return "";
}

std::string Parser::commodity(void)
{
    
    for(int i = 0; i < numcommodities; i++) 
    {
        if(token == valid_commodity[i])
        {
            return token;
        }
    }
    error();
    return "";
}

std::string Parser::amount(void)
{
    if(isInteger(token))
        return token;
    error();
    return "";
}

std::string Parser::price(void)
{
    try
    {
        std::stod(token);
        return token;
    }
    catch(std::exception& e)
    {
        error();
    }
    return "";
}

void Parser::parse() { 
    getToken(); /* get the first token */
    try
    {
        raw(); /* call the parsing procedure for the start symbol */
    }catch(ParseException pe)
    {
        throw pe;
    }
}

bool Parser::isValid(std::string& err, std::string& myin, std::vector<std::string>& myout)
{
    errorstr.clear();
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
    err = errorstr;
    return val;
}


