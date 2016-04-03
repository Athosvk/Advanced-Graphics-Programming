//***************************************************************************************
// BoxDemo.cpp by Frank Luna (C) 2011 All Rights Reserved.
//
// Demonstrates rendering a colored box.
//
// Controls:
//		Hold the left mouse button down and move the mouse to rotate.
//      Hold the right mouse button down to zoom in and out.
//
//***************************************************************************************
#include "d3dApp.h"
#include "d3dx11Effect.h"
#include "MathHelper.h"
#include "Assignment5.h"

Assignment5::Assignment5(HINSTANCE hInstance)
    : D3DApp(hInstance),
    mInputLayout(0),
    mTheta(1.5f*MathHelper::Pi), mPhi(0.25f*MathHelper::Pi), mRadius(5.0f)
{
    mMainWndCaption = L"Box Demo";

    mLastMousePos.x = 0;
    mLastMousePos.y = 0;

    XMMATRIX I = XMMatrixIdentity();
    XMStoreFloat4x4(&mView, I);
    XMStoreFloat4x4(&mProj, I);
}

Assignment5::~Assignment5()
{
    ReleaseCOM(mInputLayout);
}

bool Assignment5::Init()
{
    if(!D3DApp::Init())
    {
        return false;
    }

    m_Box.initialise(md3dDevice);
    ID3DX11Effect* shader = InitialiseShader(L"Textured.fx");
    m_Box.setShader(shader);
    m_Phone.setShader(shader);
    BuildVertexLayout(shader);
    m_Box.constructVertexBuffer(md3dDevice);
    m_Box.constructIndexBuffer(md3dDevice);
    m_Phone.initialise(md3dDevice);
    md3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    md3dImmediateContext->IASetInputLayout(mInputLayout);

    m_Box.setTransform(XMMatrixRotationRollPitchYaw(22.2f, 45.0f, 45.0f) * 
        XMMatrixTranslation(0.0f, 0.0f, 2.0f));
    return true;
}

void Assignment5::OnResize()
{
    D3DApp::OnResize();

    // The window resized, so update the aspect ratio and recompute the projection matrix.
    XMMATRIX P = XMMatrixPerspectiveFovLH(0.25f*MathHelper::Pi, AspectRatio(), 1.0f, 1000.0f);
    XMStoreFloat4x4(&mProj, P);
    m_Phone.resizeScreen(XMFLOAT2(static_cast<float>(mClientWidth), 
        static_cast<float>(mClientHeight)), md3dDevice);
}

void Assignment5::UpdateScene(float dt)
{
    // Convert Spherical to Cartesian coordinates.
    float x = mRadius*sinf(mPhi)*cosf(mTheta);
    float z = mRadius*sinf(mPhi)*sinf(mTheta);
    float y = mRadius*cosf(mPhi);

    // Build the view matrix.
    XMVECTOR pos = XMVectorSet(x, y, z, 1.0f);
    XMVECTOR target = XMVectorZero();
    XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

    XMMATRIX V = XMMatrixLookAtLH(pos, target, up);
    XMStoreFloat4x4(&mView, V);
}

void Assignment5::drawToDisplay()
{
    m_Phone.setAsRenderTarget(md3dImmediateContext, mDepthStencilView);
    m_Phone.clearScreen(md3dImmediateContext, Colors::LightSteelBlue);

    XMMATRIX view = m_Phone.getCameraTransform();
    XMMATRIX proj = XMLoadFloat4x4(&mProj);
    XMMATRIX viewProj = view * proj;

    m_Box.draw(md3dImmediateContext, viewProj);
    md3dImmediateContext->RSSetViewports(1, &mScreenViewport);
    md3dImmediateContext->OMSetRenderTargets(1, &mRenderTargetView, mDepthStencilView);
}

