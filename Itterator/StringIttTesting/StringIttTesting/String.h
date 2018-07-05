#pragma once
#include <iostream>
#include <cassert>
#include "CustomIterator.h"

class String {
private:
	int currentLength;
	int maxLength;
	char* cArray;

	void Clean() { for (int i = currentLength; i < maxLength; i++) cArray[i] = '\0'; }
	bool Invariant() { return currentLength <= maxLength || cArray == nullptr; }
	void Release() {
		assert(Invariant());
		delete[] cArray;
		cArray = 0;
	}
	void Insert(char c) {
		assert(Invariant());
		cArray[currentLength] = c;
		++currentLength;
		assert(Invariant());
	}

	void AllocateNewMemory(int size, int cap) {
		assert(Invariant());
		char* temp = new char[cap];
		try {
			if (temp) {
				for (int i = 0; i < size; ++i)
					temp[i] = cArray[i];
				Release();
				cArray = temp;
				maxLength = cap;
				temp = nullptr;
			}
			else
				throw std::bad_alloc();
		}
		catch (std::bad_alloc& ba) {
			delete[] temp;
			temp = 0;
			std::cout << ba.what();
		}
		assert(Invariant());
	}

public:
	// Iterator
	using iterator = BaseIterator<char, 1>;
	using reverse_iterator = BaseIterator<char, -1>; // reverse
	using const_iterator = BaseIterator<const char, 1>; // const
	using const_reverse_iterator = BaseIterator<const char, -1>; // const reverse

	iterator begin() { return iterator(cArray); }
	iterator end() { return iterator(cArray + currentLength); }
	reverse_iterator rbegin(){ return reverse_iterator(cArray + currentLength - 1); }
	reverse_iterator rend() { return reverse_iterator(cArray - 1); }

	const_iterator cbegin() { return const_iterator(cArray); }
	const_iterator cend() { return const_iterator(cArray + currentLength); }
	const_reverse_iterator crbegin() { return const_reverse_iterator(cArray + currentLength - 1); }
	const_reverse_iterator crend() { return const_reverse_iterator(cArray - 1); }

	// Constructors
#pragma region 
	~String() { Release(); }

	String() : currentLength(0), maxLength(16) { cArray = new char[16]; Clean(); assert(Invariant()); }

	String(const String& rhs) : currentLength(rhs.currentLength), maxLength(rhs.maxLength) {
		cArray = new char[maxLength];
		for (int i = 0; i <= currentLength; i++)
			cArray[i] = rhs.cArray[i];
		Clean();
		assert(Invariant());
	}

	String(const char* cstr) : currentLength(0) {
		while (cstr[currentLength])
			++currentLength;
		maxLength = currentLength > 0 ? currentLength * 2 : 16;
		cArray = new char[maxLength];
		for (int i = 0; i <= currentLength; i++)
			cArray[i] = cstr[i];
		Clean();
		assert(Invariant());
	}
#pragma endregion Constructors

	// Operators
#pragma region
	String& operator=(const String& rhs) {
		assert(Invariant());
		if (maxLength != rhs.maxLength)
			reserve(rhs.maxLength);
		currentLength = rhs.currentLength;
		for (int i = 0; i <= currentLength; i++)
			cArray[i] = rhs.cArray[i];
		assert(Invariant());
		return *this;
	}
	friend std::ostream& operator<<(std::ostream& cout, String& rhs) {
		for (int i = 0; i < rhs.currentLength; ++i)
			cout << rhs.cArray[i];
		return cout;
	}
	char& operator[](int i) { return cArray[i]; }
	const char& operator[](int i) const { return cArray[i]; }
#pragma endregion working operators
	friend bool operator==(const String& lhs, const String& rhs) {
		if (lhs.currentLength != rhs.currentLength) return false;
		for (int i = 0; i < lhs.currentLength; i++)
			if (lhs.cArray[i] != rhs.cArray[i])	return false;
		return true;
	}
	friend bool operator!=(const String& lhs, const String& rhs) { return !(lhs == rhs); }
	operator bool() { if (cArray[0] != '\0' || currentLength > 0) return true; return false; }

	// Methods
	int size() const { return currentLength; }
	int capacity() const { return maxLength; }
	void shrink_to_fit() { assert(Invariant()); AllocateNewMemory(currentLength, currentLength); }
	void reserve(int n) { assert(Invariant()); AllocateNewMemory(currentLength, n); }
	const char* data() const { return cArray; }
	void push_back(char c) {
		assert(Invariant());
		if (currentLength + 1 < maxLength) {
			Insert(c);
			Clean();
		}
		else {
			AllocateNewMemory(currentLength + 1, maxLength * 2);
			Insert(c);
			Clean();
		}
		assert(Invariant());
	}
	void resize(int n) {
		assert(Invariant());
		if (n >= maxLength)
			AllocateNewMemory(currentLength, n);
		if (n > currentLength)
			Clean();
		currentLength = n;
		assert(Invariant());
	}

	char& at(int index) {
		assert(Invariant());
		try {
			if (index < 0 || index > maxLength)
				throw std::out_of_range("Out of Range\n");
			else
				return cArray[index];
		}
		catch (std::out_of_range oor) {
			std::cout << oor.what();
		}
	}
	String& operator+=(const String& rhs) { 
		assert(Invariant());
		int newLength = currentLength + rhs.currentLength;
		if (newLength > maxLength) reserve(maxLength + rhs.maxLength);
		int index = 0;
		for (int i = currentLength; i < newLength; i++)
		{
			cArray[i] = rhs.cArray[index];
			++index;
		}
		currentLength = newLength;
		assert(Invariant());
		return *this;
	}
};