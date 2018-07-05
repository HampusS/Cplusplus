#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cassert>

template <typename T>
class BaseIterator : public std::iterator<std::random_access_iterator_tag, T> {
protected:
	T* ptr;
	bool invariant() { return ptr != nullptr; }

public:
	BaseIterator(T* ptr) : ptr(ptr) {}
	T& operator*() { return *ptr; }
	T& operator[](int i) { return *(ptr + i); }
	T* operator->() { return ptr; }
	bool operator==(const BaseIterator& rhs) { return ptr == rhs.ptr; }
	bool operator!=(const BaseIterator& rhs) { return ptr != rhs.ptr; }
};