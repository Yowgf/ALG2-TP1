// ALG2-TP1 project header file
// DS module
// node class
// =============================================================
////////////////////////////////////////////////////////////////

#include "DS/node.hpp"

namespace DS {

node::node(const std::string p_value, node* const p_node) : value(p_value)
{
  if (p_node != nullptr) {
    next.insert( {p_node->get_value()->at(0), p_node} );
  }
}

node::~node() 
{
  next.clear();
}  
  
}
