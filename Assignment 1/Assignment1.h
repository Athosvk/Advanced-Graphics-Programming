#include <d3dApp.h>

#include "Prism.h"

class Assignment1 : public D3DApp
{
private:
    static const float KeyProcessInterval;

    ID3D11Buffer* mBoxVB;
    ID3D11Buffer* mBoxIB;

    ID3DX11Effect* mFX;
    ID3DX11EffectTechnique* mTech;
    ID3DX11EffectMatrixVariable* mfxWorldViewProj;
    ID3DX11EffectScalarVariable* mfxRotation;

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
    Prism mPrism = Prism(3, 3.0f, XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));

    float mKeyTimer = 0.0f;

public:
    Assignment1(HINSTANCE hInstance);
    ~Assignment1();

    bool Init();
    void OnResize();
    void UpdateScene(float dt);
    void DrawScene();

    void OnMouseDown(WPARAM btnState, int x, int y);
    void OnMouseUp(WPARAM btnState, int x, int y);
    void OnMouseMove(WPARAM btnState, int x, int y);

private:
    void BuildGeometryBuffers();
    void BuildFX();
    void BuildVertexLayout();
    void CreateRasterizerStates();
    void UpdateGeometry();
};