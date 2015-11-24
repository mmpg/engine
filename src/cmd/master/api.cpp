#include <sstream>
#include "api.hpp"
#include "../../utils.hpp"
#include "../../debug.hpp"

namespace mmpg {

namespace {

void BadAttribute(std::string attr, zmq::socket_t& response) {
  utils::Send(response, "ERROR|Bad attribute value for: " + attr);
}

void FetchLog(std::istream& request, zmq::socket_t& response, const Log& world_log) {
  long unsigned int time;

  if(!(request >> time)) {
    BadAttribute("time", response);
    return;
  }

  utils::Send(response, "TODO: Fetch and send log");
}

void UnknownRequest(std::istream& request, zmq::socket_t& response, const Log& world_log) {
  utils::Send(response, "ERROR|Unknown request");
}

}

Api::Api(zmq::context_t &context, unsigned int port) :
    socket_(context, ZMQ_REP),
    handlers_({
                  {"LOG", FetchLog}
              })
{
  socket_.bind("tcp://*:" + std::to_string(port));

  debug::Println("API", "Listening to 0.0.0.0:" + std::to_string(port) + "...");
}

void Api::Run(const Log& world_log) {
  while(true) {
    zmq::message_t request;
    socket_.recv(&request);

    std::string request_body((char*)request.data(), request.size());

    std::istringstream request_stream(request_body);
    std::string type;

    if(request_stream >> type) {
      debug::Println("API", "Received request: " + type);

      if(handlers_.find(type) != handlers_.end()) {
        handlers_[type](request_stream, socket_, world_log);
        continue;
      }
    }

    UnknownRequest(request_stream, socket_, world_log);
  }
}

}
