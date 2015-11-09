//
// Created by hector on 9/11/15.
//

#include <fstream>
#include "worker.hpp"
#include "../../utils.hpp"
#include "../../debug.hpp"

namespace mmpg {

Worker::Worker() {

}

Worker::~Worker() {

}


void Worker::Run() {
  create_directories();
  read_players();
  compile_players();
  run_players();
}


bool Worker::has_player_with_key(std::string key) const {
  return key_player_.find(key) != key_player_.end();
}


bool Worker::has_player_with_email(std::string email) const {
  return email_player_.find(email) != email_player_.end();
}

void Worker::create_directories() {
  // Create folder for players
  utils::Mkdir("match/players", 0777);

  // Create folder for building players
  utils::Mkdir("match/build", 0777);
}

void Worker::read_players() {
  // Read players
  std::ifstream input("match/players.txt");
  std::string email;

  // Compile players
  debug::Println("WORKER", "Compiling players:");

  while(std::getline(input, email)) {
    Player* player = new Player(email);

    key_player_[player->key()] = player;
    email_player_[player->email()] = player;
  }
}

void Worker::compile_players() {
  for(auto& kv : email_player_) {
    Player* player = kv.second;

    debug::Print("WORKER", "    " + player->email() + "...");

    player->build();

    debug::Println(player->is_built() ? " ok" : " failed");
  }
}

void Worker::run_players() {
  debug::Println("WORKER", "Running players:");

  for(auto& kv : email_player_) {
    Player* player = kv.second;

    if(player->is_built()) {
      debug::Print("WORKER", "    " + player->email() + "...");

      player->start();

      debug::Println(player->is_alive() ? " ok" : " failed");
    }
  }
}

}
