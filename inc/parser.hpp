#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "grammar.hpp"

class ParseException : public std::runtime_error
{
    public:
        ParseException():runtime_error("INVALID_MESSAGE"){}
        ParseException(std::string msg):runtime_error(msg.c_str()){}
};

class Parser
{
    private:

        std::vector<std::string> output;
        std::string input;
        std::string token; 
        std::string errorstr; 

        void raw(void);
        void post(void);
        void list(void);
        void error(void);
        void parse(void);
        void aggress(void);
        void command(void);
        void getToken(void);
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
    public:
        Parser();
        bool isValid(std::string&, std::string&, std::vector<std::string>&);
};

#endif //PARSER_H


