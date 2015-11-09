#include <zmq.hpp>
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

  std::string action = id + " MOVE_UP";

  server.send(action.c_str(), action.length());

  while(true);

  return 0;
}
