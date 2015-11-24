#pragma once

#include <string>
#include <zmq.hpp>
#include <map>
#include "log.hpp"
#include "notifier.hpp"

namespace mmpg {

class Api {
 public:
  Api(zmq::context_t& context, unsigned int port);

  void Run(const Log& log);

 private:
  typedef void (*RequestHandler)(std::istream&, zmq::socket_t&, const Log&);

  zmq::socket_t socket_;
  std::map<std::string, RequestHandler> handlers_;
};

}
