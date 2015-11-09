#pragma once

#include <iostream>

namespace mmpg {
namespace debug {

void Print(std::string msg);
void Print(std::string who, std::string msg);

void Println();
void Println(std::string msg);
void Println(std::string who, std::string msg);

}
}
