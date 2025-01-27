// EntityManager.cpp
#include "EntityManager.hpp"

EntityManager::EntityManager()
{
    
}

void EntityManager::update()
{
    // Adds entities from m_entitiesToAdd to the proper locations
    //  - Adds them to the vector of all entites
    //  - Adds them to the vector inside the map, with the tag as the key
    
    /*
    for (auto& entity : m_entitiesToAdd)
    {
        m_entities.push_back(entity); // Pass entity to m_entities array.
        m_entityMap[entity->tag()].push_back(entity); // Give entityMap the tag of the entity.
    }
    */
        
        
    //m_entitiesToAdd.clear(); // Clear all elements in the array
    removeDeadEntities(m_entities);
    
    for (auto& [tag, entityVec] : m_entityMap)
    {
        removeDeadEntities(entityVec);
    }
}

void EntityManager::removeDeadEntities(EntityVec & vec)
{
    
}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string & tag)
{
    // Adds enemies to the m_entitiesToAdd, then placed in the proper location in the update() function.

    // Create entity and shared pointer
    auto entity = std::shared_ptr<Entity>(new Entity(m_totalEntities++, tag));
    
    m_entitiesToAdd.push_back(entity);
    
    return entity;
}

const EntityVec & EntityManager::getEntities()
{
    return m_entities;
}

const EntityVec & EntityManager::getEntities(const std::string & tag)
{
    return m_entityMap[tag];
}
