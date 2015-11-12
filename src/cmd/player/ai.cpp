#include <action/move.hpp>
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

Action* AI::MoveUp() const {
  return new Move('U');
}

Action* AI::MoveDown() const {
  return new Move('D');
}

Action* AI::MoveLeft() const {
  return new Move('L');
}

Action* AI::MoveRight() const {
  return new Move('R');
}

}
