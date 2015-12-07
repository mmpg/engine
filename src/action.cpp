#include "action.hpp"

namespace mmpg {
Action::Action(std::string type) : type_(type) {

}

Action::~Action() {

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
