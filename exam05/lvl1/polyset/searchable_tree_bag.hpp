#pragma once
#include "tree_bag.hpp"
#include "searchable_bag.hpp"

class Searchabletree_bag : public tree_bag, public searchable_bag {
public:
    Searchabletree_bag() : tree_bag() {}
    Searchabletree_bag(const Searchabletree_bag& other) : tree_bag(other) {}
    ~Searchabletree_bag() {}
    Searchabletree_bag& operator=(const Searchabletree_bag& other) {
        if (this != &other) tree_bag::operator=(other);
        return *this;
    }
    virtual bool has(int value) const {
        node* current = tree;
        // BST의 정렬 성질을 이용해 매 단계마다 탐색 범위를 절반씩 줄인다.
        while (current) {
            if (current->value == value) return true;
            current = (current->value > value) ? current->l : current->r;
        }
        return false;
    }
};
