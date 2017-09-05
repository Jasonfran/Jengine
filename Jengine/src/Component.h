#pragma once
#include <string>
#include <vector>

class Component
{
	static std::vector<unsigned int> recyclableIDs;
	static unsigned int nextID;
public:
	Component();
	virtual ~Component() {};
};

