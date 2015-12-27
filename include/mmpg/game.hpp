#pragma once

#include "world.hpp"
#include "action.hpp"

namespace mmpg {

class Game {
 public:
  virtual World* GenerateWorld() = 0;
  virtual World* ReadWorld(std::istream& stream) = 0;

  virtual Action* ReadAction(std::istream& stream) = 0;
};

}
