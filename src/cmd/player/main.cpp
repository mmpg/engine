#include <fstream>
#include "../../utils.hpp"

using namespace mmpg;

int main() {
  std::ifstream read("input");
  std::ofstream write("output");

  std::string request;

  while(getline(read, request)) {
    if(request == "PING") {
      write << "PONG" << std::endl;
    }
  }

  return 0;
}
