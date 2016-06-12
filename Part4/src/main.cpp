#include <iostream>
#include <string>
#include "parser.hpp"
#include "processor.hpp"
#include "database.hpp"

//TCP Headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdlib>
#include <cstring>
#include <unistd.h>


std::string runCommand(std::string command);
int base();
int runSocket1(int portno);
int runSocket2(int portno);

std::vector<std::string> temp;
Database database;

int main(int argc, char** argv) 
{
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
            exit(1);
        }
        while(true)
        {
           runSocket1(atoi(argv[2]));
        }
    }
    else if(type == "ext2")
    {
        if (argc < 3) 
        {
            fprintf(stderr,"ERROR, no port provided\n");
            exit(1);
        }
        runSocket2(atoi(argv[2]));
    }
}

int runSocket1(int portno)
{
    int sockfd, newsockfd;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n = 1;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int a = 1;
    setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&a,sizeof(int));
    setsockopt(sockfd,SOL_SOCKET,SO_KEEPALIVE,&a,sizeof(int));
    if (sockfd < 0)
    {
        std::cout << "ERROR opening socket" << std::endl;
        return 1;
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    int err = bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
    if (err < 0) 
    {
        std::cout << "ERROR on binding" << std::endl;
        return 1;
    }
    std::string output ="";
    listen(sockfd,1);
    clilen = sizeof(cli_addr);
    
    int cont = (newsockfd = accept(sockfd, 
             (struct sockaddr *) &cli_addr, 
             &clilen));
    close(sockfd);
    while (cont >= 0)
    {
        if (newsockfd < 0) 
        {
            std::cout << "ERROR on accept" << std::endl;
            return 1;
        }
        while(n)
        {
            bzero(buffer,256);
            n = recv(newsockfd,buffer,255, 0);
            if(n == 0)
                continue;
            if (n < 0)
            {
                std::cout << "after recv" << std::endl;
                std::cout << "ERROR reading from socket" << std::endl;
                return 1;
            }
            //printf("Here is the message:\n %s\n",buffer);
            output = runCommand(buffer);
            n = send(newsockfd,output.c_str(), output.size(), 0);
            if (n < 0)
            {
                std::cout << "ERROR writing to socket" << std::endl;
                return 1;
            }
            output.clear();
        }
        close(newsockfd);
        cont = (newsockfd = accept(sockfd, 
             (struct sockaddr *) &cli_addr, &clilen));
    }
    return 0; 
}


int runSocket2(int portno)
{
    return 0;
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
    if(isValid(output, command, temp))
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




