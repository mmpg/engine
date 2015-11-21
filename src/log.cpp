#include "log.hpp"
#include "utils.hpp"

namespace mmpg {

Log::Log(std::string directory) : directory_(directory), file_(0) {
  utils::Mkdir(directory, 0775);

  new_log_file(current_interval());
}

void Log::Add(const std::string& line) {
  lines_.push_back(line);
}


void Log::Flush() {
  if(lines_.size() > 0) {
    *file_ << lines_[0];
  }

  for(int i = 1; i < lines_.size(); ++i) {
    *file_ << '\n' << lines_[i];
  }

  *file_ << std::endl;

  lines_.clear();

  std::time_t current = current_interval();

  if(interval_ != current) {
    new_log_file(current);
  }
}

std::time_t Log::current_interval() const {
  return (std::time(0) / 300) * 300;
}

void Log::new_log_file(const std::time_t& current) {
  interval_ = current;

  if(file_) {
    file_->close();
    delete file_;
  }

  file_ = new std::ofstream(directory_ + "/" + std::to_string(interval_) + ".log");
}
}
