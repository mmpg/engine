#include "debug.hpp"

namespace mmpg {
namespace debug {
void Print(std::string msg) {
  std::cerr << msg;
}

void Println(std::string msg) {
  Print(msg);
  std::cerr << std::endl;
}
}
}
