#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <ctime>

namespace mmpg {

class Log {
 public:
  Log(std::string directory);

  std::string Read(unsigned int time) const;

  void Add(const std::string& line);
  void Flush();
  void Clear();

 private:
  std::string directory_;
  std::vector<std::string> lines_;
  std::ofstream* file_;
  std::time_t interval_;

  std::time_t interval(const std::time_t& time) const;
  std::string log_file(const std::time_t& interval) const;
  void new_log_file(const std::time_t& interval);
};

}
