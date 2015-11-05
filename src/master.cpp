#include <iostream>
#include <fstream>
#include "utils.hpp"
#include "debug.hpp"

using namespace mmpg;

int main() {
  // Create folder for players
  utils::Mkdir("match/players", 0777);

  // Create folder for building players
  utils::Mkdir("match/build", 0777);

  std::ifstream input("match/players.txt");
  std::string email;

  debug::Println("Compiling players:");

  while(std::getline(input, email)) {
    utils::Mkdir("match/players/" + email, 0777);

    debug::Print("  " + email + "...");

    if(utils::System("./bin/build_player " + email)) {
      debug::Println(" ok");
    } else {
      debug::Println(" failed");
    }
  }

  return 0;
}
