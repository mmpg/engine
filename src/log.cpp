#include "log.hpp"
#include "utils.hpp"

namespace mmpg {

Log::Log(std::string directory) : directory_(directory), file_(0) {
  utils::Mkdir(directory, 0775);

  new_log_file(interval(std::time(0)));
}

std::string Log::Read(unsigned int time) const {
  std::string log = log_file(interval(time));

  if(utils::FileExists(log)) {
    return utils::ReadFile(log);
  } else {
    return "";
  }
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

  std::time_t current = interval(std::time(0));

  if(interval_ != current) {
    new_log_file(current);
  }
}

std::time_t Log::interval(const std::time_t& time) const {
  return (time / 300) * 300;
}

std::string Log::log_file(const std::time_t& interval) const {
  return directory_ + "/" + std::to_string(interval) + ".log";
}

void Log::new_log_file(const std::time_t& current) {
  interval_ = current;

  if(file_) {
    file_->close();
    delete file_;
  }

  file_ = new std::ofstream(log_file(interval_));
}

void Log::Clear() {
  utils::System("rm -f " + directory_ + "/*.log");
  new_log_file(interval(std::time(0)));
}
}
