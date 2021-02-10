// ALG2-TP1 project header file
// Alg module
// lz78 class
// =============================================================
////////////////////////////////////////////////////////////////

#include "Alg/lz78.hpp"

namespace Alg {

lz78::lz78(std::ifstream& in, std::ofstream& out, bool is_comp_decomp)
  : in(in), out(out), cur_str_id(0)
{
  try {
    if (!is_comp_decomp) {
      comp();
    }
    else {
      decomp();
    }    
  }
  catch (std::exception& e) { // TODO
    throw;
  }
}

void lz78::comp()
{
  #if 0
  // Read input character by character
  char c = in.get();
  if (c != ' ') {
    cur_str.push_back(c);
  }
  while (in.good()) {
    c = in.get();

    // Insert character in trie until we have a space character
    if (c != ' ') {
      trie.insert(c);
    }
    else {
      dispatch_output(c);

      cur_str.clear();
      cur_str_id += 1;
    }   
    
  }
  #endif
}
  
void lz78::decomp()
{}

void lz78::dispatch_output(const char c)
{
  #if 0
  if (!cur_str.empty()) { // If it is empty, then we are at the root
    unsigned cur_breakpoint = trie.insert(c);

    // Add string to the map
    strmap.insert(std::make_pair(cur_str_id, cur_str));
    
    // Output in format "\0<N>,<N><str>[...]"
    out << '\0' << cur_str_id << ',' << cur_breakpoint << cur_str;
        
  }
  #endif
}
  
}
