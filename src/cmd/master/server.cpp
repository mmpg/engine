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
    std::istringstream action(data);

    // Obtain player key
    std::string key;
    action >> key;

    if(worker.has_player_with_key(key)) {
      // Player exists
      debug::Println("SERVER", data);

      unsigned int player_id = worker.player_id(key);

      // Lock the world, so no one can read while updating it
      world.Lock();

      // Perform action
      world.Update(player_id, action);

      // TODO: Notify action in JSON
      notifier.Notify(std::to_string(player_id) + " " + data);

      // Unlock the world
      world.Unlock();

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
