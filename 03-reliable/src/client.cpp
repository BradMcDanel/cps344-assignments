#include <asio.hpp>
#include <iostream>
#include <fstream>
#include "../include/sender.hpp"

using asio::ip::tcp;

int main() {
  asio::io_context io_context;
  Sender sender(io_context, "127.0.0.1", "3000");

  // An explanation of the API
  // data_ready(): returns true if a message is available, otherwise false
  // get_msg(): gets an available message
  // request_msg(id): requests a message at id [0, NUM_MSGS)

  // You will need to make significant modifications to the logic below
  // As a starting point, run the server as follows:
  // ./server --no-delay --no-packet-drops which makes the below code work

  // As an example, you could start by requesting the first 10 messages
  int32_t curr_msg = 0;
  int32_t minMsg = 0;
  int32_t maxMsg = 10;
  std::string poemLines[852];

  std::ofstream file;
  file.open("poem.txt");

  while(maxMsg <= 852){
    for (int i = minMsg; i < maxMsg; i++) {
      sender.request_msg(i);
    }

    while (true) {
      if (sender.data_ready()) {
        // Get a response Msg:
        // A Msg has a msg_id (corresponds to id in request_msg) and
        // a char array of CHUNK_SIZE (128) storing the data
        auto msg = sender.get_msg();

        if(msg.msg_id == curr_msg){
          // Eventually, you will combine these chunks to write the file
          auto data_str = std::string(msg.data.data(), CHUNK_SIZE);
          file << data_str << std::endl;

          // Print the msg id and message recieved (may be out of order)
          std::cout << "msg_id(" << msg.msg_id << ")::" << data_str << std::endl;

          curr_msg++;
        }
      }
      else{
        minMsg = curr_msg;

        if(minMsg + 10 > 852){
          maxMsg = 852;
        }
        else{
          maxMsg += 10;
        }
      }
    }
  }

  return 0;
}
