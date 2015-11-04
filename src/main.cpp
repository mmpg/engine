#include <zmq.hpp>
#include "server.hpp"
#include "notifier.hpp"

int main ()  {
  zmq::context_t context(1);

  mmpg::Server server(context, "5555");
  mmpg::Notifier notifier(context, "5556");

  server.Run(notifier);

  return 0;
}
