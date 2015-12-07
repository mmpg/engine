#pragma once

#include <zmq.hpp>
#include <world.hpp>
#include "worker.hpp"
#include "notifier.hpp"
#include "../log.hpp"

namespace mmpg {

class Server {
 public:
  Server(zmq::context_t& context, unsigned int port);

  void Run(Worker& worker, World& world, Notifier& notifier, Log& log);

 private:
  zmq::socket_t socket_;
};

}