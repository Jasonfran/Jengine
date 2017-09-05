#pragma once
#include <map>
#include <unordered_map>
#include <vector>
#include <memory>
#include "Jengine.h"

class Component;

typedef std::unordered_map<std::string, std::unordered_map<unsigned int, std::shared_ptr<Component>>> componentMap;

class EntityManager
{
	std::unordered_map<unsigned int, std::string> idToName;
	std::unordered_map<std::string, unsigned int> nameToId;
	componentMap componentsStore;
	std::vector<unsigned int> recyclableIDs;
	unsigned int nextID;
	unsigned int generateID();
	bool entityExists( unsigned int entityID );
public:
	EntityManager();
	unsigned int create();
	unsigned int create( std::string name );
	void destroy( unsigned int entityID );

	template <typename T>
	void addComponent( unsigned int entityID, std::shared_ptr<T> component );
	template <typename T>
	bool hasComponent( unsigned int entityID );
	template <typename T>
	std::shared_ptr<T> getComponentFromEntity( unsigned int entityID );
	template <typename T>
	std::vector<unsigned int> getEntitiesWithComponent();


	unsigned int getID( std::string name );
	std::string getName( unsigned int entityID );
};

template<typename T>
inline void EntityManager::addComponent( unsigned int entityID, std::shared_ptr<T> component )
{
	if (entityExists( entityID ))
	{
		componentsStore[typeid(T).name()][entityID] = component;
	}
}

template<typename T>
inline bool EntityManager::hasComponent( unsigned int entityID )
{
	return componentsStore[typeid(T).name()].count( entityID );
}

template<typename T>
inline std::shared_ptr<T> EntityManager::getComponentFromEntity( unsigned int entityID )
{
	if (hasComponent<T>( entityID ))
	{
		return std::dynamic_pointer_cast<T>(componentsStore[typeid(T).name()][entityID]);
	}
}

template<typename T>
inline std::vector<unsigned int> EntityManager::getEntitiesWithComponent()
{
	std::vector<unsigned int> entities;
	for (auto& keyval : componentsStore[typeid(T).name()])
	{
		entities.push_back( keyval.first );
	}
	return entities;
}
