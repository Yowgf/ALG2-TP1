// ALG2-TP1 project appliance
// DS module
// ctrie_unit class
// =============================================================
////////////////////////////////////////////////////////////////

#include "DS/ctrie_unit.hpp"

#include "DS/ctrie.hpp"
#include "Utils/unit.hpp"

#include <string>

using namespace DS;
using namespace Utils;

namespace Unit_tests {

ctrie_unit::ctrie_unit()
{
  Utils::unit::print_start("ctrie_unit");

  check_empty();
  
  check_some_nodes_insertion_1();
  check_some_nodes_insertion_3_equal();
  check_some_nodes_insertion_3_diff();

  check_some_nodes_pivot_empty();
  check_some_nodes_pivot_1();
  check_some_nodes_pivot_2_equal();
  check_some_nodes_pivot_3_diff();
  check_some_nodes_pivot_8_diff();
  check_some_nodes_pivot_15_diff();
  check_some_nodes_pivot_33_diff();
  
  Utils::unit::print_end("ctrie_unit");
}

void ctrie_unit::check_empty()
{
  ctrie test_ctrie = ctrie{};

  unit::CHECK_TRUE("check_empty", test_ctrie.get_len() == 1); 
}

void ctrie_unit::check_some_nodes_insertion_1()
{
  ctrie test_ctrie = ctrie{};

  test_ctrie.insert('a');
  
  unit::CHECK_TRUE("check_some_nodes_insertion_1", test_ctrie.get_len() == 2);
}

void ctrie_unit::check_some_nodes_insertion_3_equal()
{
  ctrie test_ctrie = ctrie{};

  test_ctrie.insert('a');
  test_ctrie.insert('a');
  test_ctrie.insert('a');

  unit::CHECK_TRUE("check_some_nodes_insertion_3_equal", test_ctrie.get_len() == 2);
}

void ctrie_unit::check_some_nodes_insertion_3_diff()
{
  ctrie test_ctrie = ctrie{};

  test_ctrie.insert('a');
  test_ctrie.insert('b');
  test_ctrie.insert('c');

  unit::CHECK_TRUE("check_some_nodes_insertion_3_diff", test_ctrie.get_len() == 2);
}

void ctrie_unit::check_some_nodes_pivot_empty()
{
  ctrie test_ctrie = ctrie{};

  unit::CHECK_TRUE("check_some_nodes_pivot_empty", test_ctrie.get_pivot_str() == std::string{});
}
  
void ctrie_unit::check_some_nodes_pivot_1()
{
  ctrie test_ctrie = ctrie{};

  test_ctrie.insert('a');
  
  unit::CHECK_TRUE("check_some_nodes_pivot_1", test_ctrie.get_pivot_str() == std::string{'a'});
}

void ctrie_unit::check_some_nodes_pivot_2_equal()
{
  ctrie test_ctrie = ctrie{};

  test_ctrie.insert('a');
  test_ctrie.insert('a');

  unit::CHECK_TRUE("check_some_nodes_pivot_2_equal", test_ctrie.get_pivot_str() == std::string{'a', 'a'});
}

void ctrie_unit::check_some_nodes_pivot_3_diff()
{
  ctrie test_ctrie = ctrie{};

  test_ctrie.insert('a');
  test_ctrie.insert('b');
  test_ctrie.insert('b');

  unit::CHECK_TRUE("check_some_nodes_pivot_3_diff", test_ctrie.get_pivot_str() == std::string{'a', 'b', 'b'});
}

void ctrie_unit::check_some_nodes_pivot_8_diff()
{
  ctrie test_ctrie = ctrie{};

  test_ctrie.insert('b');
  test_ctrie.insert('o');
  test_ctrie.insert('i');
  test_ctrie.insert(' ');
  test_ctrie.insert('b');
  test_ctrie.insert('o');
  test_ctrie.insert('b');
  test_ctrie.insert('o');

  unit::CHECK_TRUE("check_some_nodes_pivot_8_diff", test_ctrie.get_pivot_str() == std::string{'b', 'o'});
}

void ctrie_unit::check_some_nodes_pivot_15_diff()
{
  ctrie test_ctrie = ctrie{};

  test_ctrie.insert('b');
  test_ctrie.insert('o');
  test_ctrie.insert('i');
  test_ctrie.insert(' ');
  test_ctrie.insert('b');
  test_ctrie.insert('o');
  test_ctrie.insert('b');
  test_ctrie.insert('a');
  test_ctrie.insert('o');
  test_ctrie.insert(' ');
  test_ctrie.insert('b');
  test_ctrie.insert('a');
  test_ctrie.insert('b');
  test_ctrie.insert('a');
  test_ctrie.insert('o');

  unit::CHECK_TRUE("check_some_nodes_pivot_15_diff", test_ctrie.get_pivot_str() == std::string{'a', 'b', 'a', 'o'});
  
}
  
void ctrie_unit::check_some_nodes_pivot_33_diff()
{
  ctrie test_ctrie = ctrie{};

  test_ctrie.insert('s');
  test_ctrie.insert('h');
  test_ctrie.insert('e');
  test_ctrie.insert(' ');
  test_ctrie.insert('s');
  test_ctrie.insert('e');
  test_ctrie.insert('l');
  test_ctrie.insert('l');
  test_ctrie.insert('s');
  test_ctrie.insert(' ');
  test_ctrie.insert('s');
  test_ctrie.insert('e');
  test_ctrie.insert('a');
  test_ctrie.insert(' ');
  test_ctrie.insert('s');
  test_ctrie.insert('h');
  test_ctrie.insert('e');
  test_ctrie.insert('l');
  test_ctrie.insert('l');
  test_ctrie.insert('s');
  test_ctrie.insert(' ');
  test_ctrie.insert('b');
  test_ctrie.insert('y');
  test_ctrie.insert(' ');
  test_ctrie.insert('t');
  test_ctrie.insert('h');
  test_ctrie.insert('e');
  test_ctrie.insert(' ');
  test_ctrie.insert('s');
  test_ctrie.insert('h');
  test_ctrie.insert('o');
  test_ctrie.insert('r');
  test_ctrie.insert('e');

  unit::CHECK_TRUE("check_some_nodes_pivot_33_diff", test_ctrie.get_pivot_str() == std::string{'o', 'r', 'e'});
}
  
}
