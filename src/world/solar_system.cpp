#include <random>
#include "solar_system.hpp"
#include "universe.hpp"

namespace mmpg {

SolarSystem::SolarSystem(int seed) {

  std::seed_seq sseq({seed, (int)Universe::OBJECTS::SOLAR_SYSTEM, 0});
  std::mt19937 generator(sseq);

  sun = new Sun(Sun::TYPE::G, 20 + generator() % 10);
}

}
