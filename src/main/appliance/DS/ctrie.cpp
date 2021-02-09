// ALG2-TP1 project appliance file
// DS module
// ctrie class
// =============================================================
////////////////////////////////////////////////////////////////

#include "DS/ctrie.hpp"

#include "Utils/error.hpp"

#include <iostream>
#include <stdexcept>
#include <tuple>

namespace DS {
  
ctrie::ctrie() : strmap(new smap{}), len(0), root_node(create_new_leaf('\0')),
                 pivot_node(root_node), pivot_str_id(0),
                 pivot_begin(0), pivot_len(0), pivot_cpos(0), new_leaf(false)
{
  
  pivot_str = strmap->at(pivot_str_id);
}

ctrie::~ctrie()
{
  destroy_strmap();
  // Delete the whole tree recursively (the recursive call is implicit)
  rec_destructor(root_node);
}

void ctrie::destroy_strmap()
{
  // Delete each string in the map
  smap::iterator it = strmap->begin();
  smap::iterator ti = strmap->end();
  for (; it != ti; ++it) {
    delete it->second;
  }
  delete strmap;
}

void ctrie::rec_destructor(node* cur_node)
{
  if (cur_node != nullptr) {
    umap* node_map = cur_node->get_next();
    if (node_map == nullptr) {
      delete cur_node;
      return;
    }
    umap::iterator it = node_map->begin();
    umap::iterator ti = node_map->end();
    for (; it != ti; ++it) {
      rec_destructor(it->second);
    }
    delete cur_node;
  }
}
  
void ctrie::insert(const char c) noexcept(false)
{
  if (pivot_node == nullptr) {
    throw std::logic_error("pivot_node nullptr");
  }
  if (c == '\0') {
    throw std::invalid_argument("Character can not be '\\0'!");
  }
  #if CTRIE_DEBUG == 1
  std::cerr << "Inserting character " << c << '\n';
  #endif

  // Case root
  if (pivot_node == root_node) {
    insert_root(c);
  }
  else if (new_leaf) {
    insert_new_leaf(c);
  }
  else if (pivot_node->empty()) { // Not new, but a leaf
    insert_old_leaf(c);
  }
  else { // Internal node
    insert_internal(c);
  }
  #if CTRIE_DEBUG == 1
  std::cerr << "Leaving insert.\n";
  #endif
}

node* ctrie::create_new_leaf(const char c)
{
  #if CTRIE_DEBUG == 1
  LOG("Entering create_new_leaf");
  #endif
  
  // create new string in map using just the character provided
  std::string* new_str = new std::string{c};
  
  strmap->insert( {len, new_str} );

  node* new_child = new node{len, 0, 1};
  len += 1;
  
  return new_child;
}

void ctrie::insert_root(const char c)
{
  if (c != ' ') {
    deepen(c);
  }
}

void ctrie::insert_new_leaf(const char c)
{
  #if CTRIE_DEBUG == 1
  LOG("In new leaf");
  #endif
  if (c != ' ') {
    pivot_str->push_back(c);
  #if CTRIE_DEBUG == 1
    LOGA("Current pivot_str", *pivot_str);
  #endif
    pivot_cpos += 1;
    pivot_len += 1;
  }
  else {
    pivot_str->push_back('\0');
    pivot_update(root_node, 0); // Go back to the beggining
    new_leaf = false;
  }
}

void ctrie::insert_old_leaf(const char c)
{
  #if CTRIE_DEBUG == 1
  LOG("Entering old_leaf");
  #endif
  // Don't need to consider case when pivot_cpos is just at the tip of pivot_str,
  //  because having '\0' there naturally covers that case in the conditional
  //  below.
  if (c == pivot_str->at(pivot_cpos)) {
    pivot_cpos += 1;
  }
  else {
    branch_leaf(c);
  }
}

void ctrie::insert_internal(const char c)
{
  // Have to take into account reassignment of nodes from parent to child
  if (pivot_cpos == pivot_begin + pivot_len) {
    deepen(c);
  }
  else if (c == pivot_str->at(pivot_cpos)) {
    pivot_cpos += 1;
  }
  else {
    branch_internal(c);
  }
}

void ctrie::deepen(const char c) noexcept(false)
{
  #if CTRIE_DEBUG == 1
  LOG("Entering deepen");
  #endif
  try {
    pivot_update(pivot_node->at(c), 1); // may throw out_of_range
  }
  catch (const std::out_of_range& e) {
    give_birth(c);
  }
}

void ctrie::give_birth(const char c)  
{
  #if CTRIE_DEBUG == 1
  LOG("Entering give_birth");
  #endif
  // Brand new string, generate next id
  node* new_child = create_new_leaf(c);
  
  pivot_node->insert(std::make_pair(c, new_child));

  new_leaf = true;
  pivot_update(new_child, 1); // Start at second character
}  
  
void ctrie::branch_leaf(const char c)
{
  #if CTRIE_DEBUG == 1
  LOG("Entering branch_leaf");
  #endif
  
  npair children = branch_create(c);
  
  branch_assign(pivot_node, children);
  branch_fix(std::get<1>(children));
}

void ctrie::branch_internal(const char c)
{
  #if CTRIE_DEBUG == 1
  LOG("Entering branch_internal");
  #endif
  npair children = branch_create(c);

  // Assign old children to left child
  umap* pn_next = pivot_node->get_fresh();
  std::get<0>(children)->get_fresh()->swap(*pn_next);
  
  branch_assign(pivot_node, children);
  branch_fix(std::get<1>(children));
}

npair ctrie::branch_create(const char c)
{
  #if CTRIE_DEBUG == 1
  LOG("Entering branch_create");
  #endif

  node* left_child = new node{pivot_str_id, pivot_cpos, pivot_len - pivot_cpos};
  node* right_child = create_new_leaf(c);
  
  return std::make_tuple(left_child, right_child);
}

void ctrie::branch_assign(node* parent, npair& children)
{
  #if CTRIE_DEBUG == 1
  LOG("Entering branch_assign");
  #endif
  node* lc = std::get<0>(children);
  node* rc = std::get<1>(children);
  
  std::string* lc_str = strmap->at(lc->get_str_id());
  std::string* rc_str = strmap->at(rc->get_str_id());
  
  pivot_node->insert(std::make_pair(lc_str->at(lc->get_begin()), lc));
  pivot_node->insert(std::make_pair(rc_str->at(rc->get_begin()), rc));
}
  
void ctrie::branch_fix(node* right_child)
{
  #if CTRIE_DEBUG == 1
  LOG("Entering branch_fix");
  #endif
  // Fix pivot_str
  *pivot_str = pivot_str->substr(pivot_begin, pivot_cpos);

  pivot_update(right_child, 1); // Forward to new right child
  new_leaf = true;
}
  
void ctrie::pivot_update(node* const new_node, const unsigned pos)
{
  #if CTRIE_DEBUG == 1
  LOG("Entering pivot_update");
  #endif
  pivot_node = new_node;
  
  pivot_str_id = pivot_node->get_str_id();
  pivot_begin = pivot_node->get_begin();
  pivot_cpos = pivot_begin + pos;
  pivot_len = pivot_node->get_len();
    
  pivot_str = strmap->at(pivot_str_id);
}
  
}
