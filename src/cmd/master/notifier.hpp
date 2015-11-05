#pragma once

#include <iostream>
#include <string>
#include <zmq.hpp>

namespace mmpg {

class Notifier {
 public:
  Notifier(zmq::context_t& context, std::string port);

  void Notify(std::string message);

 private:
  zmq::socket_t socket_;
};

}
