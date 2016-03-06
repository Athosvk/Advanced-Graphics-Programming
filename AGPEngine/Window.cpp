#include <d3dUtil.h>

#include "Window.h"

namespace AGPEngine
{
    Window::Window(int a_Width, int a_Height, const std::wstring& a_Title, HINSTANCE a_ApplicationHandle)
        : m_Width(a_Width),
        m_Height(a_Height),
        m_Title(a_Title),
        m_ApplicationHandle(a_ApplicationHandle)
    {
        initialiseWindow();
        initialiseDirectx();
    }

    Window::~Window()
    {
        m_DepthStencilView->Release();
        m_RenderTarget->Release();
        m_DepthStencilBuffer->Release();
        m_SwapChain->Release();
        m_DeviceContext->ClearState();
        m_DeviceContext->Release();
        m_Device->Release();
    }

    float Window::getAspectRatio()
    {
        return static_cast<float>(m_Width) / m_Height;
    }

    void Window::renderCurrentFrame()
    {
        m_SwapChain->Present(m_VSyncEnabled ? 1 : 0, 0);
    }

    void Window::clear()
    {
        FLOAT backgroundColor[4] = { m_BackgroundColor.r, m_BackgroundColor.g,
            m_BackgroundColor.b, m_BackgroundColor.a };
        m_DeviceContext->ClearRenderTargetView(m_RenderTarget, backgroundColor);
    }

