#include "world.hpp"

namespace mmpg {

void World::Lock() {
  mutex_.lock();
}

void World::Unlock() {
  mutex_.unlock();
}

unsigned int World::updates_per_second() const {
  return 5;
}

}
