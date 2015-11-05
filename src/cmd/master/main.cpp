#include <iostream>
#include <fstream>
#include <vector>
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

  std::vector<Player*> players;

  while(std::getline(input, email)) {
    Player* player = new Player(email);

    debug::Print("    " + email + "...");

    player->build();

    debug::Println(player->is_built() ? " ok" : " failed");

    players.push_back(player);
  }

  debug::Println();

  // Start players
  debug::Println("Starting players:");

  for(Player* player : players) {
    if(player->is_built()) {
      debug::Print("    " + player->email() + "...");

      player->start();

      debug::Println(player->is_started() ? " ok" : " failed");
    }
  }

  return 0;
}
