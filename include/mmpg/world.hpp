#pragma once

#include <mutex>
#include <vector>

namespace mmpg {

class World {
 public:
  void Lock();
  void Unlock();

  virtual void Update(float delta) = 0;
  virtual unsigned int updates_per_second() const;

  virtual void PrintStructure(std::ostream& stream) const = 0;
  virtual void PrintViewerStructure() const = 0;

  virtual void ReadData(std::istream& stream) const = 0;
  virtual void PrintData(std::ostream& stream) const = 0;
  virtual void PrintViewerData(std::ostream& stream) const = 0;

 private:
  std::mutex mutex_;
};

}
