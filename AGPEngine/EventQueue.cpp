#include "EventQueue.h"

namespace AGPEngine
{
    Event::Event(WPARAM a_Parameter1, LPARAM a_Parameter2, UINT a_EventType)
    {
    }

    LRESULT EventQueue::handleWindowEvent(HWND a_Window, UINT a_MessageType, WPARAM a_Parameter1, LPARAM a_Parameter2)
    {
        return DefWindowProc(a_Window, a_MessageType, a_Parameter1, a_Parameter2);
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

    void EventQueue::update()
    {
        MSG message = {};
        while(PeekMessage(&message, 0, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
    }
}