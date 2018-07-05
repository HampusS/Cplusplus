// StringIttTesting.cpp : Defines the entry point for the console application.
//
#define _CRTDBG_MAP_ALLOC
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

#include "stdafx.h"
#include "String.h"
#include <algorithm>
#include <iostream>
#define VG
using std::cout;
using std::endl;

void TestIttInAlg() {
	static const int N = 26;
	String v;
	v.reserve(N);
	for (int i = 0; i < N; ++i) {
		v.push_back('a' + i);
	}
	v.begin();
	auto b = std::begin(v);
	auto e = std::end(v);
	std::random_shuffle(b, e);
	cout << v << endl;
	std::stable_sort(b, e);
	cout << v << endl;
}

void TestRevIttInAlg() {
	static const int N = 26;
	String v;
	v.reserve(N);
	for (int i = 0; i < N; ++i) {
		v.push_back('a' + i);
	}
	auto b = std::rbegin(v);
	auto e = std::rend(v);
	//std::random_shuffle(b, e);
	cout << v << endl;
	//std::stable_sort(b, e);
	cout << v << endl;
}

/*	*it, ++it, it++, (it+i), it[i], == och !=	*/
void TestIttPart() {
	String s1("foobar");
	for (auto i = s1.begin(); i != s1.end(); i++)
		cout << *i;
	cout << endl;
	auto it = s1.begin();

	assert(*it == 'f');
	assert(*(it++) == 'f' && *it == 'o');
	++it;
	assert(*++it == 'b');
	assert(*(it + 1) == 'a');
	assert(it[2] == 'r');
}

void TestIttPartR() {
	String s1("foobar");
	for (auto i = s1.rbegin(); i != s1.rend(); i++)
		cout << *i;
	cout << endl;
	s1 = "raboof";
	auto it = s1.rbegin();
	assert(*it == 'f');
	assert(*(it++) == 'f' && *it == 'o');
	++it;
	assert(*++it == 'b');
	assert(*(it + 1) == 'a');
	assert(it[2] == 'r');
}

#ifdef VG
void TestIttPartC() {
	String s1("foobar");
	for (auto i = s1.cbegin(); i != s1.cend(); i++)
		cout << *i;
	cout << endl;
	//    s1 = "raboof";
	auto it = s1.cbegin();
	assert(*it == 'f');
	assert(*(it++) == 'f' && *it == 'o');
	++it;
	assert(*++it == 'b');
	assert(*(it + 1) == 'a');
	assert(it[2] == 'r');
}

void TestIttPartCR() {
	String s1("foobar");
	for (auto i = s1.crbegin(); i != s1.crend(); ++i)
		cout << *i;
	cout << endl;
	s1 = "raboof";
	auto it = s1.crbegin();
	assert(*it == 'f');
	assert(*(it++) == 'f' && *it == 'o');
	++it;
	assert(*++it == 'b');
	assert(*(it + 1) == 'a');
	assert(it[2] == 'r');
}
#endif VG

void TestFörGodkäntItt() {
	//-	typdefs för iterator, const_iterator,  reverse_iterator och const_revers_iterator
	String::iterator Str;
	String::reverse_iterator rStr;
	//-	funktionerna begin, end, cbegin, cend, rbegin, rend, crbegin och crend.
	TestIttPart();
	TestIttPartR();
#ifdef VG
	String::const_iterator cStr;
	String::const_reverse_iterator crStr;
	TestIttPartC();
	TestIttPartCR();
#endif VG
	//Iteratorerna ska kunna göra:
	//-	*it, ++it, it++, (it+i), it[i], == och !=
	//-	default constructor, copy constructor och tilldelning (=) 
	String s("foobar");
	Str = s.begin();
	rStr = s.rbegin();
#ifdef VG
	cStr = s.cbegin();
	crStr = s.crbegin();
#endif VG
	*Str = 'a';
	char cc = *(rStr + -2);
	*(rStr + 2) = 'c';
	//*(cStr + 1) = 'b';	//Ska ge kompileringsfel!
	//*(crStr + 3) = 'd';	//Ska ge kompileringsfel!
	assert(s == "aoocar");
	cout << "\nTestFörGodkänt Itt klar\n";
#ifdef VG
	cout << "\nTestFörVälGodkänt Itt klar\n";
#endif VG
}

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	TestIttInAlg();
	TestRevIttInAlg();
	TestFörGodkäntItt();
	std::cin.get();
	return 0;
}