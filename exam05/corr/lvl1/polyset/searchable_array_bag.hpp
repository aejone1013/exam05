#pragma once
#include "array_bag.hpp"
#include "searchable_bag.hpp"
class Searchablearray_bag : public array_bag, public searchable_bag {
public:
	Searchablearray_bag() : array_bag() {}
	Searchablearray_bag(const Searchablearray_bag& other) : array_bag(other) {}
	~Searchablearray_bag() {}
	Searchablearray_bag& operator=(const Searchablearray_bag& other) {
		if (this != &other)
			array_bag::operator=(other);
		return *this;
	}
	virtual bool has(int value) const {
		for (int i = 0; i < _size; ++i) if (_data[i] == value) return true;
		return false;
	}
};
