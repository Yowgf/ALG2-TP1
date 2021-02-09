// ALG2-TP1 project main file
// main function
// =============================================================
//
// Description:
// This is the place where the program takes the input and hands
//   it over to validity checker, which should then dispatch it
//   to the algorithm manager.
// Any uncaught exceptions in functions subsequent to ~main~ are
//   handled here with a gentle STOP!
////////////////////////////////////////////////////////////////

#include "Alg/Alg.hpp"
#include "DS/DS.hpp"
#include "Interface/Interface.hpp"
#include "Utils/Utils.hpp"

#include <stdexcept>

int main(int argc, char** argv)
{
  try {
    Interface::init(argc, argv);
  }
  catch(const std::exception& e) {
    Utils::error{e, "Fatal"};
  }
  catch(const Utils::graceful_terminate& e) {
    return Utils::error::error_code;
  }
  catch(...) {
    Utils::error{std::runtime_error{"Uncaught exception identified"}, "Fatal"};
  }

  return Utils::error::error_code;
}
