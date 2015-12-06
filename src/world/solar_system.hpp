#pragma once

#include "sun.hpp"

namespace mmpg {

class SolarSystem {
 public:
  SolarSystem(int seed);

  Sun* sun;
};

}
