#include <player/ai.hpp>
#include "master.hpp"
#include <sstream>

namespace mmpg {

AI* AI::main = 0;

int AI::Register(AI* ai) {
  AI::main = ai;

  return 0;
}

AI::~AI() {
  ClearAction();
}

void AI::Init(int player_id, Game* game, Master* master) {
  me_ = player_id;
  game_ = game;
  master_ = master;
}

void AI::ChangeAction(Action* new_action) {
  ClearAction();
  action_ = new_action;
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

void AI::RefreshWorld(World* world) {
  std::istringstream world_data(master_->WorldData());
  world->ReadData(world_data);
}

}
