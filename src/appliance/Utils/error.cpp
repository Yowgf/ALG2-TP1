// ALG2-TP1 project header file
// Utils module
// error class
// ====================================
//
// Description:
// Class that implements errors found in the
//   project.
////////////////////////////////////////////////////////////////

#include "Utils/error.hpp"

#include <iostream>

namespace Utils {

// Static members definition
int error::error_code = 0;

//:D
error::error(std::exception& e, const char* t_type)
{
	error(e, std::string(t_type));
}

//:D
error::error(std::exception& e, const std::string t_type)
{
	if(!t_type.compare("Inst terminate")) 
		inst_term_error(e);
	else if(!t_type.compare("Fatal"))
		fatal_error(e);
	else if (!t_type.compare("Not fatal"))
		not_fatal_error(e);
	else
		fatal_error(e = std::invalid_argument(std::string("Unknown error ") += t_type));
}

//:D
void error::inst_term_error(std::exception& e)
{
	std::cerr << std::endl << e.what() << std::endl;
	std::cerr << "Fatal error, instantly terminating program..." << std::endl;
	exit(1);
}

//:D
void error::fatal_error(std::exception& e)
{
	std::cerr << std::endl << e.what() << std::endl;
	std::cerr << "Fatal error, terminating program..." << std::endl;
	error_code = 1;
}

//:D
void error::not_fatal_error(std::exception& e)
{
	std::cerr << std::endl;
	std::cerr << "Encountered not fatal error during execution:" << std::endl;
	std::cerr << std::string(10, '~') << std::endl;
	std::cerr << e.what() << std::endl;
	std::cerr << std::endl;
	std::cerr << std::string(10, '~') << std::endl;
}

}
