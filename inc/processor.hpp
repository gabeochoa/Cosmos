#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <string> 
#include <iostream>
#include <vector>
#include "database.hpp"

class Processor
{
    private:
        Processor(){};
        static Processor* _instance; 
    public:
        static Processor getInstance();
        std::string run(Database&, std::vector<std::string>);
};

#endif //PROCESSOR_H