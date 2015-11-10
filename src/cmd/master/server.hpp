#pragma once

#include <zmq.hpp>
#include "worker.hpp"
#include "../../world.hpp"
#include "notifier.hpp"

namespace mmpg {

class Server {
 public:
  Server(zmq::context_t& context, unsigned int port);

  void Run(Worker& worker, World& world, Notifier& notifier);

 private:
  zmq::socket_t socket_;
};

}