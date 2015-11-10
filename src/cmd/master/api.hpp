#pragma once

#include <string>
#include <zmq.hpp>
#include "notifier.hpp"

namespace mmpg {

class Api {
 public:
  Api(zmq::context_t& context, unsigned int port);

  void Run();

 private:
  zmq::socket_t socket_;
};

}
