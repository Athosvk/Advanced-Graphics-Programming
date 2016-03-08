#pragma once
#include <d3d11.h>

#include "EventQueue.h"
#include "Color.h"

namespace AGPEngine
{
    class Window
    {
    private:
        ID3D11Device* m_Device = nullptr;
        ID3D11DeviceContext* m_DeviceContext = nullptr;
        IDXGISwapChain* m_SwapChain = nullptr;
        ID3D11RenderTargetView* m_RenderTarget = nullptr;
        ID3D11Texture2D* m_DepthStencilBuffer = nullptr;
        ID3D11DepthStencilView* m_DepthStencilView = nullptr;
        D3D11_VIEWPORT m_Viewport = {};
        EventQueue m_EventQueue;
        int m_Width;
        int m_Height;
        int m_MinimumWidth = 200;
        int m_MinimumHeight = 200;
        std::wstring m_Title = L"";
        HINSTANCE m_ApplicationHandle;
        HWND m_WindowHandle;
        enum class EWindowState
        {
            Maximized,
            Minimized,
            Original,
            Resizing
        } m_WindowState;
        bool m_VSyncEnabled = false;
        Color m_BackgroundColor = Color::Black;

    public:
        Window(int a_Width, int a_Height, const std::wstring& a_Title, HINSTANCE a_ApplicationHandle);
        ~Window();
        
        float getAspectRatio();
        void renderCurrentFrame();
        void clear();
        EventQueue& getEventQueue();
    private:
        void initialiseWindow();
        void initialiseDirectx();
        void onResize();
        void handleResize(WPARAM a_Type, int a_NewWidth, int a_NewHeight);
        LRESULT CALLBACK processEvent(HWND a_Window, UINT a_MessageType, WPARAM a_Parameter1,
            LPARAM a_Parameter2);
        static LRESULT CALLBACK handleWindowEvent(HWND a_Window, UINT a_MessageType, WPARAM a_Parameter1, 
            LPARAM a_Parameter2);
    };
}
