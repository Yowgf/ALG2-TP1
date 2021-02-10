// ALG2-TP1 project header file
// DS module
// ctrie class
// =============================================================
//
// Description:
// This class implements a compact trie
////////////////////////////////////////////////////////////////

#ifndef CTRIE_H
#define CTRIE_H 1

#include "DS/node.hpp"

#define CTRIE_DEBUG 0

#if CTRIE_DEBUG == 1
#include "Utils/error.hpp"

#include <iostream>
#endif

namespace DS {

typedef std::tuple<node*, node*> npair;
typedef std::unordered_map<unsigned, std::string*> smap;
  
class ctrie {
public:
  ctrie();
  ~ctrie();

  unsigned insert(const char c) noexcept(false);
  unsigned get_len() noexcept(true) { return len; }
  node* get_pivot() noexcept(true) { return pivot_node; }

  // Mainly for debugging purpopses
  std::string get_pivot_str() { return strmap->at(pivot_str_id)->substr(pivot_begin, pivot_len); }

  // Map containing 
  smap* strmap;
  
private:
  void destroy_strmap();
  unsigned len; // Used to identify strings. Only changed in create_new_leaf
  node* const root_node;
  
  node* pivot_node; // Node itself
  unsigned pivot_str_id;
  unsigned pivot_begin;
  unsigned pivot_len;
  
  unsigned pivot_cpos; // position on the string of the node it points to
  std::string* pivot_str;
  
  bool new_leaf; // Tells if pivot_node is constructing new leaf

  // For leaf creation. ~len~ is incremented
  node* create_new_leaf(const char c);  
  
  // Auxiliary functions for insertion
  
  void insert_root(const char c);
  void insert_new_leaf(const char c);
  void insert_old_leaf(const char c);
  void insert_internal(const char c);

  // Go one level further, according to key c
  void deepen(const char c) noexcept(false);
  // Add a new child and forward to it
  void give_birth(const char c);
  // Branch leaf node into two new nodes
  void branch_leaf(const char c);
  // Very similar to procedure above
  void branch_internal(const char c);
  npair branch_create(const char c);
  void branch_assign(node* parent, npair& children);
  void branch_fix(node* right_child);
  
  // Update pivot node to the node provided, and make necessary adjustments
  void pivot_update(node* const, const unsigned pos);
  
  // Recursively destroy the tree
  void rec_destructor(node*);
};
  
}

#endif
