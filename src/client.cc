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
        "dns,D", po::value<std::string>(), "DNS")(
        "ip", po::value<std::string>()->default_value(default_ip),
        "ip address")("port,p",
                      po::value<ushort>()->default_value(default_port),
                      "port number");
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
  asio::io_service ios;
  if (vm.count("dns")) {
    string dns = vm.at("dns").as<string>();
    asio::ip::tcp::resolver::query resolver_query(
        dns, std::to_string(port), asio::ip::tcp::resolver::numeric_service);
    asio::ip::tcp::resolver resolver(ios);
    asio::ip::tcp::resolver::iterator it = resolver.resolve(resolver_query, ec);
    if (ec.failed()) {
      // Failed to resolve the DNS name. Breaking execution.
      std::cout << "Failed to resolve a DNS name."
                << "Error code = " << ec.value()
                << ". Message = " << ec.message();
      return EXIT_FAILURE;
    }
    asio::ip::tcp::resolver::iterator it_end;
    for (; it != it_end; ++it) {
      // Here we can access the endpoint like this.
      asio::ip::tcp::endpoint ep = it->endpoint();
      std::cout << ep.address().to_string() << std::endl;
    }
  }
  asio::ip::address ip = asio::ip::address::from_string(ip_string, ec);
  if (ec.failed()) {
    std::cout << "Failed to parse the IP address. Error code = " << ec.value()
              << ". Message: " << ec.message();
    return EXIT_FAILURE;
  }

  asio::ip::tcp::endpoint endpoint(ip, port);
  asio::ip::tcp protocol = asio::ip::tcp::v4();
  asio::ip::tcp::socket socket(ios);
  socket.open(protocol, ec);

  if (ec.failed()) {
    std::cout << "Failed to open the socket! Error code = " << ec.value()
              << ". Message: " << ec.message();
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
