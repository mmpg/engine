#pragma once

#include <mutex>
#include <vector>
#include "action.hpp"

namespace mmpg {

class World {
 public:
  void Lock();
  void Unlock();

  virtual void Update(int player, const Action& action) = 0;
  virtual void Print(std::ostream& stream) = 0;
  virtual void PrintJSON(std::ostream& stream) = 0;

 private:
  std::mutex mutex_;
};

}
