// ALG2-TP1 project header file
// Utils module
// error class
// ============================
//
// Description:
// Class that implements errors found in the
//   project.
////////////////////////////////////////////////////////////////

#ifndef ERROR_H
#define ERROR_H 1

#include <stdexcept>
#include <string>

namespace Utils {

class error {
private:
	// In decreasing order of severity.
	// Instantly terminates program execution, after
	//   printing message (should be avoided).
	void inst_term_error(std::exception&);
	// Fatal error, the program should then deallocate memory and
	//   terminate the program in a non-abrupt fashion.
	void fatal_error(std::exception&);
	// Not a fatal error, just print a message.
	void not_fatal_error(std::exception&);

public:
	static int error_code;
	error(std::exception&, const char*);
	error(std::exception&, const std::string);
};

}

#endif
