// ALG2-TP1 project header file
// DS module
// node class
// =============================================================
////////////////////////////////////////////////////////////////

#include "DS/node.hpp"

#include "DS/ctrie.hpp"

namespace DS {

node::node(const unsigned id, const unsigned begin, const unsigned len) :
  str_id(id), str_begin(begin), str_len(len)
{
  next = nullptr;
}
  
node::node(const unsigned id, const unsigned begin, const unsigned len,
           const char next_c, node* const p_node) : node(id, begin, len)
{
  if (p_node != nullptr) {
    next = new umap{};
    next->insert( {next_c, p_node} );
  }
}
  
node::~node() 
{
  delete next;
}  

umap* node::get_fresh()
{
  if (next == nullptr) {
    next = new umap{};
  }
  return next;
}
  
void node::insert(std::pair<char, node*> cn)
{
  // Only create map if necessary
  if (next == nullptr) {
    next = new umap{};
  }
  next->insert( cn );
}

node* node::at(const char c) noexcept(false)
{
  if (next == nullptr) {
    throw std::out_of_range{"nullptr next"};
  }
  return next->at(c);
}
  
}
