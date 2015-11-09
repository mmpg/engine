#include <zmq.hpp>
#include <sstream>
#include "worker.hpp"
#include "../../world.hpp"
#include "../../debug.hpp"


using namespace mmpg;

mmpg::Worker worker;
mmpg::World world;

int main() {
  // Start game world server
  zmq::context_t zcontext(1);

  zmq::socket_t server(zcontext, ZMQ_REP);
  server.bind("tcp://*:5557");

  worker.Run();

  debug::Println("MASTER", "Listening to 0.0.0.0:5577");

  while(true) {
    zmq::message_t request;
    server.recv(&request);

    // Parse request
    std::string data(static_cast<char*>(request.data()), request.size());
    std::istringstream action(data);

    // Obtain player id
    std::string id;
    action >> id;

    if(worker.has_player(id)) {
      // Player exists
      debug::Println("MASTER", "    " + data);

      // Perform action
      world.Update(id, action);

      // Reply with the current game world
      std::ostringstream world_serialized;
      world.Print(world_serialized);

      server.send(world_serialized.str().c_str(), world_serialized.str().length());
    } else {
      server.send("400", 3);
    }
  }

  return 0;
}
