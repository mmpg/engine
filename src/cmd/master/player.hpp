#pragma once

#include <string>

namespace mmpg {

class Player {
 public:
  Player(std::string email);
  ~Player();

  void build();
  void start();

  const std::string& id() const;
  const std::string& email() const;
  std::string path() const;
  bool is_built() const;
  bool is_alive() const;

 private:
  std::string id_;
  std::string email_;
  bool is_built_;
  pid_t pid_;
};

}
