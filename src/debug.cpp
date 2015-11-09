#include <iomanip>
#include "debug.hpp"

namespace mmpg {
namespace debug {

void Print(std::string msg) {
  std::cerr << msg;
  std::cerr.flush();
}

void Print(std::string who, std::string msg) {
  std::string subject = "[" + who + "] ";

  std::cerr << std::right << std::setfill(' ') << std::setw(12) << subject << msg;
  std::cerr.flush();
}

void Println() {
  std::cerr << std::endl;
}

void Println(std::string msg) {
  std::cerr << msg << std::endl;
}

void Println(std::string who, std::string msg) {
  Print(who, msg);
  std::cerr << std::endl;
}

}
}
