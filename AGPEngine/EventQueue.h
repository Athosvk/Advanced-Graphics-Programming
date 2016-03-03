#pragma once
#define NOMINMAX
#include <Windows.h>
#include <queue>

namespace AGPEngine
{
    class Event
    {
    public:
        WPARAM Parameter1;
        LPARAM Parameter2;
        UINT EventType;

        Event(WPARAM a_Parameter1, LPARAM a_Parameter2, UINT a_EventType);
    };

    class EventQueue
    {
    private:
        std::queue<Event> m_CurrentEvents;

    public:
        void handleWindowEvent(HWND a_Window, UINT a_MessageType, WPARAM a_Parameter1, LPARAM a_Parameter2);
        Event dequeue();
        bool isEmpty() const;
    };
}
