#pragma once

#include "worker.hpp"

namespace mmpg {
class Master {
 public:
  Master();
  ~Master();

  void Run();

 private:
  bool run_;
  Worker* worker_;
};
}
