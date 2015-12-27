#pragma once

#include <mutex>
#include <vector>

namespace mmpg {

class World {
 public:
  void Lock();
  void Unlock();

  virtual void Print(std::ostream& stream) = 0;
  virtual void PrintJSON(std::ostream& stream) = 0;

 private:
  std::mutex mutex_;
};

}
