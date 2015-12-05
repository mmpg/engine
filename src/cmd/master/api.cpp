#include <sstream>
#include "api.hpp"
#include "../../utils.hpp"
#include "../../debug.hpp"

namespace mmpg {

namespace {

const int CODE_FETCH_LOG = 0;
const int CODE_PLAYER_EXISTS = 1;
const int CODE_DEPLOY_PLAYER = 2;

void InvalidAttribute(zmq::socket_t& response, std::string attr) {
  utils::Send(response, "ERROR|Invalid attribute value for: " + attr);
}

void UnknownRequest(std::istream& request, zmq::socket_t& response) {
  (void) request;
  utils::Send(response, "ERROR|Unknown request");
}

void FetchLog(std::istream& request, zmq::socket_t& response, const Log& world_log) {
  unsigned int time;

  if(!(request >> time)) {
    InvalidAttribute(response, "time");
    return;
  }

  utils::Send(response, world_log.Read(time));
}

void PlayerExists(std::istream& request, zmq::socket_t& response, const Worker& worker) {
  std::string email;

  if(!(request >> email)) {
    InvalidAttribute(response, "email");
    return;
  }

  utils::Send(response, worker.has_player_with_email(email) ? "TRUE" : "FALSE");
}

void DeployPlayer(std::istream& request, zmq::socket_t& response, Worker& worker) {
  std::string email;

  if(!(request >> email) or !worker.has_player_with_email(email)) {
    InvalidAttribute(response, "email");
    return;
  }

  std::string player;

  if(!(request >> player)) {
    InvalidAttribute(response, "player");
    return;
  }

  // TODO: Get compilation error info
  bool ok = worker.Deploy(email, utils::Base64Decode(player));

  utils::Send(response, ok ? "OK" : "ERROR");
}

}

Api::Api(zmq::context_t &context, unsigned int port) :
    socket_(context, ZMQ_REP),
    handlers_({
                  {"LOG", CODE_FETCH_LOG},
                  {"PLAYER_EXISTS", CODE_PLAYER_EXISTS},
                  {"DEPLOY_PLAYER", CODE_DEPLOY_PLAYER}
              })
{
  socket_.bind("tcp://*:" + std::to_string(port));

  debug::Println("API", "Listening to 0.0.0.0:" + std::to_string(port) + "...");
}

void Api::Run(Worker& worker, const Log& world_log) {
  while(true) {
    zmq::message_t request;
    socket_.recv(&request);

    std::string request_body((char*)request.data(), request.size());

    std::istringstream request_stream(request_body);
    std::string type;

    if(request_stream >> type) {
      debug::Println("API", "Received request: " + type);

      auto code = handlers_.find(type);

      if(code == handlers_.end()) {
        UnknownRequest(request_stream, socket_);
        continue;
      }

      switch(code->second) {
        case CODE_FETCH_LOG:
          FetchLog(request_stream, socket_, world_log);
          break;

        case CODE_PLAYER_EXISTS:
          PlayerExists(request_stream, socket_, worker);
          break;

        case CODE_DEPLOY_PLAYER:
          DeployPlayer(request_stream, socket_, worker);
          break;

        default:
          UnknownRequest(request_stream, socket_);
      }
    }
  }
}

}
