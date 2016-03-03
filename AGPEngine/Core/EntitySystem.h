#pragma once
#include <unordered_map>
#include <map>
#include <typeindex>
#include <memory>

#include "Component.h"
#include "MessagingSystem.h"

namespace AGPEngine
{
    template<typename T>
    class ComponentAddedMessage : public Message
    {
        T* m_AddedComponent;

    public:
        ComponentAddedMessage(T* a_AddedComponent)
            : m_AddedComponent(a_AddedComponent)
        {
        }

        T* getAddedComponent() const
        {
            return m_AddedComponent;
        }
    };

    class EntityActivatedMessage : public Message
    {
        GameObject m_ActivatedEntity;

    public:
        EntityActivatedMessage(GameObject a_Entity);

        GameObject getActivatedEntity() const;
    };

    class EntityDeactivatedMessage : public Message
    {
        GameObject m_DeactivatedEntity;
        
    public:
        EntityDeactivatedMessage(GameObject a_Entity);

        GameObject getDeactivatedEntity() const;
    };

    class EntitySystem
    {
    private:
        struct EntityState
        {
        public:
            bool Active = true;
        };

        //Unsigned used for game object id
        std::unordered_map<std::type_index, std::map<unsigned, std::unique_ptr<Component>>> m_Components;
        std::map<unsigned, EntityState> m_EntityStates;
        MessagingSystem& m_MessagingSystem;
        unsigned m_LastID = 0;

    public:
        EntitySystem(MessagingSystem& a_MessagingSystem);

        template<typename T>
        T* addComponent(GameObject a_GameObject)
        {
            std::unique_ptr<Component> newComponent = std::make_unique<T>(a_GameObject);
            T* componentHandle = static_cast<T*>(newComponent.get());
            m_Components[std::type_index(typeid(T))].emplace(a_GameObject.getID(), std::move(newComponent));
            m_MessagingSystem.broadcast<ComponentAddedMessage<T>>(componentHandle);
            return componentHandle;
        }

        template<typename T>
        T* getComponent(unsigned a_GameObjectID) const
        {
            auto iterator = m_Components.find(typeid(T));
            if(iterator != m_Components.end())
            {
                auto componentIterator = iterator->second.find(a_GameObjectID);
                return componentIterator != iterator->second.end() ? static_cast<T*>(componentIterator->second.get()) : nullptr;
            }
            return nullptr;
        }

        template<typename T>
        std::vector<T*> getComponentsOfType() const
        {            
            std::vector<T*> components;
            auto iterator = m_Components.find(typeid(T));
            if(iterator != m_Components.end())
            {
                components.reserve(iterator->second.size());
                for(auto& keyValue : iterator->second)
                {
                    if(keyValue.second->getGameObject().isActive())
                    {
                        components.push_back(static_cast<T*>(keyValue.second.get()));
                    }
                }
            }
            return components;
        }

        template<typename T = GameObject>
        T createEntity()
        {
            auto id = generateNextID();
            m_EntityStates.emplace(id, EntityState());
            return T(id, *(this));
        }

        bool isActive(GameObject a_EntityID);
        void activate(GameObject a_EntityID);
        void deactivate(GameObject a_EnittyID);

    private:
        unsigned generateNextID();
    };
}