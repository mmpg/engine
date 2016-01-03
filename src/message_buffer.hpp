#pragma once

#include <streambuf>
#include <zmq.hpp>

namespace mmpg {

class MessageBuffer : public std::streambuf {
 public:
  void Ready();

  zmq::message_t message;
};

};
