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

const float Assignment5::KeyProcessInterval = 0.4f;

Assignment5::Assignment5(HINSTANCE hInstance)
: D3DApp(hInstance), mFX(0), mTech(0),
  mfxWorldViewProj(0), mInputLayout(0), 
  mTheta(1.5f*MathHelper::Pi), mPhi(0.25f*MathHelper::Pi), mRadius(5.0f)
{
	mMainWndCaption = L"Box Demo";
	
	mLastMousePos.x = 0;
	mLastMousePos.y = 0;

	XMMATRIX I = XMMatrixIdentity();
	XMStoreFloat4x4(&mWorld, XMMatrixScalingFromVector(XMVectorSet(0.3f, 0.3f, 0.3f, 1.0f)));
	XMStoreFloat4x4(&mView, I);
	XMStoreFloat4x4(&mProj, I);
    mEnable4xMsaa = true;
}

Assignment5::~Assignment5()
{
	ReleaseCOM(mFX);
	ReleaseCOM(mInputLayout);
    ReleaseCOM(mWireframeState);
    ReleaseCOM(mRegularState);
}

bool Assignment5::Init()
{
    if(!D3DApp::Init())
    {
        return false;
    }

    CreateRasterizerStates();
	BuildFX();
	BuildVertexLayout();
    md3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    m_Mesh = std::make_unique<Model>("Assets/Models/Zombie.fbx", md3dDevice);
	return true;
}

void Assignment5::OnResize()
{
	D3DApp::OnResize();

	// The window resized, so update the aspect ratio and recompute the projection matrix.
	XMMATRIX P = XMMatrixPerspectiveFovLH(0.25f*MathHelper::Pi, AspectRatio(), 1.0f, 1000.0f);
	XMStoreFloat4x4(&mProj, P);
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

    if(GetAsyncKeyState('1') & 0x8000 && mKeyTimer >= KeyProcessInterval)
    {
        mKeyTimer -= KeyProcessInterval;
        mCurrentState = mCurrentState == mWireframeState ? mRegularState : mWireframeState;
        md3dImmediateContext->RSSetState(mCurrentState);
    }
    mKeyTimer += dt;
}

void Assignment5::DrawScene()
{
	md3dImmediateContext->ClearRenderTargetView(mRenderTargetView, reinterpret_cast<const float*>(&Colors::LightSteelBlue));
	md3dImmediateContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH|D3D11_CLEAR_STENCIL, 1.0f, 0);

	md3dImmediateContext->IASetInputLayout(mInputLayout);
    m_Mesh->bind(md3dImmediateContext);

	// Set constants
	XMMATRIX world = XMLoadFloat4x4(&mWorld);
	XMMATRIX view  = XMLoadFloat4x4(&mView);
	XMMATRIX proj  = XMLoadFloat4x4(&mProj);
	XMMATRIX worldViewProj = world*view*proj;

	mfxWorldViewProj->SetMatrix(reinterpret_cast<float*>(&worldViewProj));

    D3DX11_TECHNIQUE_DESC techDesc;
    mTech->GetDesc( &techDesc );
    for(UINT p = 0; p < techDesc.Passes; ++p)
    {
        mTech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
        
        m_Mesh->draw(md3dImmediateContext);
    }

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
	if( (btnState & MK_LBUTTON) != 0 )
	{
		// Make each pixel correspond to a quarter of a degree.
		float dx = XMConvertToRadians(0.25f*static_cast<float>(x - mLastMousePos.x));
		float dy = XMConvertToRadians(0.25f*static_cast<float>(y - mLastMousePos.y));

		// Update angles based on input to orbit camera around box.
		mTheta += dx;
		mPhi   += dy;

		// Restrict the angle mPhi.
		mPhi = MathHelper::Clamp(mPhi, 0.1f, MathHelper::Pi-0.1f);
	}
	else if( (btnState & MK_RBUTTON) != 0 )
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

void Assignment5::BuildFX()
{
	DWORD shaderFlags = 0;
#if defined( DEBUG ) || defined( _DEBUG )
    shaderFlags |= D3D10_SHADER_DEBUG;
	shaderFlags |= D3D10_SHADER_SKIP_OPTIMIZATION;
#endif
 
	ID3D10Blob* compiledShader = 0;
	ID3D10Blob* compilationMsgs = 0;
	HRESULT hr = D3DX11CompileFromFile(L"FX/color.fx", 0, 0, 0, "fx_5_0", shaderFlags, 
		0, 0, &compiledShader, &compilationMsgs, 0);

	// compilationMsgs can store errors or warnings.
	if( compilationMsgs != 0 )
	{
		MessageBoxA(0, (char*)compilationMsgs->GetBufferPointer(), 0, 0);
		ReleaseCOM(compilationMsgs);
	}

	// Even if there are no compilationMsgs, check to make sure there were no other errors.
	if(FAILED(hr))
	{
		DXTrace(__FILE__, (DWORD)__LINE__, hr, L"D3DX11CompileFromFile", true);
	}

	HR(D3DX11CreateEffectFromMemory(compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), 
		0, md3dDevice, &mFX));

	// Done with compiled shader.
	ReleaseCOM(compiledShader);

	mTech = mFX->GetTechniqueByName("ColorTech");
	mfxWorldViewProj = mFX->GetVariableByName("gWorldViewProj")->AsMatrix();
}

void Assignment5::BuildVertexLayout()
{
	// Create the vertex input layout.
	D3D11_INPUT_ELEMENT_DESC vertexDesc[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"UVCOORDINATES", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 28, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	// Create the input layout
    D3DX11_PASS_DESC passDesc;
    mTech->GetPassByIndex(0)->GetDesc(&passDesc);
	HR(md3dDevice->CreateInputLayout(vertexDesc, 3, passDesc.pIAInputSignature, 
		passDesc.IAInputSignatureSize, &mInputLayout));
}

void Assignment5::CreateRasterizerStates()
{
    D3D11_RASTERIZER_DESC rasterizerDescription;
    ZeroMemory(&rasterizerDescription, sizeof(D3D11_RASTERIZER_DESC));
    rasterizerDescription.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
    rasterizerDescription.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
    rasterizerDescription.FrontCounterClockwise = false;
    rasterizerDescription.DepthClipEnable = true;
    HR(md3dDevice->CreateRasterizerState(&rasterizerDescription, &mWireframeState));

    rasterizerDescription.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
    HR(md3dDevice->CreateRasterizerState(&rasterizerDescription, &mRegularState));
    mCurrentState = mRegularState;
}