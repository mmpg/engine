#include "player.hpp"
#include "../../utils.hpp"

namespace mmpg {

Player::Player(std::string email) : email_(email) {

}

void Player::build() {
  // TODO: Improve error management
  utils::Mkdir("match/players/" + email_, 0777);

  is_built_ = utils::System("./bin/build_player " + email_);
}

void Player::start() {
  // TODO: Create pipes, fork process, set limits and execute player
}

bool Player::is_built() {
  return is_built_;
}

const std::string& Player::email() const {
  return email_;
}

}
