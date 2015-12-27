#pragma once

#include <ostream>
#include "world.hpp"

namespace mmpg {

class Action {
 public:
  virtual ~Action();

  virtual std::string str() const = 0;
  virtual void PrintJSON(std::ostream& stream) const = 0;
  virtual void Perform(int player_id, World& world) const = 0;
};

}
