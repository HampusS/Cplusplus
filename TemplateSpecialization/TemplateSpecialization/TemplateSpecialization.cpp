// TemplateSpecialization.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>


struct A {
	template <class T> void Test(T& s) {
		std::cout << "Standard Ref Template" << std::endl;
		s++;
	}


	// Template Specialization
	template<> void Test<int&>(int& s) {
		std::cout << "Int specialization" << std::endl;
		s++;
	}
};



int main()
{
	A 
	int i = 7;
	double d = 7;
	Test(i);
	Test(d);
	std::cout << "Final Int: " << i << std::endl;
	std::cout << "Final Double: " << d << std::endl;

	std::cin.get();
	return 0;
}

