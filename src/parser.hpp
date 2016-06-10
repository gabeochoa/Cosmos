#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

class ParseException: public std::runtime_error{
    public:
        ParseException():runtime_error("Parse Error"){}
        ParseException(std::string msg):runtime_error(msg.c_str()){}
};

std::string valid_dealers[] = {"DB","JPM","UBS","RBC","BARX","MS","CITI","BOFA","RBS","HSBC"};
std::string valid_commodity[] = {"GOLD", "SILV", "PORK", "OIL", "RICE"};

std::vector<std::string> output;
std::string input = "";
std::string token; 

/* declarations to allow arbitrary recursion */
void raw(void);
void post(void);
void list(void);
void agress(void);
void command(void);
void revoke_check(void);
void inputmessage(void);

std::string side(void);
std::string price(void);
std::string amount(void);
std::string dealerid(void);
std::string commodity(void);

//http://stackoverflow.com/questions/2844817/how-do-i-check-if-a-c-string-is-an-int
inline bool isInteger(const std::string & s)
{
   if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false ;

   char * p ;
   strtol(s.c_str(), &p, 10) ;

   return (*p == 0) ;
}


void error(void) { 
    printf("parse error\n");
    throw new ParseException();
}

void getToken(void) { 
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

std::string dealerid(void) { 
    std::string result;
    for(std::string vd : valid_dealers)
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
    output.push_back(dealerid()); 
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

std::string side(void)
{
    if(token == "BUY" || token == "SELL")
        return token;
    error();
    return "";
}

std::string commodity(void)
{
    for(std::string comm : valid_commodity)
    {
        if(token == comm)
        {
            return token;
        }
    }
    error();
    return "";
}

std::string amount(void)
{
    if(isInteger(token))
        return token;
    error();
    return "";
}

std::string price(void)
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

// int main()
// {
//     for (std::string line; std::getline(std::cin, line);) {
//         std::vector<std::string> ot;
//         bool a = isValid(line, ot);
//         if(!a)
//         {
//             std::cout << "NOT ";
//         }
//         std::cout << "VALID: " << line << std::endl;
//         //std::cout << a << std::endl;
//         //for(string s : ot)
//         //    std::cout << s << std::endl;
//     }
// }





