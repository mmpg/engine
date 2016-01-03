#pragma once

#include <zmq.hpp>
#include "game.hpp"
#include "../message_buffer.hpp"

namespace mmpg {

class Master {
 public:
  Master(const std::string& key_, zmq::context_t& context, const std::string& host, unsigned int port);

  void ReadWorldStructure(MessageBuffer& buffer);
  void WorldData(MessageBuffer& buffer);

  void Send(Action* action);

 private:
  std::string key_;
  zmq::socket_t socket_;

  void Request(char type, MessageBuffer& buffer);
};

}
