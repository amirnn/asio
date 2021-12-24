#include <iostream>
#include <string>

// #define ASIO_STANDALONE
#include <boost/asio.hpp>
#include <boost/asio/ts/buffer.hpp>
#include <boost/asio/ts/internet.hpp>

#include <boost/json.hpp>

using namespace boost;

// ip address of example.com 93.184.216.34
std::string ipAddressString = "93.184.216.34";
unsigned short port = 80;

int main(int , char const **)
{
    boost::system::error_code ec;
    asio::ip::address ip = asio::ip::address::from_string(ipAddressString, ec);
    if (ec.value() != 0)
    {
        std::cout 
            << "Failed to parse the IP address. Error code = "
            << ec.value() << ". Message: " << ec.message();
        return ec.value();
    }
    
    asio::ip::tcp::endpoint endpoint(ip, port);
    


    return EXIT_SUCCESS;
}
