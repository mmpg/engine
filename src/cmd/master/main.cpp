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

  // Compile players
  debug::Println("Compiling players:");

  std::vector<Player*> players;

  while(std::getline(input, email)) {
    Player* player = new Player(email);

    debug::Print("    " + email + "...");

    player->build();

    if(player->is_built()) {
      debug::Println(" ok");
    } else {
      debug::Println(" failed");
    }
  }

  // Start players
  debug::Println("Starting players:");


  return 0;
}
