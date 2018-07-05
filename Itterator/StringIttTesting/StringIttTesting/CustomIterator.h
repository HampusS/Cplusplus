#pragma once
#include <iostream>
#include <iterator>
#include <cassert>

template <typename T, int dir>
class BaseIterator : public std::iterator<std::random_access_iterator_tag, T> {
public:
	T* _ptr;
	int direction;
	virtual bool invariant() { return _ptr != nullptr; }

	// Constructors
	~BaseIterator() { _ptr = nullptr; }
	explicit BaseIterator() : direction(dir) {};
	explicit BaseIterator(T* ptr) :
		_ptr(ptr), direction(dir) {
		assert(invariant());
	}

	// Operators
	virtual bool operator==(const BaseIterator& rhs) { assert(invariant()); return _ptr == rhs._ptr; }
	virtual bool operator!=(const BaseIterator& rhs) { assert(invariant()); return _ptr != rhs._ptr; }
	virtual T& operator*() { assert(invariant()); return *_ptr; }
	virtual T* operator->() { assert(invariant()); return _ptr; }
	virtual T& operator[](int i) { assert(invariant()); return *(_ptr + (i * direction)); }

	virtual BaseIterator operator=(BaseIterator rhs) { _ptr = rhs._ptr; assert(invariant()); return *this; }
	virtual BaseIterator operator+(int i) {	assert(invariant()); return BaseIterator(_ptr + (i * direction)); }
	virtual BaseIterator operator++(int) { assert(invariant()); BaseIterator i = *this; _ptr += direction; return i; }
	virtual BaseIterator operator++() { assert(invariant()); _ptr += direction; return *this; }

	virtual bool operator<(const BaseIterator& rhs) { assert(invariant()); return _ptr < rhs._ptr; }
	virtual int operator-(BaseIterator rhs) { assert(invariant()); int i = *_ptr - *rhs._ptr; return i; }
	virtual int operator+=(int rhs) { assert(invariant()); int i = *_ptr + rhs; return i; }
	virtual BaseIterator operator--() { assert(invariant()); _ptr -= direction; return *this; }
};