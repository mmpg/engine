#pragma once

#include <string>

namespace mmpg {

class Player {
 public:
  Player(std::string email);

  void build();
  void start();

  const std::string& email() const;
  bool is_built();

 private:
  std::string email_;
  bool is_built_;
};

}
