#pragma once
// EntityManager.hpp

#include "Common.hpp"
#include "Entity.hpp"

typedef std::vector<std::shared_ptr<Entity>> EntityVec; // Dynamic Array, with each element pointing to an Entity.
typedef std::map<std::string, EntityVec> EntityMap; // Map (dictionary), Key is string for Entity. Value is EntityVec

class EntityManager
{
    EntityVec m_entities;
    EntityVec m_entitiesToAdd; // Temp list
    EntityMap m_entityMap;
    size_t m_totalEntities;

    void removeDeadEntities(EntityVec& vec);


public:
    EntityManager();
    void update();
    std::shared_ptr<Entity> addEntity(const std::string& tag);

    const EntityVec& getEntities();
    const EntityVec& getEntities(const std::string& tag);
};
