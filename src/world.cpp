#include "world.hpp"

namespace mmpg {


World::World() {

}

World::World(std::istringstream stream) {
  // TODO: Parse world from stream
}

void World::Update(int player, std::istringstream& action) {
  // TODO: Update world accordingly
}

void World::Print(std::ostringstream& stream) {

}

void World::Lock() {
  mutex_.lock();
}

void World::Unlock() {
  mutex_.unlock();
}

}
