// ALG2-TP1 project appliance file
// unit testing main
//
// Description:
// Here all the unit tests are incorporated into the main
//   function
/////////////////////////////////////////////////////////////////

#include "Utils/Utils.hpp"

#include "Alg/Alg_unit.hpp"
#include "DS/DS_unit.hpp"
#include "Interface/Interface_unit.hpp"
#include "Utils/Utils_unit.hpp"

#include <iostream>

using namespace Unit_tests;
int main() {
  try {
    init_unit{};
    ctrie_unit{};
    lz78_unit{};
  }
  catch (const Utils::graceful_terminate& e) {
    return Utils::error::error_code;
  }
  catch (const std::exception& e) {
    Utils::error(e, "Fatal");
  }

  return Utils::error::error_code;
}
