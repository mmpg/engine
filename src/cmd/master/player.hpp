#pragma once

#include <string>

namespace mmpg {

class Player {
 public:
  Player(std::string email);

  void build();
  void start();

  const std::string& email() const;
  std::string path() const;
  bool is_built() const;
  bool is_started() const;
  pid_t pid() const;

 private:
  std::string email_;
  bool is_built_;
  pid_t pid_;

  void create_pipe(std::string name) const;
};

}
