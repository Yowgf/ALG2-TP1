// ALG2-TP1 project header file
// DS module
// ctrie_unit class
// =============================================================
//
// Description:
// ctrie class unit tests
////////////////////////////////////////////////////////////////

#ifndef CTRIE_UNIT_H
#define CTRIE_UNIT_H 1

namespace Unit_tests {

class ctrie_unit {
public:
  ctrie_unit();
  
private:
  // Creates a new empty ctrie, and see if all goes well
  void check_empty();

  // Creates a ctrie and manipulates it to insert some nodes
  void check_some_nodes_insertion_1();
  void check_some_nodes_insertion_3_equal();
  void check_some_nodes_insertion_3_diff();

  // Deal with the node being inserted in the right place
  void check_some_nodes_pivot_empty();
  void check_some_nodes_pivot_1();
  void check_some_nodes_pivot_2_equal();
  void check_some_nodes_pivot_3_diff();
  void check_some_nodes_pivot_8_diff();
  void check_some_nodes_pivot_15_diff();
  void check_some_nodes_pivot_33_diff();
};

}

#endif
