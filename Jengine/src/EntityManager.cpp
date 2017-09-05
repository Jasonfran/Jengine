#include "EntityManager.h"

EntityManager::EntityManager()
{
}

unsigned int EntityManager::generateID()
{
	unsigned int entityID;
	if (recyclableIDs.size() > 0)
	{
		entityID = recyclableIDs.back();
		recyclableIDs.pop_back();
	}
	else
	{
		entityID = nextID++;
	}
	return entityID;
}

bool EntityManager::entityExists( unsigned int entityID )
{
	return idToName.count( entityID );
}

unsigned int EntityManager::create()
{
	unsigned int entityID = generateID();
	idToName[entityID] = "-";
	return entityID;
}

unsigned int EntityManager::create(std::string name)
{
	unsigned int entityID = generateID();
	idToName[entityID] = name;
	nameToId[name] = entityID;
	return entityID;
}

void EntityManager::destroy( unsigned int entityID )
{
	if (entityExists(entityID))
	{
		nameToId.erase( idToName[entityID] );
		idToName.erase( entityID );
		for (auto& componentType : componentsStore)
		{
			componentType.second.erase( entityID );
		}
		recyclableIDs.push_back( entityID );
	}
}

unsigned int EntityManager::getID( std::string name )
{
	if (nameToId.count( name ))
		return nameToId[name];
}

std::string EntityManager::getName( unsigned int entityID )
{
	if (entityExists( entityID ))
		return idToName[entityID];
}

