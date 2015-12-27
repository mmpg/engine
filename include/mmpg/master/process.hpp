#pragma once

#include "../game.hpp"

namespace mmpg {
namespace master {

class Process {
 public:
  Process();

  void Run(Game& game);
};

}
}
