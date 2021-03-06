#pragma once

#include <string>
#include <zmq.hpp>
#include <map>
#include "../log.hpp"
#include "notifier.hpp"
#include "worker.hpp"
#include "world.hpp"

namespace mmpg {

class Api {
 public:
  Api(zmq::context_t& context, unsigned int port);

  void Run(Worker& worker, const World& world, const Log& log);

 private:
  zmq::socket_t socket_;
  std::map<std::string, int> handlers_;
};

}
