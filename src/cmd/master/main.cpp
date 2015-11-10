#include <zmq.hpp>
#include <thread>
#include "worker.hpp"
#include "../../world.hpp"
#include "notifier.hpp"
#include "api.hpp"
#include "server.hpp"

using namespace mmpg;

void run_api(Api& api) {
  api.Run();
}

void run_server(Server& server, Worker& worker, World& world, Notifier& notifier) {
  server.Run(worker, world, notifier);
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
  std::thread api_thread(run_api, std::ref(api));
  std::thread server_thread(run_server, std::ref(server), std::ref(worker), std::ref(world), std::ref(notifier));

  // Run players
  worker.Run();

  // Client synchronization
  while(true) {
    world.Lock();

    std::ostringstream stream;
    world.Print(stream);
    notifier.Notify(stream.str());

    world.Unlock();

    // Every second
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  return 0;
}
