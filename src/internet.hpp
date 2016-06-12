
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

int processSocket(int clientsock)
{
    std::string output ="";
    int n = 1;
    char buffer[256];
    if (clientsock < 0) 
    {
        std::cout << "ERROR on accept" << std::endl;
        return 1;
    }
    while(n)
    {
        bzero(buffer,256);
        n = recv(clientsock,buffer,255, 0);
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
        n = send(clientsock,output.c_str(), output.size(), 0);
        if (n < 0)
        {
            std::cout << "ERROR writing to socket" << std::endl;
            return 1;
        }
        output.clear();
    }
    return 0;
}

int runSocket1(int portno)
{
    int sockfd, newsockfd;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;
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
    listen(sockfd,1);
    clilen = sizeof(cli_addr);
    
    int cont = (newsockfd = accept(sockfd, 
             (struct sockaddr *) &cli_addr, 
             &clilen));
    close(sockfd);
    
    if (processSocket(newsockfd) < 0) 
    {
        std::cout << "ERROR processing" << std::endl;
        return 1;
    }

    close(newsockfd);
    return 0; 
}

int runSocket2(int portno)
{
    return 0;
}