#include "stdafx.h"
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <list>
#include <numeric>
#include <random>
#include <iostream>
#include <forward_list>
#include <iterator>
using namespace std;

vector<int> v(100);
int arr[101];
forward_list<int> fList = { 20,5,15,40,50,30 };

template<typename T, typename out>
out Merge(T begin1, T end1, T begin2, T end2, out result) {
	while (begin1 != end1) {
		if (begin2 == end2)
			return std::copy(begin1, end1, result);

		if (*begin1 < *begin2) {
			*result = *begin1;
			++begin1;
		}
		else {
			*result = *begin2;
			++begin2;
		}
		++result;
	}

	return std::copy(begin2, end2, result);
}

template<typename T>
void Partition(T lhs, T rhs)
{
	size_t n = std::distance(lhs, rhs);
	if (n < 2)
		return;
	T mid = lhs;
	for (size_t i = 0; i < n / 2; ++i)
		++mid;
	std::vector<typename T::value_type> res;
	Partition(lhs, mid);
	Partition(mid, rhs);
	Merge(lhs, mid, mid, rhs, std::back_inserter(res));
	std::copy(res.begin(), res.end(), lhs);
}

template<typename T>
void MergeSort(T& inList) {
	Partition(inList.begin(), inList.end());
}

int main()
{
	// Forward List - Merge Sort
	for (auto i = fList.begin(); i != fList.end(); i++)
		cout << *i << " ";
	cout << endl;
	MergeSort(fList);
	for (auto i = fList.begin(); i != fList.end(); i++)
		cout << *i << " ";
	cout << endl;

	// Array stl Sorting
	for (size_t i = 0; i < 101; i++)
		arr[i] = i;
	random_shuffle(begin(arr), end(arr));
	cout << "Array before sort:" << endl;
	for (size_t i = 0; i < 101; i++)
		cout << arr[i] << " ";
	cout << endl;
	sort(begin(arr), end(arr), [](const int a, const int b) {return a > b; });
	cout << "Array after sort:" << endl;
	for (size_t i = 0; i < 101; i++)
		cout << arr[i] << " ";
	cout << endl;

	// Vector stl Sorting
	cout << "Vector before sort:" << endl;
	iota(v.begin(), v.end(), 0);
	random_shuffle(v.begin(), v.end());
	for (auto i = 0; i < v.size(); i++)
		cout << v[i] << " ";
	cout << endl;
	sort(v.rbegin(), v.rend());
	remove_if(v.begin(), v.end(), [](const int& value) {return (value % 2) == 1; });
	cout << "Vector after sort:" << endl;
	for (auto i = 0; i < v.size(); i++)
		cout << v[i] << " ";

	cin.get();
	return 0;
}
