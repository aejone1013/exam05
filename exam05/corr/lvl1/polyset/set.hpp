#pragma once
#include "searchable_bag.hpp"
class set {
private:
	searchable_bag* bag;
public:
	set(searchable_bag* bag) : bag(bag) {}
	set(searchable_bag& bag) : bag(&bag) {}
	set(const set& other) : bag(other.bag) {}
	virtual ~set() {}
	set& operator=(const set& other) { if (this != &other) bag = other.bag; return *this; }
	void insert(int value) { if (!bag->has(value)) bag->insert(value); }
	void insert(int* values, int size) {
		if (!values || size <= 0) return;
		for (int i = 0; i < size; i++) if (!bag->has(values[i])) bag->insert(values[i]);
	}
	searchable_bag& get_bag() { return *bag; }
	const searchable_bag& get_bag() const { return *bag; }
	bool has(int value) const { return bag->has(value); }
	void print() const { bag->print(); }
	void clear() { bag->clear(); }
};
