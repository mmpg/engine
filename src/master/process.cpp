#include <thread>
#include <sstream>
#include <master/process.hpp>
#include "api.hpp"
#include "server.hpp"
#include "../utils.hpp"
#include "../debug.hpp"

namespace mmpg {
namespace master {

namespace {

void run_api(Api& api, Worker& worker, Log& log) {
  api.Run(worker, log);
}

void run_server(Server& server, Worker& worker, Game& game, World& world, Notifier& notifier, Log& log) {
  server.Run(worker, game, world, notifier, log);
}

void run_game_loop(World& world, Notifier& notifier, Log& log) {
  unsigned int updates_per_second = world.updates_per_second();
  unsigned int update_in_second = 0;
  float update_interval = 1.f / updates_per_second;
  float accum = 0.f;
  float last_tick = utils::clock_time();

  while(true) {
    float current_tick = utils::clock_time();
    accum += current_tick - last_tick;
    last_tick = current_tick;

    while(accum >= update_interval) {
      world.Lock();

      world.Update(update_interval);

      if(update_in_second == updates_per_second) {
        // Sync every second
        log.Flush();

        std::ostringstream stream;
        world.PrintJSON(stream);

        std::string notification = std::to_string(utils::time_ms()) + " SYNC " + stream.str();
        notifier.Notify(notification);

        log.Add(notification);

        update_in_second = 0;
      } else {
        update_in_second++;
      }

      world.Unlock();

      accum -= update_interval;
    }

    std::this_thread::sleep_for(std::chrono::duration<float, std::ratio<1,1>>(update_interval - accum));
  }
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

  // Print current world
  std::ostringstream stream;
  world->Print(stream);

  debug::Println("MASTER", "Current world:");
  debug::Print(stream.str());

  // Start servers
  std::thread api_thread(run_api, std::ref(api), std::ref(worker), std::ref(log));
  std::thread server_thread(run_server, std::ref(server), std::ref(worker), std::ref(game), std::ref(*world),
                            std::ref(notifier), std::ref(log));

  // Run players
  worker.Run();

  // Run game loop
  run_game_loop(*world, notifier, log);
}

}
}
