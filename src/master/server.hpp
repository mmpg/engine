#pragma once

#include <zmq.hpp>
#include "game.hpp"
#include "worker.hpp"
#include "notifier.hpp"
#include "../log.hpp"

namespace mmpg {

class Server {
 public:
  Server(zmq::context_t& context, unsigned int port);

  void Run(Worker& worker, Game& game, World& world, Notifier& notifier, Log& log);

 private:
  zmq::socket_t socket_;
};

}