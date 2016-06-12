#include <iostream>
#include <string>
#include "parser.hpp"
#include "processor.hpp"
#include "database.hpp"

/*
    Run command:
    - validates the raw command and splits by space
    - calls processor with valid command
*/
std::string runCommand(std::string command);
/*
    base:
    - reads from local cin
    - passes command to 'runCommand'
*/
int base();
/*
    runSocket1:
    - Handles Ext1
    - opens tcp port and waits for input
    - passes input as command to 'runCommand'
    - passes output back to client
*/
int runSocket1(int portno);
/*
    runSocket2:
    -*not implemented*
*/
int runSocket2(int portno);

//Just moved the code
#include "internet.hpp"

std::vector<std::string> temp;
Database database;
Parser parser;

char usagestring[] = "Usage: ./cms base | ./cms ext1 [port] | ./cms ext1 [port]";

int main(int argc, char** argv) 
{
    if (argc < 2)
    {
        fprintf(stderr,"%s\n", usagestring);
        return 1;
    } 

    std::string type = argv[1];

    if(type == "base")
    {
        base();
    }
    else if(type == "ext1")
    {
        if (argc < 3) 
        {
            fprintf(stderr,"ERROR, no port provided\n");
            fprintf(stderr,"%s\n", usagestring);
            exit(1);
        }
        runSocket1(atoi(argv[2]));
    }
    else if(type == "ext2")
    {
        return 2;
        // if (argc < 3) 
        // {
        //     fprintf(stderr,"ERROR, no port provided\n");
        //     fprintf(stderr,"%s\n", usagestring);
        //     exit(1);
        // }
        // runSocket2(atoi(argv[2]));
    }
}

int base()
{
    for (std::string line; std::getline(std::cin, line);) 
    {
        std::cout << runCommand(line);
    }
    return 0;
}

std::string runCommand(std::string command)
{
    Processor proc = Processor::getInstance();
    std::cout << command << std::endl;
    std::string output;
    if(parser.isValid(output, command, temp))
    {
       output = proc.run(database, temp);
    }
    else
    {
        //keep output the same
        output += "\n";
    }
    database.clearLog();
    temp.clear();
    return output;
}



