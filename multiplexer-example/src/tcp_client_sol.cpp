#include <array>
#include <asio.hpp>
#include <iostream>
#include <limits>
#include <string>

using asio::ip::tcp;

const size_t MAX_STRING_SIZE = 256; // Maximum string message size

int main() {
  asio::io_context io_context;
  tcp::resolver resolver(io_context);
  auto endpoints = resolver.resolve("127.0.0.1", "3000");

  tcp::socket socket(io_context);
  asio::connect(socket, endpoints);

  asio::error_code error;

  std::cout << "Enter port number (1-3): ";
  unsigned int port_input; // Use an unsigned int to safely store user input
  std::cin >> port_input;
  uint8_t port = static_cast<uint8_t>(
      port_input); // Ensure the port is in the correct range and type

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                  '\n'); // Clear the input buffer
  std::cout << "Enter string message: ";
  std::string message;
  std::getline(std::cin, message);

  // Ensure message size is within limit, accounting for the port byte
  if (message.size() > MAX_STRING_SIZE - 1) {
    std::cerr << "Message too long, truncating." << std::endl;
    message = message.substr(0, MAX_STRING_SIZE - 1);
  }

  // Prepend port to message
  std::string full_message = std::string(1, static_cast<char>(port)) + message;

  // Send the combined message and port
  asio::write(socket, asio::buffer(full_message), error);
  if (error) {
    std::cerr << "Error sending message: " << error.message() << std::endl;
    return 1;
  }

  // Read and print the server's response
  std::array<char, MAX_STRING_SIZE> responseBuf;
  size_t len = socket.read_some(asio::buffer(responseBuf), error);
  if (error) {
    std::cerr << "Error reading response: " << error.message() << std::endl;
    return 1;
  }

  std::string response(responseBuf.data(), len);
  std::cout << "Server's response: " << response << std::endl;

  return 0;
}