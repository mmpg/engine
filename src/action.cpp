#include "action.hpp"
#include "action/move.hpp"

namespace mmpg {

// TODO: Use a register
Action* Action::Read(std::istream& data) {
  char t;

  data >> t;

  switch(t) {
    case 'U':
    case 'D':
    case 'L':
    case 'R':
      return new Move(t);

    default:
      throw "Undefined action";
  }
}

Action::Action(std::string type) : type_(type) {

}

const std::string& Action::type() const {
  return type_;
}

void Action::PrintJSON(std::ostream& stream) const {
  stream << "{\"type\":\"" << type_ << "\"";
  end_json(stream);
}

void Action::end_json(std::ostream& stream) const {
  stream << "}";
}
}
