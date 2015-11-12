#pragma once

#include <mutex>
#include <vector>
#include "action.hpp"

namespace mmpg {

class World {
 public:
  World();

  void Lock();
  void Unlock();

  void Read(std::string path);
  void Read(std::istream& stream);
  void Update(int player, const Action& action);
  void Print(std::ostream& stream);
  void PrintJSON(std::ostream& stream);

  struct Ship {
    float x, y;
  };

 private:
  std::mutex mutex_;
  std::vector<Ship*> ships_;
};

}
