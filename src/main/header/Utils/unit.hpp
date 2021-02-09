// ALG2-TP1 project header file
// Utils module
// unit class
// =============================================================
// Description:
// This is a crude implementation of an unit test framework
////////////////////////////////////////////////////////////////

#ifndef UNIT_H
#define UNIT_H 1

#include "Utils/error.hpp"

#include <exception>
#include <string>
#include <typeinfo>

namespace Utils {

#define EQ_TYPE(e1, e2) (typeid(e1) == typeid(e2))
  
// Calls CHECK(annotation, stm), with stm being the vality of the fact t_func throws e1
#define CHECK_THROWS(ann, f, e1, ...) try { (*f)(__VA_ARGS__); Utils::unit::CHECK(ann, false); } \
  catch (const std::exception& e2) { Utils::unit::CHECK(ann, EQ_TYPE(e1, e2)); } \
  catch (const Utils::graceful_terminate& e2) { Utils::unit::CHECK(ann, EQ_TYPE(e1, e2)); }

#define CHECK_NO_THROW(ann, f, ...) try { (*f)(__VA_ARGS__); \
    Utils::unit::CHECK(ann, true); }                        \
  catch (const std::exception& e2) { Utils::unit::CHECK(ann, false); } \
  catch (const Utils::graceful_terminate& e2) { Utils::unit::CHECK(ann, false); }
  
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
  // Useful for startup and finish of unit testing classes
  static void print_start(const char* annotation);
  static void print_end(const char* annotation);
  
  static void CHECK_TRUE(const std::string annotation, const bool t_stm);
  static void CHECK_FALSE(const std::string annotation, const bool t_stm);
  
  // Routines used inside of the class for unit testing
  static void CHECK(const std::string, const bool t_stm);

};
  

}

#endif
