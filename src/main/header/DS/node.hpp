// ALG2-TP1 project header file
// DS module
// node class
// =============================================================
//
// Description:
// This class implements a simple node, that is tied to a static
//   map that associates string ids with actual strings, for the
//   the sake of efficiency.
////////////////////////////////////////////////////////////////

#ifndef NODE_H
#define NODE_H

#include <unordered_map>

namespace DS {

class node;
typedef std::unordered_map<char, node*>  umap;  
  
class node {
public:
  // Leaf
  node(const unsigned id, const unsigned begin, const unsigned len);
  node(const unsigned id, const unsigned begin, const unsigned len, const char c, node* const next);
  ~node();

  const unsigned get_str_id() noexcept(true) { return str_id; }  
  unsigned get_begin() noexcept(true) { return str_begin; }
  unsigned get_len() noexcept(true) { return str_len; }
  
  umap* get_next() noexcept(true) { return next; }
  umap* get_fresh();
  void insert(std::pair<char, node*> cn);
  bool empty() noexcept(true) { return next == nullptr || next->empty(); }
  node* at(const char c) noexcept(false);

private:
  // Three unsigned integers to reference which string is kept in the node, for
  //  memory efficiency.
  const unsigned str_id; // Never changes
  unsigned str_begin;
  unsigned str_len;
  
  umap* next;

};

}

#endif
