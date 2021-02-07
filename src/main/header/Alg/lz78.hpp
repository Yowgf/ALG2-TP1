// ALG2-TP1 project header file
// Alg module
// lz78 class
// =============================================================
//
// Description:
// This is the class that receives the input and output file
//   references from the Interface module, as well as the
//   algorithm options (e.g. compression / decompression)
////////////////////////////////////////////////////////////////

#ifndef LZ78_H
#define LZ78_H 1

#include <fstream>
#include <string>

namespace Alg {

class lz78 {
public:
  lz78(std::ifstream& in, std::ofstream& out, bool is_comp_decomp);
  
private:
  std::ifstream& in_file;
  std::ofstream& out_file;
  bool is_comp_decomp;

};

}

#endif
