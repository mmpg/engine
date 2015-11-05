#include "player.hpp"
#include "../../utils.hpp"

namespace mmpg {

Player::Player(std::string email) : email_(email), is_built_(false), pid_(-1) {

}

void Player::build() {
  // TODO: Improve error management
  utils::Mkdir(path(), 0777);

  is_built_ = utils::System("./bin/build_player " + email_);
}

void Player::start() {
  create_pipe("input");
  create_pipe("output");

  pid_ = utils::Fork();

  if(pid_ == 0) {
    utils::Chdir(path());
    utils::Exec("player", {"player"});
  }
}


const std::string& Player::email() const {
  return email_;
}

std::string Player::path() const {
  return "match/players/" + email_;
}

bool Player::is_built() const {
  return is_built_;
}

bool Player::is_started() const {
  return pid_ != 0;
}

pid_t Player::pid() const {
  return pid_;
}

void Player::create_pipe(std::string name) const {
  std::string filename = path() + "/" + name;

  if(utils::FileExists(filename)) {
    utils::Unlink(filename);
  }

  utils::Mkfifo(filename);
}
}
