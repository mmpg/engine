#include <zmq.hpp>
#include "../../utils.hpp"

using namespace mmpg;

int main(int argc, char* argv[]) {
  if(argc < 2) {
    return 1;
  }

  std::string key = argv[1];

  zmq::context_t zcontext(1);
  zmq::socket_t server(zcontext, ZMQ_REQ);

  server.connect("tcp://127.0.0.1:5557");

  server.send(key.c_str(), key.length());

  while(true);

  return 0;
}
