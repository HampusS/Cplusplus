#pragma once
#include "Link.h"

class Node : public Link<Node>
{
	float data;

	//match används i FindNext funktionen bool match(float rhs) { return val=rhs; }
public:
	Node(float v = 0) : data(v) {}
	Node(){}
	~Node() { }

	bool Match(float rhs) { return data == rhs; }

	//std::ostream& Print(std::ostream& cout) const {
	//	return cout << data;
	//}

};
