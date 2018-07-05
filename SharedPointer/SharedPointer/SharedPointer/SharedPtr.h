#pragma once
#include "cassert"

template <class T>
class SharedPtr {
private:
	template <class P>
	struct Controller {
		int counter = 0;
		P* obj;
		Controller() :obj(nullptr), counter(1) { }
		Controller(P* in) :obj(in), counter(1) { }
		Controller(const Controller&) = delete;
		~Controller() { delete obj;	obj = nullptr; }
	};
	Controller<T>* ctrl;
	void Increment() { if (ctrl != nullptr) ++ctrl->counter; }
	bool Invariant() { return ctrl == nullptr || ctrl->counter > 0; }

public:
	~SharedPtr() { reset(); }
	SharedPtr() :ctrl(nullptr) { assert(Invariant()); }
	SharedPtr(T* in) :ctrl(in!=nullptr? new Controller<T>(in): nullptr) { assert(Invariant()); }
	SharedPtr(const SharedPtr& rhs) :ctrl(rhs.ctrl) { Increment(); assert(Invariant()); }
	SharedPtr(SharedPtr&& rhs) {
		assert(Invariant());
		ctrl = rhs.ctrl;
		Increment();
		rhs.reset();
		assert(Invariant());
	}

	bool operator ==(const SharedPtr& rhs) const {
		if (ctrl == nullptr && rhs.ctrl == nullptr)
			return true;
		return ctrl == rhs.ctrl ? true : false;
	}
	bool operator <(const SharedPtr& rhs) const {
		if (ctrl == nullptr || rhs.ctrl == nullptr)
			return ctrl == nullptr ? true : false;
		if (ctrl->obj != nullptr && rhs.ctrl->obj != nullptr)
			return &ctrl->obj < &rhs.ctrl->obj;
		return ctrl->obj == nullptr ? true : false;
	}
	operator bool() const { return ctrl == nullptr || ctrl->obj == nullptr ? false : true; }
	bool unique() const { if (ctrl->counter == 1) return true; return false; }
	T* operator ->() const { return ctrl->obj; }
	T* get() const { return ctrl->obj; }
	T& operator *() const { return *ctrl->obj; }

	SharedPtr<T>& operator =(const SharedPtr<T>& rhs) {
		assert(Invariant());
		if (ctrl != rhs.ctrl) {
			reset();
			ctrl = rhs.ctrl;
			Increment();
		}
		assert(Invariant());
		return *this;
	}

	void reset() {
		assert(Invariant());
		if (ctrl != nullptr) {
			if (ctrl->counter == 1) {
				delete ctrl;
				ctrl = nullptr;
			}
			else {
				--ctrl->counter;
				ctrl = nullptr;
			}
		}
		assert(Invariant());
	}
};