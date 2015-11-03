#include <zmq.hpp>
#include "server.hpp"

int main ()  {
  // Prepare our context and socket
  zmq::context_t context(1);
  mmpg::Server server(context, "5555");

  server.run();

  return 0;
}
