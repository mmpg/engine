#include <sstream>
#include "server.hpp"
#include "../../debug.hpp"

namespace mmpg {

Server::Server(zmq::context_t& context, unsigned int port) : socket_(context, ZMQ_REP) {
  socket_.bind("tcp://*:" + std::to_string(port));

  debug::Println("SERVER", "Listening to 0.0.0.0:" + std::to_string(port) + "...");
}


void Server::Run(Worker& worker, World& world, Notifier& notifier) {
  while(true) {
    zmq::message_t request;
    socket_.recv(&request);

    // Parse request
    std::string data(static_cast<char*>(request.data()), request.size());
    std::istringstream msg(data);

    // Obtain player key
    std::string key;
    msg >> key;

    if(worker.has_player_with_key(key)) {
      // Player exists
      unsigned int player_id = worker.player_id(key);
      Action* action = Action::Read(msg);

      if(action == 0) {
        debug::Println("SERVER", "Invalid action received");
      } else {
        // Lock the world, so no one can read while updating it
        world.Lock();

        // Perform action
        world.Update(player_id, *action);

        // Notify action
        std::ostringstream action_json;
        action->PrintJSON(action_json);
        notifier.Notify("ACTION " + std::to_string(player_id) + " " + action_json.str());

        // Unlock the world
        world.Unlock();

        delete action;
      }

      // Reply with the current game world
      std::ostringstream world_serialized;
      world.Print(world_serialized);

      socket_.send(world_serialized.str().c_str(), world_serialized.str().length());
    } else {
      socket_.send("400", 3);
    }
  }
}

}
