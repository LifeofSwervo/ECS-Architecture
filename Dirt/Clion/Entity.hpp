// Entity.hpp
#pragma once
#include "Common.hpp"
#include "Components.hpp"

class Entity
{
    friend class EntityManager;

    bool m_active = true;
    size_t m_id = 0;
    std::string m_tag = "default";

    // Constructor / Destructor
    Entity(const size_t id, const std::string& tag);

public:
    // Component Pointers
    std::shared_ptr<CTransform> cTransform;
    std::shared_ptr<CShape> cShape;
    std::shared_ptr<CCollision> cCollision;
    std::shared_ptr<CInput> cInput;
    std::shared_ptr<CScore> cScore;
    std::shared_ptr<CLifespan> cLifespan;




    // Private member access functions
    bool isActive() const; // Const at the end of declaration ensures function is not modified.
    const std::string & tag() const;
    const size_t id() const;
    void destroy();
};