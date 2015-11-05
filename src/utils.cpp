#include "utils.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

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

void Mkfifo(std::string path) {
  int error;
  error = mkfifo(path.c_str(), O_CREAT);

  if(error != 0) {
    myerr("error at mkfifo");
  }

  error = chmod(path.c_str(), 0600);

  if(error != 0) {
    myerr("error at chmod");
  }
}

void Unlink(std::string path) {
  int error = unlink(path.c_str());

  if(error != 0) {
    myerr("error at unlink");
  }
}

void Chdir(std::string path) {
  int error = chdir(path.c_str());

  if(error != 0) {
    myerr("error at chdir");
  }
}

void Exec(std::string path, std::vector<std::string> args) {
  char* argv[args.size() + 1];

  for(int i = 0;  i < args.size(); ++i) {
    argv[i] = strdup(args[i].c_str());
  }

  // It's important to null terminate the argv array
  argv[args.size()] = 0;

  execv(path.c_str(), argv);
  myerr("error at execv"); // We should not reach this code
}

bool FileExists(std::string path) {
  return access(path.c_str(), F_OK) != -1;
}

bool System(std::string cmd) {
  return ::system(cmd.c_str()) == 0;
}

pid_t Fork() {
  pid_t pid = fork();

  if(pid < 0) {
    myerr("error at fork");
  }

  return pid;
}

}
}
