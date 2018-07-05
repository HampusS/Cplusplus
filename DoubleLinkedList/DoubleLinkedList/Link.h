#pragma once
#include <iostream>

template <class T>
class DLList;

template <class T>
class Link {
private:
	Link* next;
	Link* prev;
	friend class DLList<T>;

public:
	bool Invariant() {
		return next->prev == this && prev->next == this || next->prev == NULL && prev->next == NULL;
	}
	Link() { next = nullptr; prev = nullptr; }
	virtual ~Link() { }

	T* Next();
	const T* Next() const;
	T* Prev();
	const T* Prev() const;

	T* InsertAfter(T* TToInsert);
	T* InsertBefore(T* TToInsert);
	T* DeleteAfter();
	template<class Arg> T* FindNext(const Arg& searchFor);

	virtual std::ostream& Print(std::ostream& cout) { 
		return cout << "Link"; 
	}
};

template <class T> 
T* Link<T>::Next() {
	return dynamic_cast<T*>(next);
}

template <class T>
const T* Link<T>::Next() const {
	return dynamic_cast<T*>(next);
}

template <class T>
T* Link<T>::Prev() {
	return dynamic_cast<T*>(prev);
}

template <class T>
const T* Link<T>::Prev() const {
	return dynamic_cast<T*>(prev);
}

template<class T>
inline T * Link<T>::InsertAfter(T * TToInsert){
	TToInsert->next = next;
	TToInsert->prev = this;
	if (next)
		next->prev = TToInsert;
	next = TToInsert;
	return TToInsert;
}

template<class T>
inline T * Link<T>::InsertBefore(T * TToInsert){
	TToInsert->prev = prev;
	TToInsert->next = this;
	if (prev)
		prev->next = TToInsert;
	prev = TToInsert;
	return TToInsert;
}

template<class T>
inline T * Link<T>::DeleteAfter(){
	T* temp = next != nullptr ? dynamic_cast<T*>(next) : nullptr;
	if (temp){
		next = next->next;
		next->prev = this;
	}
	return temp;
}

template<class T>
template<class Arg>
inline T * Link<T>::FindNext(const Arg & searchFor){
	if (next == nullptr)
		return nullptr;
	else if (dynamic_cast<T*>(next)->Match(searchFor))
		return dynamic_cast<T*>(next);
	else
		next->FindNext(searchFor);
}
