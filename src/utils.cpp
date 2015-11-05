#include "utils.hpp"

namespace mmpg {
namespace utils {
void Mkdir(std::string path, __mode_t mode) {
  struct stat sb;

  if(stat(path.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode)) {
    // Directory already exists
    return;
  }

  int error = ::mkdir(path.c_str(), mode);

  if(error) {
    myerr("error at mkdir");
  }
}

bool System(std::string cmd) {
  return ::system(cmd.c_str()) == 0;
}
}
}
