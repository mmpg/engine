#include "process.hpp"
#include "../utils.hpp"
#include "ai.hpp"
#include <sys/prctl.h>
#include <signal.h>
#include <sstream>
#include <thread>

namespace mmpg {
namespace player {

Process::Process(int argc, char* argv[]) {
  if(argc < 2) {
    throw "Player ID not provided";
  }

  id_ = argv[1];
  run_ = true;
}

void Process::Run(World& world) {
  // Kill when parent dies
  prctl(PR_SET_PDEATHSIG, SIGKILL);

  zmq::context_t zcontext(1);
  zmq::socket_t server(zcontext, ZMQ_REQ);

  server.connect("tcp://127.0.0.1:5557");

  AI* ai = AI::main;

  if(ai == 0) {
    throw "AI not registered";
  }

  // TODO: Set AI world
  (void)world;

  while(run_) {
    Action* action = ai->play();

    if(action == 0) {
      continue;
    }

    std::string msg = id_ + " " + action->str();
    server.send(msg.c_str(), msg.length());

    delete action;

    zmq::message_t reply;
    server.recv(&reply);

    std::string world_state = std::string((const char*)reply.data(), reply.size());
    std::istringstream world_stream(world_state);

    // TODO: Update AI world

    std::this_thread::sleep_for(std::chrono::milliseconds(33));
  }
}

}
}
