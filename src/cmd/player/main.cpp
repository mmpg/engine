#include <zmq.hpp>
#include <thread>
#include <sstream>
#include "../../utils.hpp"
#include "ai.hpp"

using namespace mmpg;

int main(int argc, char* argv[]) {
  if(argc < 2) {
    return 1;
  }

  std::string id = argv[1];

  zmq::context_t zcontext(1);
  zmq::socket_t server(zcontext, ZMQ_REQ);

  server.connect("tcp://127.0.0.1:5557");

  AI* ai = AI::main;

  if(ai == 0) {
    throw "AI not registered";
  }

  // TODO: Set AI world

  while(true) {
    Action* action = ai->play();

    if(action == 0) {
      continue;
    }

    std::string msg = id + " " + action->str();
    server.send(msg.c_str(), msg.length());

    delete action;

    zmq::message_t reply;
    server.recv(&reply);

    std::string world_state = std::string((const char*)reply.data(), reply.size());
    std::istringstream world_stream(world_state);

    // TODO: Update AI world

    std::this_thread::sleep_for(std::chrono::milliseconds(33));
  }

  return 0;
}
