#include <iostream>
#include <string>
#include "parser.hpp"
#include "processor.hpp"
#include "database.hpp"

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
    Processor proc;
    Database database;
    for (std::string line; std::getline(std::cin, line);) {
        std::cout << line << std::endl;
        if(isValid(line, temp))
            proc.run(database, temp);
        database.print();
    }
    return 0;
}