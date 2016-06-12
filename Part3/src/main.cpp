#include <iostream>
#include <string>
#include "parser.hpp"
#include "processor.hpp"
#include "database.hpp"

//TCP Headers
#include <cstdlib>
#include <deque>
#include <iostream>
#include <list>
#include <memory>
#include <set>
#include <utility>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

std::string runCommand(std::string command);
int base();
int runSocket1(int portno);
int runSocket2(int portno);

std::vector<std::string> temp;
Database database;


std::string make_string(boost::asio::streambuf& streambuf)
{
 return {buffers_begin(streambuf.data()), 
         buffers_end(streambuf.data())};
}
class session
  : public std::enable_shared_from_this<session>
{
    public:
        session(tcp::socket socket)
        : socket_(std::move(socket))
        {
        }

        void start()
        {
            do_read();
        }

    private:
        void do_read()
        {
            auto self(shared_from_this());
            socket_.async_read_some(boost::asio::buffer(data_, max_length),
            [this, self](boost::system::error_code ec, std::size_t length)
            {
                if (!ec)
                {
                    do_write();
                }
            });
        }

        void do_write()
        {
            std::string ret = runCommand(data_);
            std::cout << ret << std::endl;

            auto self(shared_from_this());
            boost::asio::async_write(socket_, boost::asio::buffer(ret.c_str(), ret.size()),
            [this, self](boost::system::error_code ec, std::size_t)
            {
                if (!ec)
                {
                    do_read();
                }
            });
        }

    tcp::socket socket_;
    enum { max_length = 255 };
    char data_[max_length];
};

class server
{
    public:
        server(boost::asio::io_service& io_service, short port)
        : acceptor_(io_service, tcp::endpoint(tcp::v4(), port)),
        socket_(io_service)
        {
            do_accept();
        }

    private:
        void do_accept()
        {
            acceptor_.async_accept(socket_,
            [this](boost::system::error_code ec)
            {
                if (!ec)
                {
                    std::make_shared<session>(std::move(socket_))->start();
                }
                do_accept();
            });
        }

    tcp::acceptor acceptor_;
    tcp::socket socket_;
};


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
        runSocket1(atoi(argv[2]));
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
{/*
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
    */
    return 0; 
}


int runSocket2(int portno)
{
    try
    {
        boost::asio::io_service io_service;
        server s(io_service, portno);
        io_service.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
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
    std::cout << "RUN COMMAND:" << command << std::endl;
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




