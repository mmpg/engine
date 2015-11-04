#pragma once

#include <string>
#include <zmq.hpp>
#include "notifier.hpp"

namespace mmpg {
class Server {
public:
    Server(zmq::context_t &context, std::string port);

    void Run(Notifier &notifier);

private:
    zmq::socket_t socket_;
};
}
