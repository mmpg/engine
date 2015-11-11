#pragma once

namespace mmpg {

class AI {
  virtual void play() = 0;

  virtual void load();
  virtual void save();
};

}
