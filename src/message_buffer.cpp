#include "message_buffer.hpp"

namespace mmpg {

void MessageBuffer::Ready() {
  char* data = (char*) message.data();
  setg(data, data, data + message.size());
}

}
