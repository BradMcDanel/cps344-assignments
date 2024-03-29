#include <inttypes.h>
#include <asio.hpp>
#include <fstream>
#include <iostream>
#include <queue>
#include <random>
#include <streambuf>
#include <string>
#include <thread>
#include <mutex>
#include <chrono>
#include <iomanip>
#include <sstream>
#include "../include/sender.hpp"

using asio::ip::tcp;
namespace sc = std::chrono;

std::random_device rd{};
std::mt19937 gen{rd()};

bool no_packet_drops = false;
bool no_delay = false;

std::vector<std::string> load_data(std::string filepath) {
  std::ifstream t(filepath);
  std::string text((std::istreambuf_iterator<char>(t)),
                   std::istreambuf_iterator<char>());
  std::vector<std::string> msgs;
  for (unsigned i = 0; i < text.length(); i += CHUNK_SIZE) {
    auto s = text.substr(i, CHUNK_SIZE);
    s.resize(CHUNK_SIZE, '\0');
    msgs.push_back(s);
  }
  return msgs;
}

std::string get_timestamp() {
  auto now = sc::system_clock::now();
  auto ms = sc::duration_cast<sc::milliseconds>(now.time_since_epoch()) % 1000;
  auto timer = sc::system_clock::to_time_t(now);
  std::tm bt = *std::localtime(&timer);
  std::ostringstream oss;
  oss << std::put_time(&bt, "%H:%M:%S");
  oss << '.' << std::setfill('0') << std::setw(3) << ms.count();
  return oss.str();
}

void handle_request(tcp::acceptor& acceptor,
                    const std::vector<std::string>& msgs) {
  acceptor.async_accept([&](std::error_code ec, tcp::socket&& socket) {
    std::bernoulli_distribution loss_dist(0.1);
    std::normal_distribution<> delay_dist{250, 150};
    std::vector<std::thread> threads;
    std::vector<std::pair<sc::milliseconds, uint16_t>> delays;
    auto start_time = sc::duration_cast<sc::milliseconds>(
        sc::high_resolution_clock::now().time_since_epoch());
    auto t = std::chrono::milliseconds(10);
    auto hb = sc::duration_cast<sc::milliseconds>(
        sc::high_resolution_clock::now().time_since_epoch());
    hb += sc::seconds(5);

    while (true) {
      auto curr_time = sc::duration_cast<sc::milliseconds>(
          sc::high_resolution_clock::now().time_since_epoch());
      if (hb < curr_time) {
        goto exit_loop;
      }

      // process previous delayed messages
      for (auto& delay : delays) {
        // timer expired - send message
        if (delay.first < curr_time) {
          asio::error_code error;
          std::array<char, CHUNK_SIZE + 2> data;
          std::memcpy(&data[0], &delay.second, sizeof(uint16_t));
          if (delay.second < msgs.size()) {
            std::memcpy(&data[2], msgs[delay.second].data(), CHUNK_SIZE);
            asio::write(socket, asio::buffer(data), error);
            if (error == asio::error::eof) {
              goto exit_loop;
            }
            std::cout << "[" << get_timestamp() << "] Sent response for message ID:\t" << delay.second << std::endl;
          } else {
            std::cout << "[" << get_timestamp() << "] Skipped sending response for invalid message ID:\t" << delay.second << std::endl;
          }
        }
      }

      delays.erase(std::remove_if(delays.begin(), delays.end(),
                                  [&](std::pair<sc::milliseconds, uint16_t> delay) {
                                    return delay.first < curr_time;
                                  }),
                   delays.end());

      // no new messages.. sleep a bit and try again
      if (!socket.available()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        continue;
      }

      std::array<uint16_t, 1> msg_id_buf;
      asio::error_code error;
      size_t len = socket.read_some(asio::buffer(msg_id_buf), error);
      if (error == asio::error::eof) {
        goto exit_loop;
      }

      // Validate the received message ID
      if (msg_id_buf[0] >= NUM_MSGS) {
        std::cout << "[" << get_timestamp() << "] Dropped request with invalid message ID:\t" << msg_id_buf[0] << std::endl;
        continue;
      }

      std::cout << "[" << get_timestamp() << "] Received request for message ID:\t" << msg_id_buf[0] << std::endl;

      // packet dropped
      auto dropped = loss_dist(gen);
      if (!no_packet_drops && dropped) {
        std::cout << "[" << get_timestamp() << "] Dropped request for message ID:\t" << msg_id_buf[0] << std::endl;
        continue;
      }

      // drop if already processing NUM_CHUNKS (10 requests)
      if (delays.size() >= NUM_CHUNKS) {
        std::cout << "[" << get_timestamp() << "] Dropped request due to maximum concurrent requests limit" << std::endl;
        continue;
      }

      // not dropped - add random delay
      int delay = no_delay ? 0 : std::max(delay_dist(gen), 0.0);
      auto delay_ms = curr_time + std::chrono::milliseconds(delay);
      delays.push_back(std::make_pair(delay_ms, msg_id_buf[0]));

      // recv'd data - update the hb
      hb = sc::duration_cast<sc::milliseconds>(
               sc::high_resolution_clock::now().time_since_epoch()) +
           sc::seconds(5);
    }

  exit_loop:
    handle_request(acceptor, msgs);
  });
}

int main(int argc, char* argv[]) {
  asio::io_context io_context;
  tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 3000));
  auto msgs = load_data("../data/gilgamesh.txt");

  for (int i = 1; i < argc; i++) {
    if (std::string(argv[i]) == std::string("--no-packet-drops")) {
      no_packet_drops = true;
    } else if (std::string(argv[i]) == std::string("--no-delay")) {
      no_delay = true;
    } else {
      std::cout << "Invalid option: " << argv[i] << std::endl;
      std::cout << "Options are: " << std::endl;
      std::cout << "  --no-packet-drops" << std::endl
                << "  --no-delay" << std::endl;
    }
  }

  handle_request(acceptor, msgs);
  io_context.run();

  return 0;
}
