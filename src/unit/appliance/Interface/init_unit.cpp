// ALG2-TP1 project appliance file
// Interface module
// Init class unit tests
// =============================================================
////////////////////////////////////////////////////////////////

#include "Interface/init_unit.hpp"

#include "Utils/Utils.hpp"

#include <cstdio>
#include <iostream>

#include <stdexcept>

using namespace Utils;

namespace Unit_tests {
  
init_unit::init_unit()
{
  arg_list = {&arg1, &arg2, &arg3, &arg4, &arg5};

  // Allocate prog_argv
  prog_argv = new char*[kmax_argc];
  for (unsigned i = 0; i < kmax_argc; ++i) {
    prog_argv[i] = new char[kmax_size_arg];
  }

  Utils::unit::print_start("init_unit");
  
  // Call the checks to be made
  check_no_args();
  check_3_args();
  check_5_args();

  Utils::unit::print_end("init_unit");
}

init_unit::~init_unit()
{
  for (unsigned i = 0; i < kmax_argc; ++i) {
    if (prog_argv != nullptr) {
      delete[] prog_argv[i];
    }
  }
  delete prog_argv;
}
  
void init_unit::make_argv()
{
  for (unsigned i = 0; i < kmax_argc; ++i) {
    std::string* cur_str = arg_list[i];
    if (cur_str->length() + 1 > kmax_size_arg) {
      throw std::runtime_error{"Argument is too big!"};
    }
    for (unsigned j = 0; j < cur_str->length() + 1; ++j) {
      prog_argv[i][j] = (cur_str->c_str())[j];
    }
  }
}

void init_unit::check_no_args()
{
  prog_argc = 1;
  make_argv(); // All args empty
  
  CHECK_THROWS("check_no_args", emulate_init, graceful_terminate{}, prog_argc, prog_argv);
}

void init_unit::check_3_args()
{
  prog_argc = 3;
  arg1 = "program";
  arg2 = "-c";
  arg3 = "";
  make_argv();

  CHECK_THROWS("check_3_args", emulate_init, graceful_terminate{}, prog_argc, prog_argv);
}

void init_unit::check_5_args()
{
  prog_argc = 5;
  
  arg1 = "program";
  arg2 = "-c";
  arg3 = "tmpin.txt";
  arg4 = "-o";
  arg5 = "tmpout.lz78";
  make_argv();

  // Make sure that these files exist
  FILE* tmpfile1 = fopen(arg3.c_str(), "a");
  fclose(tmpfile1);
  FILE* tmpfile2 = fopen(arg5.c_str(), "a");
  fclose(tmpfile2);
  
  CHECK_NO_THROW("check_5_args", emulate_init, prog_argc, prog_argv);
}

}
