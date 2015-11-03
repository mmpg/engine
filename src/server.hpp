#pragma once

#include <string>
#include <zmq.hpp>

namespace mmpg {
class Server {
public:
    Server(zmq::context_t &context, std::string port);

    void run();

private:
    zmq::socket_t socket_;
};
}
