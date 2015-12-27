#include <thread>
#include <sstream>
#include <master/process.hpp>
#include "api.hpp"
#include "server.hpp"
#include "../utils.hpp"

namespace mmpg {
namespace master {

namespace {

void run_api(Api& api, Worker& worker, Log& log) {
  api.Run(worker, log);
}

void run_server(Server& server, Worker& worker, Game& game, World& world, Notifier& notifier, Log& log) {
  server.Run(worker, game, world, notifier, log);
}

}

Process::Process() {

}

void Process::Run(Game& game) {
  // ZeroMQ context
  zmq::context_t zcontext(1);

  // Components
  Api api(zcontext, 5555);
  Notifier notifier(zcontext, 5556);
  Server server(zcontext, 5557);

  // TODO: Read workers from file
  // TODO: Initialize workers properly and distribute players
  // TODO: Use a worker vector
  Worker worker;

  // Game log
  Log log("match/log");

  World* world;

  if(utils::FileExists("match/world.txt")) {
    std::ifstream stream("match/world.txt");

    // Read existing world
    world = game.ReadWorld(stream);
  } else {
    // TODO: This should be API-driven
    // Generate a new world
    world = game.GenerateWorld();
    log.Clear();
  }

  // Start servers
  std::thread api_thread(run_api, std::ref(api), std::ref(worker), std::ref(log));
  std::thread server_thread(run_server, std::ref(server), std::ref(worker), std::ref(game), std::ref(*world),
                            std::ref(notifier), std::ref(log));

  // Run players
  worker.Run();

  // Client synchronization
  while(true) {
    world->Lock();

    log.Flush();

    std::ostringstream stream;
    world->PrintJSON(stream);

    std::string notification = std::to_string(utils::time()) + " SYNC " + stream.str();
    notifier.Notify(notification);

    log.Add(notification);

    world->Unlock();

    // Every second
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}

}
}
