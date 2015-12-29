#include <player/ai.hpp>
#include "master.hpp"

namespace mmpg {

AI* AI::main = 0;

int AI::Register(AI* ai) {
  AI::main = ai;

  return 0;
}

AI::AI() : me_(-1), game_(0), master_(0), action_(0) {

}

AI::~AI() {
  ClearAction();
}

void AI::Init(int player_id, const Game* game, Master* master) {
  me_ = player_id;
  game_ = game;
  master_ = master;
}

void AI::ClearAction() {
  if(action_ != 0) {
    delete action_;
    action_ = 0;
  }
}

int AI::me() const {
  return me_;
}

Action* AI::action() const {
  return action_;
}

void AI::load() {
  // Do nothing
}


void AI::save() {
  // Do nothing
}

}
