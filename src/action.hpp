#pragma once

#include <istream>

namespace mmpg {

class Action {
 public:
  static Action* Read(std::istream& stream);

  Action(std::string type);

  const std::string& type() const;

  void PrintJSON(std::ostream& stream) const;

 protected:
  virtual void end_json(std::ostream& stream) const;

 private:
  std::string type_;
};

}
