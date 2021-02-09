// ALG2-TP1 project header file
// DS module
// node class
// =============================================================
//
// Description:
// This class implements a simple node
////////////////////////////////////////////////////////////////

#ifndef NODE_H
#define NODE_H

#include <unordered_map>

namespace DS {

class node;
typedef std::unordered_map<char, node*>  umap;
  
class node {
public:
  node(const char* p_value, node* const p_next) : node(std::string(p_value), p_next) {}
  node(const std::string p_value, node* const p_next);
  ~node();
  
  std::string* get_value() noexcept(true) { return &value; }
  std::string& get_valuer() noexcept(true) { return value; }
  umap& get_next() noexcept(true) { return next; }
private:
  std::string value;
  umap next;
};

}

#endif
