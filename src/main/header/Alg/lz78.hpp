// ALG2-TP1 project header file
// Alg module
// lz78 class
// =============================================================
//
// Description:
// This is the class that receives the input and output file
//   references from the Interface module, as well as the
//   algorithm options (e.g. compression / decompression).
// It then performs compression or decompression on the input
//   file, sending the results to the output file.
////////////////////////////////////////////////////////////////

#ifndef LZ78_H
#define LZ78_H 1

#include "DS/ctrie.hpp"

#include <fstream>
#include <string>

namespace Alg {

// Algorithm currently incorrect
class lz78 {
public:
  lz78(std::ifstream& in, std::ofstream& out, bool is_comp_decomp);
  
private:
  std::ifstream& in;
  std::ofstream& out;

  DS::ctrie trie;
  std::unordered_map<unsigned int, std::string> strmap; // Auxiliary map of strings
  std::string cur_str;
  unsigned cur_str_id;
  
  void comp();
  void decomp();

  void dispatch_output(const char c);
};

}

#endif
