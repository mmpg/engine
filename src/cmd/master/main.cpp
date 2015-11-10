#include <zmq.hpp>
#include <sstream>
#include <thread>
#include "worker.hpp"
#include "../../world.hpp"
#include "../../debug.hpp"
#include "notifier.hpp"
#include "api.hpp"
#include "server.hpp"


using namespace mmpg;

void run_server(Server& server, Worker& worker, World& world, Notifier& notifier) {
  server.Run(worker, world, notifier);
}

void run_api(Api& api) {
  api.Run();
}

int main() {
  // ZeroMQ context
  zmq::context_t zcontext(1);

  // Components
  Api api(zcontext, 5555);
  Notifier notifier(zcontext, 5556);
  Server server(zcontext, 5557);
  Worker worker;
  World world;

  // Start servers
  std::thread server_thread(run_server, std::ref(server), std::ref(worker), std::ref(world), std::ref(notifier));
  std::thread api_thread(run_api, std::ref(api));

  // Run players
  worker.Run();

  // Join threads
  server_thread.join();
  api_thread.join();

  return 0;
}
