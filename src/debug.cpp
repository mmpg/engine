#include "debug.hpp"

namespace mmpg {
namespace debug {

void Print(std::string msg) {
  std::cerr << msg;
  std::cerr.flush();
}

void Print(std::string who, std::string msg) {
  std::cerr << '[' << who << "] " << msg;
  std::cerr.flush();
}

void Println() {
  std::cerr << std::endl;
}

void Println(std::string msg) {
  std::cerr <<  msg << std::endl;
}

void Println(std::string who, std::string msg) {
  std::cerr << '[' << who << "] " << msg << std::endl;
}

}
}
