#pragma once

#include <string>
#include <zmq.hpp>
#include <map>
#include "log.hpp"
#include "notifier.hpp"
#include "worker.hpp"

namespace mmpg {

class Api {
 public:
  Api(zmq::context_t& context, unsigned int port);

  void Run(const Worker& worker, const Log& log);

 private:
  zmq::socket_t socket_;
  std::map<std::string, int> handlers_;
};

}
