#pragma once
#include "searchable_bag.hpp"

class set {
private:
    // 실제 저장은 searchable_bag에 맡긴다.
    searchable_bag* bag;
public:
    set(searchable_bag* bag) : bag(bag) {}
    set(searchable_bag& bag) : bag(&bag) {}
    set(const set& other) : bag(other.bag) {}
    virtual ~set() {}
    set& operator=(const set& other)
    {
        if (this != &other) bag = other.bag;
        return *this;
    }
    void insert(int value)
    {
        // 이미 있으면 넣지 않는다.
        if (!bag->has(value))
            bag->insert(value);
    }
    void insert(int* values, int size)
    {
        if (!values || size <= 0)
            return;
        for (int i = 0; i < size; i++)
        {
            if (!bag->has(values[i]))
                bag->insert(values[i]);
        }
    }
    bool has(int value) const
    {
        return bag->has(value);
    }
    void print() const 
    {
        bag->print();
    }
    void clear()
    {
        bag->clear();
    }
};
