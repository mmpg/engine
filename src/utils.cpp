#include "utils.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <uuid/uuid.h>
#include <sys/wait.h>
#include <fstream>

namespace mmpg {
namespace utils {

void Mkdir(const std::string& path, __mode_t mode) {
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

void Mkfifo(const std::string& path) {
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

void Unlink(const std::string& path) {
  int error = unlink(path.c_str());

  if(error != 0) {
    myerr("error at unlink");
  }
}

void Chdir(const std::string& path) {
  int error = chdir(path.c_str());

  if(error != 0) {
    myerr("error at chdir");
  }
}

void Exec(const std::string& path, std::vector<std::string> args) {
  char* argv[args.size() + 1];

  for(unsigned int i = 0;  i < args.size(); ++i) {
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

bool FileExists(const std::string& path) {
  return access(path.c_str(), F_OK) != -1;
}

bool System(const std::string& cmd) {
  return ::system(cmd.c_str()) == 0;
}

int Open(const std::string& path, int mode) {
  int fd = open(path.c_str(), mode);

  if(fd < 0) {
    myerr("error at open");
  }

  return fd;
}

int OpenForRead(const std::string& path) {
  return Open(path, O_RDONLY);
}

int OpenForWrite(const std::string& path) {
  return Open(path, O_WRONLY);
}

std::string ReadFile(const std::string& path) {
  std::ifstream t(path, std::ios::binary);
  t.seekg(0, std::ios::end);
  size_t size = (size_t) t.tellg();

  std::string buffer(size, ' ');
  t.seekg(0);
  t.read(&buffer[0], size);

  return buffer;
}

bool RenameFile(const std::string& current_name, const std::string& new_name) {
  return rename(current_name.c_str(), new_name.c_str()) == 0;
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

void Stop(pid_t pid, int timeout) {
  while(IsAlive(pid)) {
    kill(pid, timeout < 0 ? SIGKILL : SIGQUIT);

    Sleep(100);
    timeout -= 100;
  }
}

std::string uuid() {
  uuid_t t;
  uuid_generate(t);

  char uuid[100];
  uuid_unparse(t, uuid);

  return std::string(uuid);
}

float time() {
  return time_us() / 1000000.f;
}

long unsigned int time_ms() {
  return time_us() / 1000;
}

long unsigned int time_us() {
  timespec time;
  clock_gettime(CLOCK_MONOTONIC, &time);

  return static_cast<long unsigned int>(time.tv_sec) * 1000000 + time.tv_nsec / 1000;
}

void Send(zmq::socket_t& socket, const std::string& msg) {
  socket.send(msg.c_str(), msg.length());
}

}
}
