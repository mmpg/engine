#pragma once

#include "../game.hpp"
#include "../action.hpp"

namespace mmpg {

class Master;

class AI {
 public:
  static AI* main;
  static int Register(AI* ai);

  virtual ~AI();

  void Init(int player_id, Game* game, Master* master);
  void RefreshWorld(World* world);

  void ChangeAction(Action* new_action);
  void ClearAction();

  int me() const;
  Action* action() const;

  virtual void Play() = 0;

 protected:
  virtual void world(World* world) = 0;

 private:
  int me_ = -1;
  Game* game_ = 0;
  Master* master_ = 0;
  Action* action_ = 0;
};

#define RegisterAI(x) static const int __x__ = mmpg::AI::Register(new x());

}
