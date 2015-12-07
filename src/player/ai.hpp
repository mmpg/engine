#pragma once

#include "action.hpp"

namespace mmpg {

class AI {
 public:
  static AI* main;
  static int Register(AI* ai);

  virtual Action* play() = 0;

  virtual void load();
  virtual void save();
};

#define RegisterAI(x) static const int __x__ = mmpg::AI::Register(new x());

}
