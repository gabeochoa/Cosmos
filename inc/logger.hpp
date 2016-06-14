#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <sstream>

class Logger : public std::ostream 
{
    private:
        class LogBuf : public std::stringbuf 
        {
            private:
                std::string m_marker;
            public:
                LogBuf(const std::string& marker) : m_marker(marker) { }
                ~LogBuf() {  pubsync(); }
                int sync() 
                {
                    //std::cout << m_marker << str();
                    //str("");
                    return 0;//return std::cout?0:-1;
                }
        };
    public:
        Logger() : 
            std::ostream(new LogBuf("")) 
        {}
        Logger(const std::string& marker) : 
            std::ostream(new LogBuf(marker)) 
        {}
        ~Logger() { delete rdbuf(); }
        std::string str()
        {
            std::stringstream ss;
            ss << rdbuf();
            return ss.str();
        }
};

#endif //LOGGER_H
