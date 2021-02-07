// ALG2-TP1 project header file
// Utils module
// error class
// =============================================================
//
// Description:
// Class that implements errors found in the
//   project.
////////////////////////////////////////////////////////////////

#include "Utils/error.hpp"

#include <exception>
#include <iostream>

namespace Utils {

// Static members definition
int error::error_code = 0;

std::stringstream error::ss;

int error::set_atexit_func = std::atexit(error::graceful_termination);
void (*error::set_term_handler)(void) = std::set_terminate(error::abrupt_termination);
  
error::error(const std::exception& e, const char* t_type) : error(e, std::string(t_type))
{}

error::error(const std::exception& e, const std::string t_type) : cur_e_msg(e.what())
{
  msg_before.clear();
  msg.clear();
  msg_after.clear();
  
 	if(!t_type.compare("Inst terminate")) {
		inst_term_error();
  }
	else if(!t_type.compare("Fatal")) {
		fatal_error();
  }
	else if (!t_type.compare("Not fatal")) {
		not_fatal_error();
  }
	else {
    cur_e_msg = std::string("Unknown error ") += t_type;
		not_fatal_error();
  }
}

//:D
[[noreturn]] void error::inst_term_error()
{
  error_code = 1;

  msg_before = std::string("\n");
  msg = cur_e_msg;
  msg_after = std::string("Fatal error, instantly terminating program\n");

  report();
  abrupt_termination();
}

//:D
void error::fatal_error()
{
	error_code = 2;

  msg_before = std::string("\n");
  msg = cur_e_msg;
  msg_after = std::string("\nFatal error, terminating program...\n");

  report();
  throw graceful_terminate{};
}

//:D
void error::not_fatal_error()
{
  error_code = 3;

  msg_before = std::string(
                           "\n Encountered not fatal error during execution:"
                           "\n"
                           "\n")
    +=  std::string(10, '~')
    +=  "\n";
  msg = cur_e_msg;
  msg_after = std::string(std::string(10, '~') += "\n");
  report();
}

void error::report() {
  ss << "Error code: " << error_code << std::endl;
  ss << msg_before;
  ss << cur_e_msg;
  ss << msg_after;
}

void error::graceful_termination()
{
  ss << '\n'
     << std::string(40, '~') << '\n'
     << "Program terminated gracefully\n"
     << "Final error code: " << error_code << '\n';
  std::cerr << ss.str();
  ss.clear();
}

[[noreturn]] void error::abrupt_termination() {
  std::cerr << ss.str();
  ss.clear();
  std::abort();
}
  
}
