// ALG2-TP1 project header file
// Utils module
// error class
// ============================
//
// Description:
// Class that implements errors found in the project.
////////////////////////////////////////////////////////////////

#ifndef ERROR_H
#define ERROR_H 1

#include <sstream>
#include <stdexcept>
#include <string>

namespace Utils {

class graceful_terminate{};
  
class error {
public:
	static int error_code;
  
  error(const std::exception&, const char*);
  error(const std::exception&, const std::string);
  
private:
  // Simple auxiliary function. The error code is the most severe
  // thing error that occurred during the program's execution
  static void update_error_code(int new_code);
  
	// In decreasing order of severity, and in increasing order of error code
	// Instantly terminates program execution, after
	//   printing message (should be avoided).
	[[noreturn]] void inst_term_error();
	// Fatal error, the program should then deallocate memory and
	//   terminate the program in a non-abrupt fashion.
	void fatal_error();
	// Not a fatal error, just print a message.
	void not_fatal_error();

  // Auxiliary functions
  void report();

  // Returns to the calling process by throwing a termination exception, that
  //   is to be caught at main. This allows correct deallocation of objects.
  static void graceful_termination();
  // Instantly terminate (not recommended)
  [[noreturn]] static void abrupt_termination();

  // Standard way to construct an error
  std::string msg_before;
  std::string msg;
  std::string msg_after;

  // Current exception
  std::string cur_e_msg;
  
  // For string manipulations
  static std::stringstream ss; // Hold all accumulated messages so far
  static int set_atexit_func;
  static void (*set_term_handler)(void);

};

}

#endif
