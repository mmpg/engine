#include <thread>
#include <sstream>
#include "process.hpp"
#include "api.hpp"
#include "server.hpp"
#include "../utils.hpp"

namespace mmpg {
namespace master {

namespace {

void run_api(Api& api, Worker& worker, Log& log) {
  api.Run(worker, log);
}

void run_server(Server& server, Worker& worker, World& world, Notifier& notifier, Log& log) {
  server.Run(worker, world, notifier, log);
}

}

Process::Process() {

}

void Process::Run(World& world) {
  // ZeroMQ context
  zmq::context_t zcontext(1);

  // Components
  Api api(zcontext, 5555);
  Notifier notifier(zcontext, 5556);
  Server server(zcontext, 5557);

  // TODO: Read workers from file
  // TODO: Initialize them properly and distribute players
  // TODO: Use a worker vector
  Worker worker;

  // Read world
  world.Read("match/world.txt");

  // Game log
  Log log("match/log");

  // TODO: Clear log when new match only
  log.Clear();

  // Start servers
  std::thread api_thread(run_api, std::ref(api), std::ref(worker), std::ref(log));
  std::thread server_thread(run_server, std::ref(server), std::ref(worker), std::ref(world), std::ref(notifier),
                            std::ref(log));

  // Run players
  worker.Run();

  // Client synchronization
  while(true) {
    world.Lock();

    log.Flush();

    std::ostringstream stream;
    world.PrintJSON(stream);

    std::string notification = std::to_string(utils::time()) + " SYNC " + stream.str();
    notifier.Notify(notification);

    log.Add(notification);

    world.Unlock();

    // Every second
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}

}
}
