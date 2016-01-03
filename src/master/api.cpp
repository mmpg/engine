#include <sstream>
#include "api.hpp"
#include "../utils.hpp"
#include "../debug.hpp"
#include "../base64.hpp"

namespace mmpg {

namespace {

enum REQUESTS { FETCH_WORLD, FETCH_LOG, PLAYER_EXISTS, DEPLOY_PLAYER };

void InvalidAttribute(zmq::socket_t& response, std::string attr) {
  utils::Send(response, "ERROR|Invalid attribute value for: " + attr);
}

void UnknownRequest(zmq::socket_t& response) {
  utils::Send(response, "ERROR|Unknown request");
}

void FetchWorld(zmq::socket_t& response, const World& world, std::string& cache) {
  if(cache == "") {
    std::ostringstream world_structure;
    world.PrintViewerStructure(world_structure);

    cache = world_structure.str();
  }

  utils::Send(response, cache);
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
  bool ok = worker.Deploy(email, base64::Decode(player));

  utils::Send(response, ok ? "OK" : "ERROR");
}

}

Api::Api(zmq::context_t &context, unsigned int port) :
    socket_(context, ZMQ_REP),
    handlers_({
                  {"WORLD", FETCH_WORLD},
                  {"LOG", FETCH_LOG},
                  {"PLAYER_EXISTS", PLAYER_EXISTS},
                  {"DEPLOY_PLAYER", DEPLOY_PLAYER}
              })
{
  socket_.bind("tcp://*:" + std::to_string(port));

  debug::Println("API", "Listening to 0.0.0.0:" + std::to_string(port) + "...");
}

void Api::Run(Worker& worker, const World& world, const Log& world_log) {
  std::string cached_world = "";

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
        UnknownRequest(socket_);
        continue;
      }

      switch(code->second) {
        case FETCH_WORLD:
          FetchWorld(socket_, world, cached_world);
          break;

        case FETCH_LOG:
          FetchLog(request_stream, socket_, world_log);
          break;

        case PLAYER_EXISTS:
          PlayerExists(request_stream, socket_, worker);
          break;

        case DEPLOY_PLAYER:
          DeployPlayer(request_stream, socket_, worker);
          break;

        default:
          UnknownRequest(socket_);
      }
    }
  }
}

}
