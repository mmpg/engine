#pragma once

#include <string>

namespace mmpg {
namespace base64 {

std::string Encode(unsigned const char* bytes_to_encode, unsigned int in_len);
std::string Decode(const std::string& encoded);

}
}
