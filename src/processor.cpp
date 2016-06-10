#include "processor.hpp"


void Processor::run(std::vector<std::string> strToProc)
{
    for(std::string s : strToProc)
    std::cout << s << std::endl;
}

