#include "notifier.hpp"
#include "../debug.hpp"

namespace mmpg {
Notifier::Notifier(zmq::context_t& context, unsigned int port) : socket_(context, ZMQ_PUB) {
  socket_.bind("tcp://*:" + std::to_string(port));

  debug::Println("NOTIFIER", "Publishing to 0.0.0.0:" + std::to_string(port) + "...");
}


void Notifier::Notify(std::string message) {
  zmq::message_t notification(message.size());
  memcpy((void*) notification.data(), message.c_str(), message.size());

  socket_.send(notification);
}
}
