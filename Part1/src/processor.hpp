#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <string> 
#include <iostream>
#include <vector>
#include "database.hpp"

class Processor 
{
    //private:
    public:
        Processor();
        void run(Database&, std::vector<std::string>);
};

#endif //PROCESSOR_H