#include "sun.hpp"

namespace mmpg {

Sun::Sun(TYPE type, unsigned int radius) : type(type), radius(radius) {

}

void Sun::PrintJSON(std::ostream& stream) const {
  stream << "{\"type\":\"G\",\"radius\":" << radius << "}";
}
}
