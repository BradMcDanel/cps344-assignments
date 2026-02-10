#include <asio.hpp>
#include <ctime>
#include <inttypes.h>
#include <iostream>
#include <string>

using asio::ip::tcp;

int main() {
  asio::io_context io_context;
  tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 3000));
  asio::error_code error;
  std::array<uint32_t, 1> send;
  std::array<uint32_t, 1> recv;
  while (true) {
    tcp::socket socket(io_context);
    acceptor.accept(socket);
    for (;;) {
      size_t len = socket.read_some(asio::buffer(recv), error);
      if (error) {
        break;
      }
      send[0] = recv[0] + 1;
      socket.send(asio::buffer(send), 0, error);
      std::cout << "Received: " << +recv[0] << ", Sent: " << +send[0]
                << std::endl;
    }
    socket.close();
  }

  return 0;
}
