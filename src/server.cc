#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/json.hpp>

using namespace boost;


ushort port = 2500;


int main(int, char const **)
{
    asio::ip::address ip = asio::ip::address_v4::any();
    asio::ip::tcp::endpoint endpoint(ip,port);
    return 0;
}
