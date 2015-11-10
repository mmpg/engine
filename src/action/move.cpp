#include "move.hpp"

namespace mmpg {

Move::Move(char direction) : super("move"), direction_(direction) {

}

void Move::end_json(std::ostream& stream) const {
  stream << ",\"direction\":\"" << direction_ << "\"}";
}
}
