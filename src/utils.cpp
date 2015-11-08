#include "utils.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <uuid/uuid.h>
#include <sys/wait.h>

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

void Sleep(unsigned int ms) {
  usleep(ms * 1000);
}

bool FileExists(std::string path) {
  return access(path.c_str(), F_OK) != -1;
}

bool System(std::string cmd) {
  return ::system(cmd.c_str()) == 0;
}

int Open(std::string path, int mode) {
  int fd = open(path.c_str(), mode);

  if(fd < 0) {
    myerr("error at open");
  }

  return fd;
}

int OpenForRead(std::string path) {
  return Open(path, O_RDONLY);
}

int OpenForWrite(std::string path) {
  return Open(path, O_WRONLY);
}

pid_t Fork() {
  pid_t pid = fork();

  if(pid < 0) {
    myerr("error at fork");
  }

  return pid;
}

bool IsAlive(pid_t pid) {
  int status;
  return waitpid(pid, &status, WNOHANG) == 0;
}

std::string uuid() {
  uuid_t t;
  uuid_generate(t);

  char uuid[100];
  uuid_unparse(t, uuid);

  return std::string(uuid);
}

}
}
