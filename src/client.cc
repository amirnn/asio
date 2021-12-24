#include <iostream>
#include <string>
using std::string;
#include <boost/asio.hpp>
#include <boost/asio/ts/buffer.hpp>
#include <boost/asio/ts/internet.hpp>
#include <boost/json.hpp>
#include <boost/program_options.hpp>

using namespace boost;
namespace po = boost::program_options;

// ip address of example.com 93.184.216.34
string default_ip = "93.184.216.34";
ushort default_port = 80;

int main(int ac, char const** av) {
  po::options_description desc("Allowed options");
  {
    desc.add_options()("help", "produce help message")(
        "ip", po::value<std::string>()->default_value(default_ip), "ip address")(
        "port", po::value<ushort>()->default_value(default_port), "port number");
  }

  po::variables_map vm;
  po::store(po::parse_command_line(ac, av, desc), vm);
  po::notify(vm);

  if (vm.count("help")) {
            std::cout << desc << "\n";
            return 0;
        }

  ushort port = vm.at("port").as<ushort>();
  string ip_string = vm.at("ip").as<string>();

  boost::system::error_code ec;
  asio::ip::address ip = asio::ip::address::from_string(ip_string, ec);
  if (ec.value() != 0) {
    std::cout << "Failed to parse the IP address. Error code = " << ec.value()
              << ". Message: " << ec.message();
    return ec.value();
  }

  asio::ip::tcp::endpoint endpoint(ip, port);

  return EXIT_SUCCESS;
}
