#pragma once

#include <zmq.hpp>
#include "game.hpp"

namespace mmpg {

class Master {
 public:
  Master(const std::string& key_, zmq::context_t& context, const std::string& host, unsigned int port);

  std::string WorldData();
  void Send(Action* action);

 private:
  std::string key_;
  zmq::socket_t socket_;
};

}
