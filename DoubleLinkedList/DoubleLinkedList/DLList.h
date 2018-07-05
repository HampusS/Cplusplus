#pragma once
#include "Link.h"

template <class T>
class DLList : public Link<T> {
private:
	std::ostream& Print(std::ostream& cout);
public:
	DLList() { next = this; prev = this; }
	//~List(){}

	T * First();
	const T * First() const;
	T * Last();
	const T * Last() const;

	T * PushFront(T * item);
	T * PushBack(T * item);
	T * PopFront();
	template<class Arg>
	T * FindFirst(const Arg& searchFor) { return FindNext(searchFor); }

	friend std::ostream& operator<<(std::ostream& cout, DLList& list) {
		return list.Print(cout);
	}

};

template<class T>
inline std::ostream & DLList<T>::Print(std::ostream & cout)
{
	for (T* node = First(); node != nullptr; node= node->Next())
	{
		dynamic_cast<T*>(node)->Print(cout);
	}
	std::cout << "\n";
	return cout;
}

template <class T>
T* DLList<T>::First() {
	return dynamic_cast<T*>(next);
}

template <class T>
const T* DLList<T>::First() const {
	return dynamic_cast<T*>(next);
}

template <class T>
T* DLList<T>::Last() {
	return dynamic_cast<T*>(prev);
}

template <class T>
const T* DLList<T>::Last() const {
	return dynamic_cast<T*>(prev);
}

template<class T>
T * DLList<T>::PushFront(T * item)
{
	if (next == this) {
		next = item;
		prev = item;
	}
	else {
		item->next = next;
		item->prev = nullptr;
		next->prev = item;
		next = item;
	}
	return item;
}

template<class T>
T * DLList<T>::PushBack(T * item)
{
	item->prev = prev;
	item->next = nullptr;
	prev->next = item;
	prev = item;
	return item;
}

template<class T>
T * DLList<T>::PopFront()
{
	if (next == this && prev == this)
	{
		return NULL;
	}
	if (next->next == NULL)
	{
		T* removedNode = dynamic_cast<T*>(next);
		next = this;
		prev = this;
		return removedNode;
	}
	return DeleteAfter();
}

