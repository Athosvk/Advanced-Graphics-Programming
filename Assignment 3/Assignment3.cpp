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
#include "Assignment3.h"

Assignment3::Assignment3(HINSTANCE hInstance)
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
    auto position = XMVectorSet(-0.5f, 0.1f, 0.0f, 0.0f);
    m_YellowTriangle.setPosition(position);
    position = XMVectorSet(-0.3f, 0.0f, 0.0f, 0.0f);
    m_OccludingTriangle.setPosition(position);
}

Assignment3::~Assignment3()
{
	ReleaseCOM(mInputLayout);
}

bool Assignment3::Init()
{
    if(!D3DApp::Init())
    {
        return false;
    }

    md3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    m_YellowTriangle.initialiseBuffers(md3dDevice);
    m_BlueTriangle.initialiseBuffers(md3dDevice);
    m_OccludingTriangle.initialiseBuffers(md3dDevice);

    auto occludedShader = InitialiseShader(L"Occluded.fx");
    m_YellowTriangle.setShader(occludedShader);
    m_BlueTriangle.setShader(occludedShader);

    m_OccludingTriangle.setShader(InitialiseShader(L"OcclusionMark.fx"));
    BuildVertexLayout(occludedShader);
    md3dImmediateContext->IASetInputLayout(mInputLayout);
	return true;
}

void Assignment3::OnResize()
{
	D3DApp::OnResize();

	// The window resized, so update the aspect ratio and recompute the projection matrix.
	XMMATRIX P = XMMatrixPerspectiveFovLH(0.25f*MathHelper::Pi, AspectRatio(), 1.0f, 1000.0f);
	XMStoreFloat4x4(&mProj, P);
}

void Assignment3::UpdateScene(float dt)
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

void Assignment3::DrawScene()
{
    auto backgroundColor = XMVectorSet(0.5f, 0.5f, 0.5f, 0.0f);
	md3dImmediateContext->
        ClearRenderTargetView(mRenderTargetView, reinterpret_cast<const float*>(&backgroundColor));
	md3dImmediateContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH|D3D11_CLEAR_STENCIL, 1.0f, 0);

	XMMATRIX view  = XMLoadFloat4x4(&mView);
	XMMATRIX proj  = XMLoadFloat4x4(&mProj);
	XMMATRIX viewProj = view*proj;

    md3dImmediateContext->OMSetRenderTargets(0, nullptr, mDepthStencilView);
    m_OccludingTriangle.draw(md3dImmediateContext, viewProj);
    md3dImmediateContext->OMSetRenderTargets(1, &mRenderTargetView, mDepthStencilView);
    m_BlueTriangle.draw(md3dImmediateContext, viewProj);
    m_YellowTriangle.draw(md3dImmediateContext, viewProj);
	HR(mSwapChain->Present(0, 0));
}

void Assignment3::OnMouseDown(WPARAM btnState, int x, int y)
{
	mLastMousePos.x = x;
	mLastMousePos.y = y;

	SetCapture(mhMainWnd);
}

void Assignment3::OnMouseUp(WPARAM btnState, int x, int y)
{
	ReleaseCapture();
}

void Assignment3::OnMouseMove(WPARAM btnState, int x, int y)
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

ID3DX11Effect* Assignment3::InitialiseShader(const std::wstring& a_FilePath)
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
    ID3DX11Effect* shader;
	HR(D3DX11CreateEffectFromMemory(compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), 
		0, md3dDevice, &shader));

	// Done with compiled shader.
	ReleaseCOM(compiledShader);
    return shader;
}

void Assignment3::BuildVertexLayout(ID3DX11Effect* a_ReferenceShader)
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
    a_ReferenceShader->GetTechniqueByIndex(0)->GetPassByIndex(0)->GetDesc(&passDesc);
	HR(md3dDevice->CreateInputLayout(vertexDesc, 3, passDesc.pIAInputSignature, 
		passDesc.IAInputSignatureSize, &mInputLayout));
}