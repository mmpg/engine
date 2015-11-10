#include <zmq.hpp>
#include <thread>
#include "../../utils.hpp"

using namespace mmpg;

int main(int argc, char* argv[]) {
  if(argc < 2) {
    return 1;
  }

  std::string id = argv[1];

  zmq::context_t zcontext(1);
  zmq::socket_t server(zcontext, ZMQ_REQ);

  server.connect("tcp://127.0.0.1:5557");

  std::string action = id + " U";

  server.send(action.c_str(), action.length());

  zmq::message_t world_status;
  server.recv(&world_status);

  while(true) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  return 0;
}
