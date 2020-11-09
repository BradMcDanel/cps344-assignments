#include <asio.hpp>
#include <iostream>
#include <fstream>
#include "../include/sender.hpp"

using asio::ip::tcp;

int main() {
  asio::io_context io_context;
  Sender sender(io_context, "127.0.0.1", "3000");

  int32_t curr_msg = 0;
  int32_t minMsg = 0;
  int32_t maxMsg = 0;

  std::ofstream file;
  file.open("C:\\Users\\juanh\\OneDrive\\Desktop\\Code\\networking\\cps373-assignments\\03-reliable\\data\\poem.txt");
  
  while(curr_msg < 853){
    minMsg = curr_msg;

    if(minMsg + 10 > 852){
      maxMsg = 853;
    }
    else{
      maxMsg = minMsg + 10;
    }

    for (int i = minMsg; i < maxMsg; i++) {
      sender.request_msg(i);
    }

    while (sender.data_ready()) {
      if (sender.data_ready()) {
        auto msg = sender.get_msg();

        if(msg.msg_id == curr_msg){
          auto data_str = std::string(msg.data.data(), CHUNK_SIZE);
          file << data_str;

          std::cout << "msg_id(" << msg.msg_id << ")::" << data_str << std::endl;

          curr_msg++;
        }
      }
    }
  }

  return 0;
}
