const size_t MAX_DATA_SIZE = 256; // Fixed size for simplicity

struct AppMessage {
  uint32_t port;
  char data[MAX_DATA_SIZE]; // Adjusted for string data

  // Serialize the struct to a buffer, considering data as part of the structure
  std::vector<char> serialize() const {
    std::vector<char> buffer(sizeof(port) + strlen(data) + 1);
    memcpy(buffer.data(), &port, sizeof(port));
    memcpy(buffer.data() + sizeof(port), data, strlen(data) + 1);
    return buffer;
  }

  static AppMessage deserialize(const std::vector<char> &buffer) {
    AppMessage msg;
    // Assuming the first byte of buffer is the port number.
    msg.port = static_cast<uint8_t>(buffer[0]); // Cast first byte to uint32_t
    if (buffer.size() > 1) { // Ensure there's data beyond the port number
      strncpy(msg.data, buffer.data() + 1,
              MAX_DATA_SIZE - 1); // Start copying after the port byte
    } else {
      msg.data[0] = '\0'; // No data, ensure null-termination
    }
    msg.data[MAX_DATA_SIZE - 1] = '\0'; // Ensure null-termination
    return msg;
  }
};