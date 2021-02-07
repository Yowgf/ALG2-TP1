// ALG2-TP1 project header file
// Utils module
// unit class
// =============================================================
// Description:
// This is a crude implementation of an unit test framework
////////////////////////////////////////////////////////////////

#ifndef UNIT_H
#define UNIT_H 1

#include <exception>
#include <string>
#include <typeinfo>

namespace Utils {

// Calls CHECK(annotation, stm), with stm being the vality of the fact t_func throws e1
#define CHECK_THROWS(ann, f, e1, ...) try { (*f)(##__VA_ARGS) }\
  catch(const std::exception& e2) { Utils::unit::CHECK(ann, typeid(e1) == typeid(e2)) }
  
class unit_test_failure : public std::exception {
public:
  unit_test_failure(const char* problem) : unit_test_failure(std::string(problem)) {}
  unit_test_failure(const std::string problem) : problem(problem) {}
  const char* what() const throw()
  {
    return problem.c_str();
  }

private:
  std::string problem;
};

class unit {
public:
  // Routines useful for unit testing (e.g. check_true, check_throws, etc).
  void CHECK_TRUE(const std::string annotation, const bool t_stm);
  void CHECK_FALSE(const std::string annotation, const bool t_stm);
  
  // Routines used inside of the class for unit testing
  void CHECK(const std::string, const bool t_stm);

};
  

}

#endif
