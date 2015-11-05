#include "player.hpp"
#include "../../utils.hpp"

namespace mmpg {

Player::Player(std::string email) : email_(email) {

}


void Player::build() {
  utils::Mkdir("match/players/" + email_, 0777);

  is_built_ = utils::System("./bin/build_player " + email_);
}

bool Player::is_built() {
  return is_built_;
}
}
