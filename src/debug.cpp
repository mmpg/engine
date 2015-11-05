#include "debug.hpp"

namespace mmpg {
namespace debug {

void Print(std::string msg) {
  std::cerr << msg;
  std::cerr.flush();
}

void Println(std::string msg) {
  std::cerr << msg << std::endl;
}

}
}
