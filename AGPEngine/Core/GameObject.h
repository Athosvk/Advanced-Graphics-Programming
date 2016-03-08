#pragma once
namespace AGPEngine
{
    class EntitySystem;
    class Transform;

    class GameObject
    {
    private:
        unsigned m_ID;
        EntitySystem& m_EntitySystem;
    protected:
        Transform* m_Transform;

    public:
        GameObject(unsigned a_ID, EntitySystem& a_EntitySystem);

        unsigned getID();
        bool isActive();
        void activate();
        void deactivate();

        template<typename T>
        T* getComponent() const
        {
            return m_EntitySystem.getComponent<T>(m_ID);
        }

        template<>
        Transform* getComponent() const
        {
            return m_Transform;
        }

        template<typename T>
        T* addComponent()
        {
            return m_EntitySystem.addComponent<T>(*this);
        }
    };
}