void Assignment5::DrawScene()
{
    XMFLOAT4 backgroundColor;
    XMStoreFloat4(&backgroundColor, Colors::LightSteelBlue);
    md3dImmediateContext->ClearRenderTargetView(mRenderTargetView, 
        reinterpret_cast<float*>(&backgroundColor));
    md3dImmediateContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    drawToDisplay();
    md3dImmediateContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

    XMMATRIX view = XMLoadFloat4x4(&mView);
    XMMATRIX proj = XMLoadFloat4x4(&mProj);
    XMMATRIX viewProj = view*proj;

    m_Box.draw(md3dImmediateContext, viewProj);
    m_Phone.draw(md3dImmediateContext, viewProj);
    HR(mSwapChain->Present(0, 0));
}

void Assignment5::OnMouseDown(WPARAM btnState, int x, int y)
{
    mLastMousePos.x = x;
    mLastMousePos.y = y;

    SetCapture(mhMainWnd);
}

void Assignment5::OnMouseUp(WPARAM btnState, int x, int y)
{
    ReleaseCapture();
}

void Assignment5::OnMouseMove(WPARAM btnState, int x, int y)
{
    if((btnState & MK_LBUTTON) != 0)
    {
        // Make each pixel correspond to a quarter of a degree.
        float dx = XMConvertToRadians(0.25f*static_cast<float>(x - mLastMousePos.x));
        float dy = XMConvertToRadians(0.25f*static_cast<float>(y - mLastMousePos.y));

        // Update angles based on input to orbit camera around box.
        mTheta += dx;
        mPhi += dy;

        // Restrict the angle mPhi.
        mPhi = MathHelper::Clamp(mPhi, 0.1f, MathHelper::Pi - 0.1f);
    }
    else if((btnState & MK_RBUTTON) != 0)
    {
        // Make each pixel correspond to 0.005 unit in the scene.
        float dx = 0.005f*static_cast<float>(x - mLastMousePos.x);
        float dy = 0.005f*static_cast<float>(y - mLastMousePos.y);

        // Update the camera radius based on input.
        mRadius += dx - dy;

        // Restrict the radius.
        mRadius = MathHelper::Clamp(mRadius, 3.0f, 35.0f);
    }

    mLastMousePos.x = x;
    mLastMousePos.y = y;
}

ID3DX11Effect* Assignment5::InitialiseShader(const std::wstring& a_FilePath)
{
    DWORD shaderFlags = 0;
#if defined( DEBUG ) || defined( _DEBUG )
    shaderFlags |= D3D10_SHADER_DEBUG;
    shaderFlags |= D3D10_SHADER_SKIP_OPTIMIZATION;
#endif

    ID3D10Blob* compiledShader = 0;
    ID3D10Blob* compilationMsgs = 0;
    HRESULT hr = D3DX11CompileFromFile(std::wstring(L"FX/" + a_FilePath).c_str(),
        0, 0, 0, "fx_5_0", shaderFlags,
        0, 0, &compiledShader, &compilationMsgs, 0);

    // compilationMsgs can store errors or warnings.
    if(compilationMsgs != 0)
    {
        MessageBoxA(0, (char*)compilationMsgs->GetBufferPointer(), 0, 0);
        ReleaseCOM(compilationMsgs);
    }

    // Even if there are no compilationMsgs, check to make sure there were no other errors.
    if(FAILED(hr))
    {
        DXTrace(__FILE__, (DWORD)__LINE__, hr, L"D3DX11CompileFromFile", true);
    }
    ID3DX11Effect* shader;
    HR(D3DX11CreateEffectFromMemory(compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(),
        0, md3dDevice, &shader));

    // Done with compiled shader.
    ReleaseCOM(compiledShader);
    return shader;
}

void Assignment5::BuildVertexLayout(ID3DX11Effect* a_ReferenceShader)
{
    // Create the vertex input layout.
    D3D11_INPUT_ELEMENT_DESC vertexDesc[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 28, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "UVCOORDINATES", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 40, D3D11_INPUT_PER_VERTEX_DATA, 0 }
    };

    // Create the input layout
    D3DX11_PASS_DESC passDesc;
    a_ReferenceShader->GetTechniqueByIndex(0)->GetPassByIndex(0)->GetDesc(&passDesc);
    HR(md3dDevice->CreateInputLayout(vertexDesc, 4, passDesc.pIAInputSignature,
        passDesc.IAInputSignatureSize, &mInputLayout));
}