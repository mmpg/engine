#include "log.hpp"
#include "utils.hpp"
#include "base64.hpp"

namespace mmpg {

Log::Log(std::string directory) : directory_(directory), file_(0) {
  utils::Mkdir(directory, 0775);

  new_log_file(interval(std::time(0)));
}

std::string Log::Read(unsigned int time) const {
  std::string gzip_file = log_file(interval(time)) + ".gz";

  if(utils::FileExists(gzip_file)) {
    std::string log = utils::ReadFile(gzip_file);
    return base64::Encode((unsigned const char*)log.c_str(), (unsigned int)log.length());
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

  for(unsigned int i = 1; i < lines_.size(); ++i) {
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
  if(file_) {
    file_->close();

    // Gzip log file
    utils::System("gzip " + log_file(interval_));

    delete file_;
  }

  interval_ = current;
  file_ = new std::ofstream(log_file(interval_));
}

void Log::Clear() {
  lines_.clear();
  utils::System("rm -f " + directory_ + "/*.log");

  if(file_) {
    file_->close();
    delete file_;
    file_ = 0;
  }

  new_log_file(interval(std::time(0)));
}

}
