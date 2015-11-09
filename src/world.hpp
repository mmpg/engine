#include <sstream>

namespace mmpg {

class World {
 public:
  World();
  World(std::istringstream stream);

  void Update(int player, std::istringstream& action);
  void Print(std::ostringstream& stream);
};

}
