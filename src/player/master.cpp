#include "master.hpp"

namespace mmpg {


Master::Master(const std::string& key, zmq::context_t& context, const std::string& host, unsigned int port) :
    key_(key), socket_(context, ZMQ_REQ) {
  socket_.connect("tcp://" + host + ":" + std::to_string(port));
}


void Master::Send(Action* action) {
  std::string msg = key_ + " " + action->str();
  socket_.send(msg.c_str(), msg.length());

  // Throw reply away
  zmq::message_t reply;
  socket_.recv(&reply);
}

void Master::ReadWorldStructure(MessageBuffer& buffer) {
  Request('S', buffer);
}

void Master::WorldData(MessageBuffer& buffer) {
  Request('W', buffer);
}

void Master::Request(char type, MessageBuffer& buffer) {
  std::string msg = key_ + " " + type;
  socket_.send(msg.c_str(), msg.length());

  socket_.recv(&buffer.message);
  buffer.Ready();
}

}
