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

std::string Master::WorldData() {
  std::string msg = key_ + " W";
  socket_.send(msg.c_str(), msg.length());

  zmq::message_t reply;
  socket_.recv(&reply);

  return std::string((const char*)reply.data(), reply.size());
}

}
