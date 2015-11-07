#include "player.hpp"
#include "../../utils.hpp"

namespace mmpg {

Player::Player(std::string email) : email_(email), is_built_(false), pid_(-1), write_(0), read_(0) {

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
  } else {
    write_ = new std::ofstream(path() + "/input");
    read_ = new std::ifstream(path() + "/output");
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

bool Player::is_alive() const {
  *write_ << "PING" << std::endl;

  std::string reply;

  if(!std::getline(*read_, reply)) {
    return false;
  }

  return reply == "PONG";
}

void Player::create_pipe(std::string name) const {
  std::string filename = path() + "/" + name;

  if(utils::FileExists(filename)) {
    utils::Unlink(filename);
  }

  utils::Mkfifo(filename);
}

Player::~Player() {
  if(read_) {
    read_->close();
    delete read_;
  }

  if(write_) {
    write_->close();
    delete write_;
  }
}
}
