// ALG2-TP1 project applance file
// Utils module
// unit class
// =============================================================
////////////////////////////////////////////////////////////////

#include "Utils/unit.hpp"

#include "Utils/error.hpp"

namespace Utils {

void unit::CHECK_TRUE(const std::string annotation, const bool t_stm)
{
  CHECK(annotation, t_stm);
}

void unit::CHECK_FALSE(const std::string annotation, const bool t_stm)
{
  CHECK(annotation, !t_stm);
}

void unit::CHECK(const std::string annotation, const bool t_stm)
{
  if (!t_stm) {
    error(unit_test_failure{annotation}, "Not fatal");
  }
}
  
}
