#include <fstream>
#include "world.hpp"

namespace mmpg {

void World::Read(std::string path) {
  std::ifstream stream(path);
  Read(stream);
}

void World::Lock() {
  mutex_.lock();
}

void World::Unlock() {
  mutex_.unlock();
}

}
