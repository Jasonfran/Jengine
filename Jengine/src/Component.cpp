#include "Component.h"

std::vector<unsigned int> Component::recyclableIDs;
unsigned int Component::nextID;

Component::Component()
{
	unsigned int componentID;
	if (recyclableIDs.size() > 0)
	{
		componentID = recyclableIDs.back();
		recyclableIDs.pop_back();
	}
	else
	{
		componentID = nextID++;
	}
}
