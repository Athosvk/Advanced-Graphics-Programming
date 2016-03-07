#include "EventQueue.h"

namespace AGPEngine
{
    Event::Event(WPARAM a_Parameter1, LPARAM a_Parameter2, UINT a_EventType)
        : Parameter1(a_Parameter1), 
        Parameter2(a_Parameter2),
        EventType(a_EventType)
    {
    }

    LRESULT EventQueue::handleWindowEvent(HWND a_Window, UINT a_MessageType, WPARAM a_Parameter1, LPARAM a_Parameter2)
    {
        switch(a_MessageType)
        {
        case WM_LBUTTONUP:
        case WM_MBUTTONUP:
        case WM_RBUTTONUP:
        case WM_LBUTTONDOWN:
        case WM_MBUTTONDOWN:
        case WM_RBUTTONDOWN:
        case WM_MOUSEMOVE:
        case WM_QUIT:
            m_CurrentEvents.emplace(a_Parameter1, a_Parameter2, a_MessageType);
            return 0;
        default:
            return DefWindowProc(a_Window, a_MessageType, a_Parameter1, a_Parameter2);
        }
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