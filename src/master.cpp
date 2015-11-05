#include <iostream>
#include <fstream>
#include "utils.hpp"

int main() {
  // Create folder for players
  mmpg::mkdir("players", 0777);

  std::ifstream input("players.txt");
  std::string email;

  while(std::getline(input, email)) {
    mmpg::mkdir("players/" + email, 0777);
  }

  return 0;
}
