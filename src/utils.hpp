#pragma once

#include <string>
#include <vector>
#include <sys/stat.h>
#include <chrono>
#include <zmq.hpp>

/**
 * Defines customized error macros.
 * (somehow adapted from err.h and error.h)
 */

#define myerror_at_line(status, error, file, line, ...) { fprintf(stderr, "Error at %s:%i: ", file, line); fprintf(stderr, __VA_ARGS__); if (error) perror(" errno"); fprintf(stderr, "\n"); exit(status); }
#define myerr(...) myerror_at_line(EXIT_FAILURE, errno, __FILE__, __LINE__, __VA_ARGS__)

namespace mmpg {
namespace utils {

void Mkdir(const std::string& path, __mode_t mode);
void Mkfifo(const std::string& path);
void Unlink(const std::string& path);
void Chdir(const std::string& path);
void Exec(const std::string& path, std::vector<std::string> args);
void Sleep(unsigned int ms);

bool FileExists(const std::string& path);
bool System(const std::string& cmd);

std::string ReadFile(const std::string& path);

int Open(const std::string& path, int mode);
int OpenForRead(const std::string& path);
int OpenForWrite(const std::string& path);

pid_t Fork();
bool IsAlive(pid_t pid);
void Stop(pid_t pid, unsigned int timeout);

std::string uuid();

long int time();

void Send(zmq::socket_t& socket, const std::string& msg);

std::string Base64Decode(const std::string& encoded);
}
}
