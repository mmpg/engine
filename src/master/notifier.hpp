#pragma once

#include <string>
#include <zmq.hpp>

namespace mmpg {

class Notifier {
 public:
  Notifier(zmq::context_t& context, unsigned int port);

  void Notify(std::string message);

 private:
  zmq::socket_t socket_;
};

}
