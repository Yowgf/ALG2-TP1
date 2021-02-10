// ALG2-TP1 project appliance file
// Interface module
// init class
// =============================================================
////////////////////////////////////////////////////////////////

#include "Interface/init.hpp"

#include "Alg/lz78.hpp"
#include "Utils/error.hpp"

#include <codecvt>
#include <locale>

namespace Interface {

init::init(int argc, char** argv)
{
  // Exceptions in this level can be fatal, because the entries of the
  //   algorithm are incorrect.
  try {
    process_entries(argc, argv);
  }
  catch (const invalid_cmd_entries& e) {
    Utils::error(e, "Fatal");
  }
  catch (const unable_open_file& e) {
    Utils::error(e, "Fatal");
  }
  catch (const unable_convert_files& e) {
    Utils::error(e, "Fatal");
  }
  catch (const std::exception& e) {
    Utils::error(e, "Not fatal");
  }

  try {
    #if 0
    Alg::lz78{in_file, out_file, is_comp_decomp};
    #endif
  }
  catch (const std::exception& e) {
    // Exceptions not handled inside the algorithm are obviously fatal errors
    Utils::error(e, "Fatal");
  }
  
}

init::~init()
{
  try {
    if (in_file.is_open()) {
      in_file.close();
    }
    if (out_file.is_open()) {
      out_file.close();
    }
  }
  catch (const std::ios_base::failure& e) {
    Utils::error(e, "Not Fatal");
  }
}

void init::process_entries(int argc, char** argv) noexcept(false)
{
  #if INIT_DEBUG == 1
  std::cerr << "Entering init::process_entries\n";
  #endif
  // - Compression
  //	./<program> -c <in-file> [-o <out-file>]
  //
  // - Decompression
  //	./<program> -x <in-file> [-o <out-file>]
  //
  // Validate arguments and open files
  try {
    if (argc != has_in_file && argc != has_out_file) {
      throw invalid_cmd_entries{};
    }
    std::string option_in = "";
    std::string option_out = "";
    std::string in_file_name = "";
    std::string out_file_name = "";
    if (argc >= has_in_file) {
      // The first argument should be discarded
      // The second argument is the option
      option_in = argv[1];
      
      // The third argument is the input file
      in_file_name = argv[2];

      // <-c|-x> <in-file>
      if (!option_in.compare("-c")) {
        is_comp_decomp = false;
      }
      else if (!option_in.compare("-x")) {
        is_comp_decomp = true;
      }
      else {
        throw invalid_cmd_entries{};
      }

      in_file.open(in_file_name);
      if (!in_file.is_open()) {
        throw unable_open_file{in_file_name};
      }

    }
    if (argc == has_out_file) {
      // The fourth argument is the -o option
      option_out = argv[3];
      
      // The fifth argument is the output file
      out_file_name = argv[4];

      // -o <out-file>
      if (option_out.compare("-o")) {
        throw invalid_cmd_entries{};
      }

      if (!out_file_name.compare("")) {
        // Default value
        out_file_name = basename(in_file_name);
      }
        
      out_file.open(out_file_name, std::ofstream::trunc);
      if (!out_file.is_open()) {
        throw unable_open_file{out_file_name};
      }

    }
    #if INIT_DEBUG == 1
    std::cerr << "Validated arguments\n";
    #endif
  }
  catch (const invalid_cmd_entries& e) {
    throw;
  }
  catch (const unable_open_file& e) {
    throw;
  }
  catch (const std::exception& e) {
    throw invalid_cmd_entries{};
  }

  try {
    // Convert the files to utf8
    convert_to_utf8();
  }
  catch (const std::exception& e) {
    throw unable_convert_files{};
  }
  
  #if INIT_DEBUG == 1
  std::cerr << "Leaving init::process_entries\n";
  #endif
}

std::string init::basename(const std::string& name) const noexcept(false) {
  unsigned len = name.length();
  unsigned i = 0;
  char c = '\0';
  // Just scan the string backwards until you reach '.'
  for (i = len - 1; i >= 0; --i) {
    c = name.at(i);
    if (c == '.') {
      --i;
      break;
    }          
  }
  return name.substr(0, i);
}

void init::convert_to_utf8()
{
  #if INIT_DEBUG == 1
  try {
    std::cerr << "Testing utf8 stream\n";
    utf8_out_file.open("boiteste.txt", std::wofstream::trunc);
    if (!utf8_out_file.is_open()) {
      throw unable_open_file{"boiteste.txt"};
    }
    std::cerr << "Opened file\n";
    utf8_out_file << "你好世界";
    std::cerr << "Inserted string\n";
    std::cerr << "stream state: "
              << utf8_out_file.good() << ' '
              << utf8_out_file.eof() << ' '
              << utf8_out_file.fail() << ' '
              << utf8_out_file.bad() << '\n';
    utf8_out_file.close();
    std::cerr << "Tested\n";
    std::cerr << "你好世界" << '\n';
    std::cerr << std::cerr.getloc().name() << '\n';
  }
  catch (const std::exception& e) {
    std::cerr << "Oops something happened: " << e.what() << '\n';
  }
  #endif
  
}

  
}
