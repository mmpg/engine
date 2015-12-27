#include "world.hpp"

namespace mmpg {

void World::Lock() {
  mutex_.lock();
}

void World::Unlock() {
  mutex_.unlock();
}

}
