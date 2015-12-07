#include "ai.hpp"

namespace mmpg {

AI* AI::main = 0;

int AI::Register(AI* ai) {
  AI::main = ai;

  return 0;
}

void AI::load() {
  // Do nothing
}


void AI::save() {
  // Do nothing
}

}
