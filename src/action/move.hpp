#pragma once

#include "../action.hpp"

namespace mmpg {

class Move : public Action {
 public:
  typedef Action super;

  Move(char direction);

  char direction() const;
  std::string str() const;

 protected:
  void end_json(std::ostream& stream) const;

 private:
  char direction_;
};

}
