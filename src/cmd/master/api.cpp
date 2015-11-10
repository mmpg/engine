#include "api.hpp"
#include "../../debug.hpp"
#include <iostream>

namespace mmpg {
Api::Api(zmq::context_t &context, unsigned int port) : socket_(context, ZMQ_REP) {
  socket_.bind("tcp://*:" + std::to_string(port));

  debug::Println("API", "Listening to 0.0.0.0:" + std::to_string(port) + "...");
}

void Api::Run() {
  while(true) {
    zmq::message_t request;

    // Wait for next request from client
    socket_.recv(&request);
    std::cout << "Received request" << std::endl;

    // Send reply back to client
    zmq::message_t reply(8);
    memcpy((void*) reply.data(), "It works", 8);
    socket_.send(reply);
  }
}
}
