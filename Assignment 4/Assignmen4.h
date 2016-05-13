#include <memory>
#include <d3dApp.h>
#include <Camera.h>

#include "Model.h"
#include "MeshRenderer.h"

class Assignmen4 : public D3DApp
{
private:
    static const float KeyProcessInterval;

    ID3DX11Effect* mFX;
    ID3DX11EffectTechnique* mTech;
    ID3DX11EffectMatrixVariable* mfxWorldViewProj;
    ID3DX11EffectMatrixVariable* mfxWorld;
    ID3DX11EffectMatrixVariable* mfxWorldInvTranspose;
    ID3DX11EffectVectorVariable* mfxEyePosW;
    ID3DX11EffectVariable* mfxSpotLight;
    ID3DX11EffectVariable* mfxMaterial;

    ID3D11InputLayout* mInputLayout;
	ID3D11InputLayout* mInputLayout;
	/// <summary>
	/// The stored WireFrame rasterizer state, so we can switch to it at run-time
	/// </summary>
	ID3D11RasterizerState* mWireframeState;
	/// <summary>
	/// The stored Regular rasterizer state, so we can switch to it at run-time
	/// </summary>
	ID3D11RasterizerState* mRegularState;
	/// <summary>
	/// The current rasterizerstate, which can be either equal to mWireFrameState or mRegularState
	/// </summary>
	ID3D11RasterizerState* mCurrentState;

    XMFLOAT4X4 mWorld;
    XMFLOAT4X4 mView;
    XMFLOAT4X4 mProj;
    XMFLOAT3 mEyePosW;

    POINT mLastMousePos;
	
	/// <summary>
	/// The elapsed time in seconds since a key has been pressed
	/// </summary>
	float mKeyTimer = 0.0f;
	/// <summary>
	/// The mesh renderer used to store the material along with the model
	/// </summary>
	MeshRenderer m_MeshRenderer;
	/// <summary>
	/// The spot light emmitted by the camera to show the lighting effects
	/// </summary>
	SpotLight m_SpotLight;
	/// <summary>
	/// The camera used to move around in the world
	/// </summary>
	Camera m_Camera;

public:
    Assignmen4(HINSTANCE hInstance);
    ~Assignmen4();

    bool Init();
    void OnResize();
    void UpdateScene(float dt);
    void UpdateCamera();
    void DrawScene();

    void OnMouseDown(WPARAM btnState, int x, int y);
    void OnMouseUp(WPARAM btnState, int x, int y);
    void OnMouseMove(WPARAM btnState, int x, int y);

private:
    void BuildFX();
    void BuildVertexLayout();
	/// <summary>
	/// Creates the rasterizer states to allow switching between wireframe and regular drawing
	/// </summary>
    void CreateRasterizerStates();
};