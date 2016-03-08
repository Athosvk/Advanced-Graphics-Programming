#include <memory>

#include "Mesh.h"

class BoxApp : public D3DApp
{
private:
    static const float KeyProcessInterval;

    ID3DX11Effect* mFX;
    ID3DX11EffectTechnique* mTech;
    ID3DX11EffectMatrixVariable* mfxWorldViewProj;

    ID3D11InputLayout* mInputLayout;
    ID3D11RasterizerState* mWireframeState;
    ID3D11RasterizerState* mRegularState;
    ID3D11RasterizerState* mCurrentState;

    XMFLOAT4X4 mWorld;
    XMFLOAT4X4 mView;
    XMFLOAT4X4 mProj;

    float mTheta;
    float mPhi;
    float mRadius;

    POINT mLastMousePos;

    float mKeyTimer = 0.0f;
    std::unique_ptr<Mesh> m_Mesh = nullptr;

public:
    BoxApp(HINSTANCE hInstance);
    ~BoxApp();

    bool Init();
    void OnResize();
    void UpdateScene(float dt);
    void DrawScene();

    void OnMouseDown(WPARAM btnState, int x, int y);
    void OnMouseUp(WPARAM btnState, int x, int y);
    void OnMouseMove(WPARAM btnState, int x, int y);

private:
    void BuildFX();
    void BuildVertexLayout();
    void CreateRasterizerStates();
};