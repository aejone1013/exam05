#ifndef TREE_BAG_HPP
#define TREE_BAG_HPP

#include "bag.hpp"

class tree_bag: virtual public bag {
	protected:
		struct node {
			int value;
			node* l;
			node* r;
		};
		node* tree;

	public:
		tree_bag();
		tree_bag(const tree_bag& other);
		~tree_bag();
		tree_bag& operator=(const tree_bag& other);

		node* extractTree();
		void setTree(node*);
		virtual void insert(int);
		virtual void insert(int* array, int size);
		virtual void print() const;
		virtual void clear();

	private:
		static void destroyTree(node*);
		static void printNode(node*);
		static node *copyNode(node*);
};

#endif
