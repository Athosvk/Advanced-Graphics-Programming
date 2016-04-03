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
    ID3D11RasterizerState* mWireframeState;
    ID3D11RasterizerState* mRegularState;
    ID3D11RasterizerState* mCurrentState;

    XMFLOAT4X4 mWorld;
    XMFLOAT4X4 mView;
    XMFLOAT4X4 mProj;
    XMFLOAT3 mEyePosW;

    POINT mLastMousePos;

    float mKeyTimer = 0.0f;
    MeshRenderer m_MeshRenderer;
    SpotLight m_SpotLight;
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
    void CreateRasterizerStates();
};