// ALG2-TP1 project header
// Alg_unit module
// lz78_unit class unit tests
// =============================================================
////////////////////////////////////////////////////////////////

#ifndef LZ78_UNIT_H
#define LZ78_UNIT 1

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

namespace Unit_tests {

class lz78_unit {
public:
  lz78_unit();
  
private:
  std::stringstream ss;
  std::ofstream manout;
  std::ifstream manin;
  
  std::ifstream tmpin;
  std::ofstream tmpout;
  const std::string inf_name = "tmpin.txt";
  const std::string outf_name = "tmpout.lz78";

  // Auxiliary functions
  void open_streams();
  void close_streams();
  void destroy_streams();
  void reopen_streams();

  void open_manin();
  void close_manin();
  void open_manout();
  void close_manout();

  // Checks
  void check_no_entry();
  void check_yes_entry();
  
  void check_word_1();
};

}

#endif
