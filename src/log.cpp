#include "log.hpp"

namespace mmpg {

Log::Log(std::string directory) : directory_(directory) {

}

void Log::Add(std::string line) {
  lines_.push_back(line);
}


void Log::Flush() {
  // TODO: Write log file
  lines_.clear();
}

}
