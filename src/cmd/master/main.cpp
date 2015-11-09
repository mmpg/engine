#include "../../debug.hpp"
#include "worker.hpp"
#include <zmq.hpp>

using namespace mmpg;

mmpg::Worker worker;

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

    std::string data = std::string(static_cast<char*>(request.data()), request.size());

    debug::Println("MASTER", "    Request received: " + data);
    server.send("reply", 5); // TODO: Send game world status
  }

  return 0;
}
