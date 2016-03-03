#include "EventQueue.h"

namespace AGPEngine
{
    Event::Event(WPARAM a_Parameter1, LPARAM a_Parameter2, UINT a_EventType)
    {
    }

    void EventQueue::handleWindowEvent(HWND a_Window, UINT a_MessageType, WPARAM a_Parameter1, LPARAM a_Parameter2)
    {
        m_CurrentEvents.emplace(a_Parameter1, a_Parameter2, a_MessageType);
    }

    Event EventQueue::dequeue()
    {
        auto newestEvent = m_CurrentEvents.front();
        m_CurrentEvents.pop();
        return newestEvent;
    }

    bool EventQueue::isEmpty() const
    {
        return m_CurrentEvents.empty();
    }
}