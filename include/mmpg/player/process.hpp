#pragma once

#include "../world.hpp"
#include "ai.hpp"

namespace mmpg {
namespace player {

class Process {
 public:
  Process(int argc, char* argv[]);

  void Run(World& world);

 private:
  std::string id_;
  bool run_;
};

}
}
