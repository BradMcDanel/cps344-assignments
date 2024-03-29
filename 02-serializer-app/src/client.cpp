#include <asio.hpp>
#include <iostream>

using asio::ip::tcp;

int main() {
  asio::io_context io_context;
  tcp::resolver resolver(io_context);
  tcp::resolver::results_type endpoints = resolver.resolve("127.0.0.1", "3000");

  tcp::socket socket(io_context);
  asio::connect(socket, endpoints);

  asio::error_code error;

  // An example of sending a message to the server
  // Note: the server expects a 3-byte message (check the pdf for details on the protocol)
  std::array<uint8_t, 3> buf;
  buf.fill(0);
  buf[0] |= 1 << 7; // example of setting the most significant bit
  asio::write(socket, asio::buffer(buf), error);

  size_t len = socket.read_some(asio::buffer(buf), error);
  uint16_t response = *reinterpret_cast<uint16_t*>(&buf.data()[0]);
  std::cout << response << std::endl;

  return 0;
}