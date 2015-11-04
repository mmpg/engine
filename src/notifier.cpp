#include "notifier.hpp"

namespace mmpg {
Notifier::Notifier(zmq::context_t& context, std::string port) : socket_(context, ZMQ_PUB) {
  socket_.bind("tcp://*:" + port);

  std::cout << "[NOTIFIER] Notifying at 0.0.0.0:" << port << std::endl;
}


void Notifier::Notify(std::string message) {
  zmq::message_t notification(message.size());
  memcpy((void*) notification.data(), message.c_str(), message.size());

  socket_.send(notification);
}
}
