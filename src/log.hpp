#pragma once

#include <string>
#include <vector>

namespace mmpg {

class Log {
 public:
  Log(std::string directory);

  void Add(std::string line);
  void Flush();

 private:
  std::string directory_;
  std::vector<std::string> lines_;
};

}
