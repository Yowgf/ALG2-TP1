// ALG2-TP1 project appliance file
// Alg_unit module
// lz78_unit class unit tests
// =============================================================
////////////////////////////////////////////////////////////////

#include "Alg/lz78_unit.hpp"

#include "Alg/lz78.hpp"
#include "Utils/Utils.hpp"

#include <cstdio>

using namespace Utils;
namespace Unit_tests {
  
lz78_unit::lz78_unit()
{
  unit::print_start("lz78_unit");

  // Perform checks
  check_no_entry();
  check_yes_entry();
  check_word_1();

  // Remove temp files
  tmpin.close();
  tmpout.close();
  remove(inf_name.c_str());
  remove(outf_name.c_str());
  
  unit::print_end("lz78_unit");
}

void lz78_unit::open_streams()
{
  if (!tmpin.is_open()) {
    tmpin.open(inf_name, std::ifstream::app);
  }
  if (!tmpout.is_open()) {
    tmpout.open(outf_name, std::ofstream::app);
  }
}

void lz78_unit::close_streams()
{
  if (tmpin.is_open()) {
    tmpin.close();
  }
  if (tmpout.is_open()) {
    tmpout.close();
  }
}

void lz78_unit::destroy_streams()
{
  close_streams();
  tmpin.open(inf_name, std::ifstream::trunc);
  tmpout.open(outf_name, std::ofstream::trunc);
  close_streams();
}

void lz78_unit::reopen_streams()
{
  destroy_streams();
  open_streams();
}

void lz78_unit::open_manout()
{
  if (!manout.is_open()) {
    manout.open(inf_name, std::ofstream::app);
  }            
}

void lz78_unit::close_manout()
{
  if (manout.is_open()) {
    manout.close();
  }
}

void lz78_unit::open_manin()
{
  if (!manin.is_open()) {
    manin.open(outf_name, std::ofstream::app);
  }            
}

void lz78_unit::close_manin()
{
  if (manin.is_open()) {
    manin.close();
  }
}

  
void lz78_unit::check_no_entry()
{
  reopen_streams();
  
  // Execute the algorithm
  Alg::lz78(tmpin, tmpout, 0);
  
  unit::CHECK_TRUE("check_no_entry", tmpout.tellp() == 0);
}

void lz78_unit::check_yes_entry()
{
  destroy_streams();

  open_manout();

  ss << 'a';
  manout << ss.str();

  ss.clear();

  close_manout();
  
  open_streams();
  
  // Execute the algorithm
  Alg::lz78(tmpin, tmpout, 0);

  unit::CHECK_TRUE("check_yes_entry", tmpout.tellp() != 0);
}

void lz78_unit::check_word_1()
{
  destroy_streams();

  open_manout();

  ss << 'a';
  manout << ss.str();

  ss.clear();
  ss.flush();

  close_manout();
  
  open_streams();
  
  // Execute the algorithm
  Alg::lz78(tmpin, tmpout, 0);

  close_streams();

  open_manin();

  ss << manin.rdbuf();
  
  unit::CHECK_TRUE("check_word_1", ss.str() == std::string{'\0', 0, 0, 'a'});
  
  ss.clear();
  ss.flush();
}
  
}
