// ALG2-TP1 project appliance file
// DS module
// ctrie class
// =============================================================
////////////////////////////////////////////////////////////////

#include "DS/ctrie.hpp"

#include <stdexcept>
#include <tuple>

namespace DS {

ctrie::ctrie() : len(0), root_node(new node{std::string{}, nullptr}),
                   pivot_node(root_node), pivot_str(pivot_node->get_value()),
                   pivot_pos(0), new_leaf(false)
{}

ctrie::~ctrie()
{
  // Delete the whole tree recursively (the recursive call is implicit)
  rec_destructor(root_node);
}  

void ctrie::rec_destructor(node* cur_node)
{
  if (cur_node != nullptr) {
    umap& node_map = cur_node->get_next();
    if (node_map.empty()) {
      delete cur_node;
      return;
    }
    umap::iterator it = node_map.begin();
    umap::iterator ti = node_map.end();
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
  else if (pivot_node->get_next().empty()) { // Not new, but a leaf
    insert_old_leaf(c);
  }
  else { // Internal node
    insert_internal(c);
  }
  #if CTRIE_DEBUG == 1
  std::cerr << "Leaving insert.\n";
  #endif
  len += 1;
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
  std::cerr << "In new leaf\n";
  #endif
  if (c != ' ') {
    pivot_str->push_back(c);
    pivot_pos += 1;
  }
  else {
    pivot_str->push_back('\0');
    pivot_new(root_node, 0); // Go back to the beggining
    new_leaf = false;
  }
}

void ctrie::insert_old_leaf(const char c)
{
  #if CTRIE_DEBUG == 1
  LOG("Entering old_leaf");
  #endif
  // Don't need to consider case when pivot_pos is just at the tip of pivot_str,
  //  because having '\0' there naturally covers that case in the conditional
  //  below.
  if (c == pivot_str->at(pivot_pos)) {
    pivot_pos += 1;
  }
  else {
    branch_leaf(c);
  }
}

void ctrie::insert_internal(const char c)
{
  // Have to take into account reassignment of nodes from parent to child
  if (pivot_pos == pivot_str->length()) {
    deepen(c);
  }
  else if (c == pivot_str->at(pivot_pos)) {
    pivot_pos += 1;
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
    pivot_new(pivot_node->get_next().at(c), 1); // may throw out_of_range
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
  node* new_child = new node{std::string{c}, nullptr};
  pivot_node->get_next().insert( {c, new_child} );

  new_leaf = true;
  pivot_new(new_child, 1); // Start at second character
}  
  
void ctrie::branch_leaf(const char c)
{
  npair children = branch_create(c);
  
  branch_assign(pivot_node, children);
  branch_fix(std::get<1>(children));
}

void ctrie::branch_internal(const char c)
{
  npair children = branch_create(c);

  // Assign old children to left child
  umap& pn_next = pivot_node->get_next();
  std::get<0>(children)->get_next().swap(pn_next);
  
  branch_assign(pivot_node, children);
  branch_fix(std::get<1>(children));
}

npair ctrie::branch_create(const char c)
{
  std::string lc_substr = pivot_str->substr(pivot_pos, pivot_str->length() - pivot_pos);
  node* left_child = new node{lc_substr, nullptr};
  node* right_child = new node{std::string{c}, nullptr};

  return std::make_tuple(left_child, right_child);
}

void ctrie::branch_assign(node* parent, npair& children)
{ 
  node* lc = std::get<0>(children);
  node* rc = std::get<1>(children);
  
  umap& pn_next = parent->get_next();  
  pn_next.insert( {lc->get_valuer().at(0), lc} );
  pn_next.insert( {rc->get_valuer().at(0), rc} );
}
  
void ctrie::branch_fix(node* right_child)
{
  // Fix pivot_str
  *pivot_str = pivot_str->substr(0, pivot_pos);

  pivot_new(right_child, 1); // Forward to new right child
  new_leaf = true;
}
  
void ctrie::pivot_new(node* const new_node, const unsigned pos)
{
  pivot_node = new_node;
  pivot_str = pivot_node->get_value();
  pivot_pos = pos;  
}
  
}
