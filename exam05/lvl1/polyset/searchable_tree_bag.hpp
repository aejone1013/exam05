#pragma once
#include "tree_bag.hpp"
#include "searchable_bag.hpp"
class Searchabletree_bag : public tree_bag, public searchable_bag {
public:
	Searchabletree_bag() : tree_bag() {}
	Searchabletree_bag(const Searchabletree_bag& other) : tree_bag(other) {}
	~Searchabletree_bag() {}
	Searchabletree_bag& operator=(const Searchabletree_bag& other) {
		if (this != &other) tree_bag::operator=(other); return *this;
	}
	virtual bool has(int value) const {
		node* cur = tree;
		while (cur) {
			if (cur->value == value) return true;
			cur = (cur->value > value) ? cur->l : cur->r;
		}
		return false;
	}
};
