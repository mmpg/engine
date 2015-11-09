#pragma once

#include <map>
#include "player.hpp"

namespace mmpg {

class Worker {
 public:
  Worker();
  ~Worker();

  void Run();

  bool has_player(std::string id) const;
  bool has_player_with_email(std::string email) const;


 private:
  std::map<std::string, Player*> players_;
  std::map<std::string, Player*> email_player_;

  void create_directories();
  void read_players();
  void compile_players();
  void run_players();
};

}