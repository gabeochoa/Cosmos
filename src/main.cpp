#include <iostream>
#include <string>
#include "parser.h"

using namespace std;

int main(int argc, char** argv) {

    if(argc != 2)
    {
        return 1;
    }
    string type = argv[1];

    if(type != "base")
    {
        std::cout << "not supported" << std::endl;
        return 1;
    }

    std::vector<std::string> temp;
    for (std::string line; std::getline(std::cin, line);) {
        std::cout << line << std::endl;
        std::cout << isValid(line, temp) << std::endl;
    }
    return 0;
}