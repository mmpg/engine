#pragma once

#include <istream>

namespace mmpg {

class Action {
 public:
  Action(std::string type);
  virtual ~Action();

  const std::string& type() const;
  virtual std::string str() const = 0;

  void PrintJSON(std::ostream& stream) const;

 protected:
  virtual void end_json(std::ostream& stream) const;

 private:
  std::string type_;
};

}