    void Window::initialiseWindow()
    {
        WNDCLASS windowDefinition
        {
            CS_HREDRAW | CS_VREDRAW,
            this->handleWindowEvent,
            0, 0, m_ApplicationHandle,
            LoadIcon(0, IDI_APPLICATION),
            LoadCursor(0, IDC_ARROW),
            static_cast<HBRUSH>(GetStockObject(NULL_BRUSH)),
            0,
            L"D3DWndClassName",
        };

        if(!RegisterClass(&windowDefinition))
        {
            MessageBox(0, L"RegisterClass Failed.", 0, 0);
            std::abort();
        }

        RECT windowDimensions = { 0, 0, m_Width, m_Height };
        AdjustWindowRect(&windowDimensions, WS_OVERLAPPEDWINDOW, false);
        int width = windowDimensions.right - windowDimensions.left;
        int height = windowDimensions.bottom - windowDimensions.top;

        m_WindowHandle = CreateWindow(L"D3DWndClassName", m_Title.c_str(),
            WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, 0, 0, m_ApplicationHandle, 0);
        if(!m_WindowHandle)
        {
            MessageBox(0, std::wstring(L"CreateWindow Failed. Error: " + 
                std::to_wstring(GetLastError())).c_str(), 0, 0);
            std::abort();
        }
        SetWindowLongPtr(m_WindowHandle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
        ShowWindow(m_WindowHandle, SW_SHOW);
        UpdateWindow(m_WindowHandle);
    }

    void Window::initialiseDirectx()
    {
        UINT createDeviceFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)  
        createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

        D3D_FEATURE_LEVEL featureLevel;
        HR(D3D11CreateDevice(
            0,                 // default adapter
            D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE,
            0,                 // no software device
            createDeviceFlags,
            0, 0,              // default feature level array
            D3D11_SDK_VERSION,
            &m_Device,
            &featureLevel,
            &m_DeviceContext));

        if(featureLevel != D3D_FEATURE_LEVEL_11_0)
        {
            MessageBox(0, L"Direct3D Feature Level 11 unsupported.", 0, 0);
            std::abort();
        }

        // Fill out a DXGI_SWAP_CHAIN_DESC to describe our swap chain.

        DXGI_SWAP_CHAIN_DESC swapChainDescription;
        swapChainDescription.BufferDesc.Width = m_Width;
        swapChainDescription.BufferDesc.Height = m_Height;
        swapChainDescription.BufferDesc.RefreshRate.Numerator = 60;
        swapChainDescription.BufferDesc.RefreshRate.Denominator = 1;
        swapChainDescription.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        swapChainDescription.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
        swapChainDescription.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
        swapChainDescription.SampleDesc.Count = 1;
        swapChainDescription.SampleDesc.Quality = 0;
        swapChainDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swapChainDescription.BufferCount = 1;
        swapChainDescription.OutputWindow = m_WindowHandle;
        swapChainDescription.Windowed = true;
        swapChainDescription.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
        swapChainDescription.Flags = 0;

        IDXGIDevice* dxgiDevice = 0;
        HR(m_Device->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgiDevice)));
        IDXGIAdapter* dxgiAdapter = 0;
        HR(dxgiDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(&dxgiAdapter)));
        IDXGIFactory* dxgiFactory = 0;
        HR(dxgiAdapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&dxgiFactory)));
        HR(dxgiFactory->CreateSwapChain(m_Device, &swapChainDescription, &m_SwapChain));

        dxgiDevice->Release();
        dxgiAdapter->Release();
        dxgiFactory->Release();

        onResize();
    }

    void Window::onResize()
    {
        if(m_RenderTarget)
        {
            m_RenderTarget->Release();
            m_DepthStencilView->Release();
            m_DepthStencilBuffer->Release();
        }

        HR(m_SwapChain->ResizeBuffers(1, m_Width, m_Height, DXGI_FORMAT_R8G8B8A8_UNORM, 0));
        ID3D11Texture2D* backBuffer;
        HR(m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer)));
        HR(m_Device->CreateRenderTargetView(backBuffer, 0, &m_RenderTarget));
        backBuffer->Release();

        D3D11_TEXTURE2D_DESC depthStencilDescription;
        depthStencilDescription.Width = m_Width;
        depthStencilDescription.Height = m_Height;
        depthStencilDescription.MipLevels = 1;
        depthStencilDescription.ArraySize = 1;
        depthStencilDescription.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
        depthStencilDescription.SampleDesc.Count = 1;
        depthStencilDescription.SampleDesc.Quality = 0;
        depthStencilDescription.Usage = D3D11_USAGE_DEFAULT;
        depthStencilDescription.BindFlags = D3D11_BIND_DEPTH_STENCIL;
        depthStencilDescription.CPUAccessFlags = 0;
        depthStencilDescription.MiscFlags = 0;

        HR(m_Device->CreateTexture2D(&depthStencilDescription, 0, &m_DepthStencilBuffer));
        HR(m_Device->CreateDepthStencilView(m_DepthStencilBuffer, 0, &m_DepthStencilView));

        m_DeviceContext->OMSetRenderTargets(1, &m_RenderTarget, m_DepthStencilView);

        m_Viewport.TopLeftX = 0;
        m_Viewport.TopLeftY = 0;
        m_Viewport.Width = static_cast<float>(m_Width);
        m_Viewport.Height = static_cast<float>(m_Height);
        m_Viewport.MinDepth = 0.0f;
        m_Viewport.MaxDepth = 1.0f;

        m_DeviceContext->RSSetViewports(1, &m_Viewport);
    }

    void Window::handleResize(WPARAM a_Type, int a_NewWidth, int a_NewHeight)
    {
        switch(a_Type)
        {
        case SIZE_MINIMIZED:
            m_WindowState = EWindowState::Minimized;
        case SIZE_MAXIMIZED:
            m_WindowState = EWindowState::Maximized;
        case SIZE_RESTORED:
            if(m_WindowState != EWindowState::Resizing)
            {
                m_WindowState = EWindowState::Original;
            }
        default:
            break;
        }
        if(m_WindowState == EWindowState::Maximized || m_WindowState == EWindowState::Maximized)
        {
            onResize();
        }
    }

    LRESULT Window::processEvent(HWND a_Window, UINT a_MessageType, WPARAM a_Parameter1, LPARAM a_Parameter2)
    {
        switch(a_MessageType)
        {
        case WM_SIZE:
            handleResize(a_Parameter1, LOWORD(a_Parameter2), HIWORD(a_Parameter2));
            return 0;
        case WM_ENTERSIZEMOVE:
            m_WindowState = EWindowState::Resizing;
            return 0;
        case WM_EXITSIZEMOVE:
            m_WindowState = EWindowState::Original;
            onResize();
            return 0;
            // The WM_MENUCHAR message is sent when a menu is active and the user presses 
            // a key that does not correspond to any mnemonic or accelerator key. 
        case WM_MENUCHAR:
            // Don't beep when we alt-enter.
            return MAKELRESULT(0, MNC_CLOSE);
        }
        return m_EventQueue.handleWindowEvent(a_Window, a_MessageType, a_Parameter1, a_Parameter2);
    }

    LRESULT Window::handleWindowEvent(HWND a_Window, UINT a_MessageType, WPARAM a_Parameter1, LPARAM a_Parameter2)
    {
        auto windowInstance = reinterpret_cast<Window*>(GetWindowLongPtr(a_Window, GWLP_USERDATA));
        return windowInstance->processEvent(a_Window, a_MessageType, a_Parameter1, a_Parameter2);
    }
}