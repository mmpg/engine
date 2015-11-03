#include "server.hpp"
#include <iostream>

namespace mmpg {
Server::Server(zmq::context_t &context, std::string port) : socket_(context, ZMQ_REP) {
  socket_.bind("tcp://*:" + port);

  std::cout << "[SERVER] Listening to 0.0.0.0:" << port << std::endl;
}

void Server::run() {
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
