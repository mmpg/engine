//
// Created by hector on 9/11/15.
//

#include "master.hpp"
#include "../../debug.hpp"
#include <zmq.hpp>

namespace mmpg {


Master::Master() : worker_(new Worker()), run_(true) {

}

Master::~Master() {
  delete worker_;
}

void Master::Run() {
  // Start game world server
  zmq::context_t zcontext(1);

  zmq::socket_t server(zcontext, ZMQ_REP);
  server.bind("tcp://*:5557");

  worker_->Run();

  debug::Println("MASTER", "Listening to 0.0.0.0:5577");

  while(run_) {
    zmq::message_t request;
    server.recv(&request);

    std::string data = std::string(static_cast<char*>(request.data()), request.size());

    debug::Println("MASTER", "    Request received: " + data);
    server.send("reply", 5); // TODO: Send game world status
  }
}

}
