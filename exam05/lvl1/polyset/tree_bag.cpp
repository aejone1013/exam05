#include "tree_bag.hpp"
#include <iostream>

tree_bag::tree_bag() : tree(NULL) {}

tree_bag::tree_bag(const tree_bag& other) : tree(copyNode(other.tree)) {}

tree_bag::~tree_bag() {
clear();
}

tree_bag& tree_bag::operator=(const tree_bag& other) {
if (this != &other) {
clear();
tree = copyNode(other.tree);
}
return *this;
}

tree_bag::node* tree_bag::extractTree() {
node* temp = tree;
tree = NULL;
return temp;
}

void tree_bag::setTree(node* newtree) {
clear();
tree = newtree;
}

void tree_bag::insert(int value) {
    node** current = &tree;
    // 삽입 위치가 나올 때까지 내려간다.
    while (*current) {
        if (value < (*current)->value) {
            current = &((*current)->l);
        } else {
            // 중복 값은 오른쪽으로 보낸다.
            current = &((*current)->r);
        }
    }
    *current = new node();
    (*current)->value = value;
    (*current)->l = NULL;
    (*current)->r = NULL;
}

void tree_bag::insert(int* array, int size) {
for (int i = 0; i < size; ++i) {
insert(array[i]);
}
}

void tree_bag::print() const {
printNode(tree);
std::cout << std::endl;
}

void tree_bag::clear() {
destroyTree(tree);
tree = NULL;
}

void tree_bag::destroyTree(node* Node) {
if (Node) {
// 자식부터 지우는 후위 순회
destroyTree(Node->l);
destroyTree(Node->r);
delete Node;
}
}

void tree_bag::printNode(node* Node) {
if (Node) {
printNode(Node->l);
std::cout << Node->value << " ";
printNode(Node->r);
}
}

tree_bag::node* tree_bag::copyNode(node* node) {
    if (!node) return NULL;
    // 노드를 공유하지 않도록 깊은 복사
    tree_bag::node* newNode = new tree_bag::node();
    newNode->value = node->value;
    newNode->l = copyNode(node->l);
    newNode->r = copyNode(node->r);
    return newNode;
}
