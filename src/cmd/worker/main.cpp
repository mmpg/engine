#include <zmq.hpp>
#include <fstream>
#include "../../debug.hpp"
#include "../../utils.hpp"
#include "player.hpp"

using namespace mmpg;

void create_directories(const std::string& worker_name) {
  // Create folder for players
  utils::Mkdir(worker_name + "/players", 0777);

  // Create folder for building players
  utils::Mkdir(worker_name + "/build", 0777);
}

void read_players(const std::string worker_name, std::vector<Player*>& players) {
  // Read players
  std::ifstream input(worker_name + "/players.txt");

  unsigned int id;
  std::string email;

  while(input >> id >> email) {
    Player* player = new Player(id, email);
    players.push_back(player);
  }
}

void compile_players(const std::vector<Player*>& players) {
  debug::Println("WORKER", "Compiling players:");

  for(Player* player : players) {
    debug::Print("WORKER", "    " + player->email() + "...");

    player->build();

    debug::Println(player->is_built() ? " ok" : " failed");
  }
}

void run_players(const std::vector<Player*>& players) {
  debug::Println("WORKER", "Running players:");

  for(Player* player : players) {
    if(player->is_built()) {
      debug::Print("WORKER", "    " + player->email() + "...");

      player->start();

      debug::Println(player->is_alive() ? " ok" : " failed");
    }
  }
}

int main(int argc, char* argv[]) {
  if(argc < 2) {
    // TODO: Print usage
    return 1;
  }

  std::string worker_name = argv[1];

  // Prepare directory structure
  create_directories(worker_name);

  // TODO: Read players from master
  // Read players
  std::vector<Player*> players;
  read_players(worker_name, players);

  // Compile players
  compile_players(players);

  // TODO: Wait for master

  // Run players
  run_players(players);

  return 0;
}
