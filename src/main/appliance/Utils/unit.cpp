// ALG2-TP1 project applance file
// Utils module
// unit class
// =============================================================
////////////////////////////////////////////////////////////////

#include "Utils/unit.hpp"

#include <iostream>

namespace Utils {

void unit::print_start(const char* annotation)
{
  std::cerr << '\n'
            << std::string(10, '~') << '\n'
            << "Starting " << annotation << " tests\n\n";
}

void unit::print_end(const char* annotation)
{
  std::cerr << '\n'
            << "Ended " << annotation << " tests\n"
            << std::string(10, '~') << '\n';
}
  
void unit::CHECK_TRUE(const std::string annotation, const bool t_stm)
{
  CHECK(annotation, t_stm);
}

void unit::CHECK_FALSE(const std::string annotation, const bool t_stm)
{
  CHECK(annotation, !t_stm);
}

void unit::CHECK(const std::string annotation, const bool t_stm)
{
  if (!t_stm) {
    std::cerr << "Check " << annotation << " unsuccessful.\n";
  }
  else {
    std::cerr << "Check " << annotation << " successful.\n";
  }
}
  
}
