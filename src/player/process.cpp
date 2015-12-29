#include <sys/prctl.h>
#include <signal.h>
#include <sstream>
#include <thread>
#include "player/process.hpp"
#include "../utils.hpp"
#include "master.hpp"

namespace mmpg {
namespace player {

Process::Process(int argc, char* argv[]) {
  if(argc < 3) {
    // TODO: Usage help
    throw "Not enough arguments";
  }

  key_ = argv[1];
  id_ = atoi(argv[2]);
  run_ = true;
}

void Process::Run(const Game& game) {
  // Kill when parent dies
  prctl(PR_SET_PDEATHSIG, SIGKILL);

  AI* ai = AI::main;

  if(ai == 0) {
    throw "AI not registered";
  }

  zmq::context_t zcontext(1);

  // TODO: Master address should be retrieved from argv
  Master master(key_, zcontext, "127.0.0.1", 5557);

  ai->Init(id_, &game, &master);

  while(run_) {
    ai->play();

    Action* action = ai->action();

    if(action == 0) {
      continue;
    }

    master.Send(action);

    ai->ClearAction();

    std::this_thread::sleep_for(std::chrono::milliseconds(33));
  }
}

}
}
