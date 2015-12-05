#include <fstream>
#include "player.hpp"
#include "../../utils.hpp"

namespace mmpg {

Player::Player(unsigned int id, std::string email) : id_(id), key_(utils::uuid()), email_(email), is_built_(false),
                                                     pid_(0)
{

}

Player::~Player() {

}

void Player::Build() {
  // TODO: Improve error management
  utils::Mkdir(path(), 0777);

  is_built_ = utils::System("./bin/build_player " + email_);
}

void Player::Start() {
  pid_ = utils::Fork();

  if(pid_ == 0) {
    utils::Chdir(path());
    utils::Exec("player", {"player", key_});
  }
}

unsigned int Player::id() const {
  return id_;
}

const std::string& Player::key() const {
  return key_;
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

bool Player::is_alive() const {
  return pid_ > 0 and utils::IsAlive(pid_);
}


void Player::Stop() {
  if(!is_alive()) {
    return;
  }

  utils::Stop(pid_, 2);
}

void Player::Update(const std::string& code) {
  // TODO: Remove code duplication
  // TODO: Save all the submissions
  std::string file = path() + "/ai.cpp";
  std::string backup = file + ".backup";

  if(utils::FileExists(file)) {
    utils::RenameFile(file, backup);
  }

  std::ofstream ai(file);

  ai << code;

  ai.close();

  is_built_ = false;
}

void Player::Recover() {
  std::string file = path() + "/ai.cpp";
  std::string backup = file + ".backup";

  if(utils::FileExists(backup)) {
    utils::RenameFile(backup, file);
  }
}

}
