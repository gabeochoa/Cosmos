
//I dont really know anything about sockets
//I really dont know anything about sockets

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
    
    newsockfd = accept(sockfd, 
             (struct sockaddr *) &cli_addr, 
             &clilen);
    close(sockfd);
    
    if (processSocket(newsockfd) < 0) 
    {
        std::cout << "ERROR processing" << std::endl;
        return 1;
    }

    close(newsockfd);
    return 0; 
}

//-------

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <arpa/inet.h>

int make_socket (uint16_t port)
{
    int sock;
    struct sockaddr_in name;

    /* Create the socket. */
    sock = socket (PF_INET, SOCK_STREAM, 0);
    int a = 1;
    setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&a,sizeof(int));
    setsockopt(sock,SOL_SOCKET,SO_KEEPALIVE,&a,sizeof(int));
    if (sock < 0)
    {
        perror ("socket");
        exit (EXIT_FAILURE);
    }
    /* Give the socket a name. */
    name.sin_family = AF_INET;
    name.sin_port = htons (port);
    name.sin_addr.s_addr = htonl (INADDR_ANY);
    if (bind (sock, (struct sockaddr *) &name, sizeof (name)) < 0)
    {
        perror ("bind");
        exit (EXIT_FAILURE);
    }

    return sock;
}

#define MAXMSG  255
std::vector<int> clay;

int handle_client (int filedes)
{
    std::cout << "MESSAGE FROM " << filedes << std::endl;
    char buffer[MAXMSG];
    bzero(buffer,256);
    int nbytes = recv(filedes,buffer, MAXMSG, 0);
    if (nbytes < 0)
    {
        /* Read error. */
        perror ("read");
        exit (EXIT_FAILURE);
    }
    else if (nbytes == 0)
    {
        /* End-of-file. */
        auto iter = std::find(clay.begin(), clay.end(), filedes);
        if(iter != clay.end())
        {
            //std::cout << "ERASE" << std::endl;
            clay.erase(iter);
        }
        else
        {
            // for(int x : clay)
            //     std::cout << x << ". ";
            // std::cout << std::endl;
        }
        if(clay.empty())
            exit(0);
        //std::cout << clay.size() << std::endl;
        return -1;
    }
    else
    {
        /* Data read. */
        fprintf (stderr, "Server: got message: `%s'\n", buffer);
        std::string output = runCommand(buffer);
        int n = send(filedes,output.c_str(), output.size(), 0);
        if (n < 0)
        {
            std::cout << "ERROR writing to socket" << std::endl;
            return 1;
        }
        output.clear();
        return 0;
    }
}


int runSocket2(int portno)
{
    int sock;
    fd_set active_fd_set, read_fd_set;
    int i;
    struct sockaddr_in clientname;
    socklen_t size;

    /* Create the socket and set it up to accept connections. */
    sock = make_socket (portno);
    if (listen (sock, 1) < 0)
    {
        perror ("listen");
        exit (EXIT_FAILURE);
    }

    /* Initialize the set of active sockets. */
    FD_ZERO (&active_fd_set);
    FD_SET (sock, &active_fd_set);

    while (1)
    {
        /* Block until input arrives on one or more active sockets. */
        read_fd_set = active_fd_set;
        if (select (FD_SETSIZE, &read_fd_set, NULL, NULL, NULL) < 0)
        {
            perror ("select");
            exit (EXIT_FAILURE);
        }

        /* Service all the sockets with input pending. */
        for (i = 0; i < FD_SETSIZE; ++i)
        if (FD_ISSET (i, &read_fd_set))
        {
            if (i == sock)
            {
                /* Connection request on original socket. */
                int newconn;
                size = sizeof (clientname);
                newconn = accept (sock,
                (struct sockaddr *) &clientname,
                &size);
                if (newconn < 0)
                {
                    perror ("accept");
                    exit (EXIT_FAILURE);
                }
    
                FD_SET (newconn, &active_fd_set);
            }
            else
            {
                if(std::find(clay.begin(), clay.end(), i) == clay.end())
                    clay.push_back(i);
                /* Data arriving on an already-connected socket. */
                if (handle_client (i) < 0)
                {
                    close (i);
                    FD_CLR (i, &active_fd_set);
                }
            }
        }
    }
    return 0;
}




