#pragma once

#include <sstream>
#include <mutex>

namespace mmpg {

class World {
 public:
  World();
  World(std::istringstream stream);

  void Lock();
  void Unlock();

  void Update(int player, std::istringstream& action);
  void Print(std::ostringstream& stream);

 private:
  std::mutex mutex_;
};

}
