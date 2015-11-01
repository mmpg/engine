#include <iostream>
#include <zmq.hpp>

int main ()  {
  // Prepare our context and socket
  zmq::context_t context(1);
  zmq::socket_t socket(context, ZMQ_REP);
  socket.bind("tcp://*:5555");

  std::cout << "Listening to 0.0.0.0:5555" << std::endl;

  while(true) {
    zmq::message_t request;

    // Wait for next request from client
    socket.recv(&request);
    std::cout << "Received request" << std::endl;

    // Send reply back to client
    zmq::message_t reply(8);
    memcpy((void*) reply.data(), "It works", 8);
    socket.send(reply);
  }

  return 0;
}
