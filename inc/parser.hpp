#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <cstdlib>
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

        //http://stackoverflow.com/questions/447206/c-isfloat-function
        template <class type> 
        bool istype(std::string myString ) {
            std::istringstream iss(myString);
            type f;
            iss >> std::noskipws >> f; 
            // Check the entire string was consumed and if either failbit or badbit is set
            return iss.eof() && !iss.fail(); 
        }

    public:
        Parser();
        bool isValid(std::string&, std::string&, std::vector<std::string>&);
};

#endif //PARSER_H


