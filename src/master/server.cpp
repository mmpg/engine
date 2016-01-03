#include <sstream>
#include "server.hpp"
#include "../debug.hpp"
#include "../utils.hpp"

namespace mmpg {

namespace {

std::string ReadStructure(const World& world) {
  std::ostringstream world_structure;
  world.PrintStructure(world_structure);

  return world_structure.str();
}

}

Server::Server(zmq::context_t& context, unsigned int port) : socket_(context, ZMQ_REP) {
  socket_.bind("tcp://*:" + std::to_string(port));

  debug::Println("SERVER", "Listening to 0.0.0.0:" + std::to_string(port) + "...");
}


void Server::Run(Worker& worker, Game& game, World& world, Notifier& notifier, Log& log) {
  std::string world_structure = ReadStructure(world);

  while(true) {
    zmq::message_t request;
    socket_.recv(&request);

    // Parse request
    std::string data(static_cast<char*>(request.data()), request.size());
    std::istringstream msg(data);

    // Obtain player key
    std::string key;
    msg >> key;

    if(!worker.has_player_with_key(key)) {
      socket_.send("400", 3);
      continue;
    }

    char type;
    msg >> type;

    if(type == 'S') {
      utils::Send(socket_, world_structure);
      continue;
    }

    if(type == 'W') {
      std::ostringstream world_data;
      world.PrintData(world_data);

      utils::Send(socket_, world_data.str());
      continue;
    }

    unsigned int player_id = worker.player_id(key);
    Action* action = game.ReadAction(type, msg);

    if(action == 0) {
      debug::Println("SERVER", "Invalid action received");
    } else {
      // Lock the world, so no one can touch it while updating it
      world.Lock();

      // Perform action
      action->Perform(player_id, world);

      // Notify action
      std::ostringstream action_json;
      action->PrintJSON(action_json);
      std::string notification = std::to_string(utils::time_ms()) + " ACTION " + std::to_string(player_id) + " " + action_json.str();

      notifier.Notify(notification);
      log.Add(notification);

      // Unlock the world
      world.Unlock();

      delete action;
    }

    socket_.send("OK", 2);
  }
}

}
