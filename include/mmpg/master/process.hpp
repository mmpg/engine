#pragma once

#include "../world.hpp"

namespace mmpg {
namespace master {

class Process {
 public:
  Process();

  void Run(World& world);
};

}
}
