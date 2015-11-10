#include <fstream>
#include "world.hpp"

namespace mmpg {

World::World() {

}

void World::Read(std::string path) {
  std::ifstream stream("match/world.txt");
  Read(stream);
}


void World::Read(std::istream& stream) {
  std::string section;

  while(stream >> section) {
    if(section == "PLAYERS") {
      int x, y;

      while(stream >> x >> y) {
        Ship* ship = new Ship;
        ship->x = x;
        ship->y = y;

        ships_.push_back(ship);
      }
    }
  }
}

void World::Update(int player, const Action& action) {
  // TODO: Update world accordingly
}


void World::Print(std::ostream& stream) {
  stream << "PLAYERS" << std::endl;

  for(Ship* ship : ships_) {
    stream << ship->x << ' ' << ship->y << std::endl;
  }
}

void World::PrintJSON(std::ostream& stream) {
  stream << "{\"players\":[";

  for(Ship* ship : ships_) {
    stream << "{\"x\":" << ship->x << ",\"y\":" << ship->y << "}";
  }

  stream << "]}";
}

void World::Lock() {
  mutex_.lock();
}

void World::Unlock() {
  mutex_.unlock();
}

}
