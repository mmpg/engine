#pragma once

#include <string>
#include <fstream>

namespace mmpg {

class Player {
 public:
  Player(std::string email);
  ~Player();

  void build();
  void start();

  const std::string& email() const;
  std::string path() const;
  bool is_built() const;
  bool is_alive() const;
  pid_t pid() const;

 private:
  std::string email_;
  bool is_built_;
  pid_t pid_;
  std::ofstream* send_;
  std::ifstream* read_;

  void create_pipe(std::string name) const;
};

}
