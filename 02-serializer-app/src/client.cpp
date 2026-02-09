#include <asio.hpp>
#include <array>
#include <cstdint>
#include <iostream>

using asio::ip::tcp;

int main() {
  asio::io_context io_context;
  tcp::resolver resolver(io_context);
  tcp::resolver::results_type endpoints = resolver.resolve("127.0.0.1", "3000");

  tcp::socket socket(io_context);
  asio::connect(socket, endpoints);

  asio::error_code error;

  // Note: the server expects a 3-byte message (check the pdf for details on the protocol)
  std::array<uint8_t, 3> request{};
  // TODO: Pack request bytes (see assignment PDF for the protocol).
  asio::write(socket, asio::buffer(request), error);

  std::array<uint8_t, 2> response_bytes{};
  asio::read(socket, asio::buffer(response_bytes), error); // Read exactly 2 bytes
  if (error) {
    std::cerr << "Read error: " << error.message() << std::endl;
    return 1;
  }

  // TODO: Convert response bytes to uint16_t (see assignment PDF for byte order).
  uint16_t response = 0;
  std::cout << response << std::endl;

  return 0;
}
