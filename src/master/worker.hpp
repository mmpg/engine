#pragma once

#include <map>
#include "player.hpp"

namespace mmpg {

class Worker {
 public:
  Worker();
  ~Worker();

  void Run();

  bool Deploy(const std::string& email, const std::string& code);

  bool has_player_with_key(const std::string& key) const;
  bool has_player_with_email(const std::string& email) const;
  unsigned int player_id(const std::string& key) const;


 private:
  std::map<std::string, Player*> key_player_;
  std::map<std::string, Player*> email_player_;

  void create_directories();
  void read_players();
  void compile_players();
  void run_players();
};

}
