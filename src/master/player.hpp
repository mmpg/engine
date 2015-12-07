#pragma once

#include <string>

namespace mmpg {

class Player {
 public:
  Player(unsigned int id, std::string email);
  ~Player();

  void Build();
  void Start();
  void Stop();
  void Update(const std::string& code);
  void Recover();

  unsigned int id() const;
  const std::string& key() const;
  const std::string& email() const;
  std::string path() const;
  bool is_built() const;
  bool is_alive() const;

 private:
  unsigned int id_;
  std::string key_;
  std::string email_;
  bool is_built_;
  pid_t pid_;
};

}
