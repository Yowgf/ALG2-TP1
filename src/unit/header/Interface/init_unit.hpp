// ALG2-TP1 project appliance file
// Interface module
// Init class unit tests
// =============================================================
////////////////////////////////////////////////////////////////

#ifndef INIT_UNIT_H
#define INIT_UNIT_H 1

#include "Interface/init.hpp"

#include <stdexcept>
#include <string>
#include <vector>

namespace Unit_tests {

class init_unit {
public:
  init_unit();
  ~init_unit();

private:
  static const unsigned kmax_argc = 5;
  static const unsigned kmax_size_arg = 64;
  int prog_argc;
  char** prog_argv;
  std::vector<std::string*> arg_list;
  std::string arg1;
  std::string arg2;
  std::string arg3;
  std::string arg4;
  std::string arg5;

  // Create factory method to be able to call the constructor
  static void emulate_init(int argc, char** argv)
  {
    Interface::init{argc, argv};
  }
  
  void make_argv();
  // Check if only providing the program will throw gracefully_terminate exception
  void check_no_args();
  void check_3_args();
  void check_5_args();
};

}

#endif
