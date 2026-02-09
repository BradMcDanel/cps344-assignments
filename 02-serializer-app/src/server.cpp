#include <asio.hpp>
#include <array>
#include <cstdint>
#include <cstring>
#include <ctime>
#include <iostream>
#include <string>

#include "bakery.hpp"

using asio::ip::tcp;

int main() {
  asio::io_context io_context;
  tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 3000));

  // Use this bakery to handle queries from the client
  Bakery bakery = text_deserializer("../data/small.txt");

  while (true) {
    // Wait for client
    std::cout << "Blocked for read" << std::endl;
    tcp::socket socket(io_context);
    acceptor.accept(socket);

    std::array<uint8_t, 3> request{};
    asio::error_code error;
    asio::read(socket, asio::buffer(request), error); // Read exactly 3 bytes

    if (error) {
      std::cerr << "Read error: " << error.message() << std::endl;
      continue;
    }

    // TODO: Unpack request bits and handle logic (see assignment PDF).

    std::array<uint8_t, 2> response{};
    // TODO: Pack 16-bit response (see assignment PDF for byte order).

    asio::write(socket, asio::buffer(response), error); // Send exactly 2 bytes
  }

  return 0;
}
