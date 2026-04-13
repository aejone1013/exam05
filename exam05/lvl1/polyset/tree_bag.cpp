#include "tree_bag.hpp"
#include <iostream>
tree_bag::tree_bag() : tree(NULL) {}
tree_bag::tree_bag(const tree_bag& other) : tree(copyNode(other.tree)) {}
tree_bag::~tree_bag() { clear(); }
tree_bag& tree_bag::operator=(const tree_bag& other) {
	if (this != &other) { clear(); tree = copyNode(other.tree); }
	return *this;
}
tree_bag::node* tree_bag::extractTree() { node* t = tree; tree = NULL; return t; }
void tree_bag::setTree(node* n) { clear(); tree = n; }
void tree_bag::insert(int value) {
	node** cur = &tree;
	while (*cur) cur = (value < (*cur)->value) ? &(*cur)->l : &(*cur)->r;
	*cur = new node(); (*cur)->value = value; (*cur)->l = (*cur)->r = NULL;
}
void tree_bag::insert(int* array, int size) { for (int i = 0; i < size; i++) insert(array[i]); }
void tree_bag::print() const { printNode(tree); std::cout << std::endl; }
void tree_bag::clear() { destroyTree(tree); tree = NULL; }
void tree_bag::destroyTree(node* n) { if (n) { destroyTree(n->l); destroyTree(n->r); delete n; } }
void tree_bag::printNode(node* n) { if (n) { printNode(n->l); std::cout << n->value << " "; printNode(n->r); } }
tree_bag::node* tree_bag::copyNode(node* n) {
	if (!n) return NULL;
	tree_bag::node* nn = new tree_bag::node();
	nn->value = n->value; nn->l = copyNode(n->l); nn->r = copyNode(n->r);
	return nn;
}
