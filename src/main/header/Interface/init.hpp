// ALG2-TP1 project header file
// Interface module
// init class
// =============================================================
//
// Description:
// This is the class that interprets the command line arguments
//   received from the main function, and passes them to the
//   wanted algorithm.
////////////////////////////////////////////////////////////////

#ifndef INIT_H
#define INIT_H 1

#include <exception>
#include <fstream>

#define INIT_DEBUG 0
#if INIT_DEBUG == 1
#include <iostream>
#endif

namespace Interface {

class invalid_cmd_entries : public std::exception {
public:
  const char* what() const throw() override
  {
    return "\nUsage: <program> <-c|-x> <in-file> [-o <out-file>]";
  }
};

class unable_open_file : public std::exception {
  std::string problem;
public:
  unable_open_file(const char* file_name)
    : unable_open_file(std::string(file_name)) {}
  unable_open_file(std::string file_name)
    : problem(std::string("Unable to open file \"") += file_name += "\"\n") {}
  const char* what() const throw() override
  {
    return problem.c_str();
  }
};

class unable_convert_files : public std::exception {
public:
  const char* what() const throw() override
  {
    return "Unable to convert files to desired format\n";
  }
};
  
class init {
public:
  init(int argc, char** argv) noexcept(false);
  ~init();
  
private:
  // Checks validity of the entries, and performs any necessary
  //   preprocessing.
  void process_entries(int argc, char** argv) noexcept(false);
  
  // Auxilliary function - gets the basename of entry string
  std::string basename(const std::string&) const noexcept(false);

  // Converts a file to utf8 format
  void convert_to_utf8();
  
  // <program> <-c|-x> <in-file> [-o <out-file>]
  // enum indicating number of arguments possible
  enum {
        has_in_file = 3,
        has_out_file = 5
  };
  // false -> comp; true -> decomp
  bool is_comp_decomp;

  std::ifstream in_file;
  std::ofstream out_file;

  std::wifstream utf8_in_file;
  std::wofstream utf8_out_file;
};

}

#endif
