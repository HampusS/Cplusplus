#pragma once
#include <iostream>
#include "GCD.h"

template<typename Tint>
class Rational {
public:
	Tint P, Q;

	Rational() : P(0), Q(1) {}
	Rational(Tint P) :P(P), Q(1) {}
	Rational(Tint P, Tint Q) :P(P), Q(Q) {
		Reduce(P, Q);
	}
	template<typename Y>
	Rational(const Rational<Y> rhs) : P(rhs.P), Q(rhs.Q) {}

	Rational operator += (const Rational& rhs) {
		P = (P * rhs.Q) + (Q * rhs.P);
		Q = Q * rhs.Q;
		Reduce(P, Q);
		return *this;
	}

	Rational operator + (const Rational& rhs) {
		Rational<Tint> temp(*this);
		return temp += rhs;
	}

	template<typename T>
	Rational operator + (const T& rhs) {
		Rational<Tint> temp(*this);
		return temp += rhs;
	}

	Rational operator - () {
		return Rational(-P, Q);
	}

	Rational& operator ++ () {
		P = P + Q;
		return *this;
	}

	template<typename T>
	Rational& operator ++ (T) {
		Rational temp(*this);
		operator++();
		return temp;
	}

	operator Tint() {
		Tint temp = P / Q;
		return temp;
	}

};

template<typename T>
std::ostream& operator << (std::ostream&  cout, Rational< T >R) {
	cout << R.P << '/' << R.Q;
	return cout;
}

template<typename T>
 std::istream& operator >> (std::istream& cin, Rational<T>& rhs) {
	cin >> rhs.P >> rhs.Q;
	return cin;
}
 template<typename T, typename I>
 bool operator == (const Rational<T>& lhs,const Rational<I>& rhs) {
	 return (lhs.P / lhs.Q) == (rhs.P / rhs.Q);
 }
 template<typename T, typename I>
 bool operator == (const T& lhs, const Rational<I>& rhs) {
	 return lhs == (rhs.P / rhs.Q);
 }
 template<typename T, typename I>
 bool operator == (const Rational<T>& lhs, const I& rhs) {
	 return (lhs.P / lhs.Q) == rhs;
 }
 //template <typename T, typename I> 
 //T rational_cast(const Rational<I>& r) {
	// T temp = r.P / r.Q;
	// return temp;
 //}

