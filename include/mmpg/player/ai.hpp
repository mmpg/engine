#pragma once

#include "../game.hpp"
#include "../action.hpp"

namespace mmpg {

class Master;

class AI {
 public:
  static AI* main;
  static int Register(AI* ai);

  AI();
  virtual ~AI();

  void Init(int player_id, const Game* game, Master* master);
  void ClearAction();

  int me() const;
  Action* action() const;

  virtual void play() = 0;

  virtual void load();
  virtual void save();

 private:
  int me_;
  const Game* game_;
  Master* master_;
  Action* action_;
};

#define RegisterAI(x) static const int __x__ = mmpg::AI::Register(new x());

}
