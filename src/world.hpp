#pragma once

#include <mutex>
#include <vector>
#include "action.hpp"

namespace mmpg {

class World {
 public:
  void Lock();
  void Unlock();

  void Read(std::string path);
  virtual void Read(std::istream& stream) = 0;
  virtual void Update(int player, const Action& action) = 0;
  virtual void Print(std::ostream& stream) = 0;
  virtual void PrintJSON(std::ostream& stream) = 0;

  // TODO: Think about where to put this logic
  virtual Action* ParseAction(std::istream& data) = 0;

 private:
  std::mutex mutex_;
};

}
