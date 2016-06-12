
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

enum { max_send_length = 255, max_recv_length = 1024 };

int main(int argc, char* argv[])
{
    try
    {
        if (argc != 3)
        {
        std::cerr << "Usage: client <host> <port>\n";
        return 1;
        }

        boost::asio::io_service io_service;

        tcp::socket s(io_service);
        tcp::resolver resolver(io_service);
        boost::asio::connect(s, resolver.resolve({argv[1], argv[2]}));
        
        for (std::string request; std::getline(std::cin, request);) 
        {
            if(request.size() > max_send_length)
            {
                continue;
            }
            boost::asio::write(s, boost::asio::buffer(request, request.size()));
            char reply[max_recv_length];
            size_t reply_length = boost::asio::read(s,
            boost::asio::buffer(reply, max_recv_length));
            std::cout.write(reply, reply_length);
            std::cout << "\n";
        }
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}


