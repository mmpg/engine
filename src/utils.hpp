#pragma once

#include <string>
#include <vector>
#include <sys/stat.h>

/**
 * Defines customized error macros.
 * (somehow adapted from err.h and error.h)
 */

#define myerror_at_line(status, error, file, line, ...) { fprintf(stderr, "Error at %s:%i: ", file, line); fprintf(stderr, __VA_ARGS__); if (error) perror(" errno"); fprintf(stderr, "\n"); exit(status); }
#define myerr(...) myerror_at_line(EXIT_FAILURE, errno, __FILE__, __LINE__, __VA_ARGS__)

namespace mmpg {
namespace utils {

void Mkdir(std::string path, __mode_t mode);
void Mkfifo(std::string path);
void Unlink(std::string path);
void Chdir(std::string path);
void Exec(std::string path, std::vector<std::string> args);

bool FileExists(std::string path);
bool System(std::string cmd);

pid_t Fork();

}
}
