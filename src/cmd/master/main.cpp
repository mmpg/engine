#include <iostream>
#include <fstream>
#include <map>
#include <unistd.h>
#include "../../utils.hpp"
#include "../../debug.hpp"
#include "player.hpp"

using namespace mmpg;

int main() {
  // Create folder for players
  utils::Mkdir("match/players", 0777);

  // Create folder for building players
  utils::Mkdir("match/build", 0777);

  // Read players
  std::ifstream input("match/players.txt");
  std::string email;

  // TODO: Abstract this in a worker class
  // Compile players
  debug::Println("Compiling players:");

  std::map<std::string, Player*> players;

  while(std::getline(input, email)) {
    Player* player = new Player(email);

    debug::Print("    " + email + "...");

    player->build();

    debug::Println(player->is_built() ? " ok" : " failed");

    players[player->key()] = player;
  }

  debug::Println();

  // Start players
  debug::Println("Starting players:");

  for(auto& kv : players) {
    Player* player = kv.second;

    if(player->is_built()) {
      debug::Print("    " + player->email() + "...");

      player->start();

      debug::Println(player->is_alive() ? " ok" : " failed");
    }
  }

  // TODO: Start game world server

  return 0;
}
