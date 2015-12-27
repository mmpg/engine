#pragma once

#include "../game.hpp"
#include "ai.hpp"

namespace mmpg {
namespace player {

class Process {
 public:
  Process(int argc, char* argv[]);

  void Run(Game& game);

 private:
  std::string id_;
  bool run_;
};

}
}
