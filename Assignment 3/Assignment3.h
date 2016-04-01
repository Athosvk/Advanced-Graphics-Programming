#include <Common/d3dApp.h>

#include "Triangle.h"

class Assignment3 : public D3DApp
{
private:
    static const float KeyProcessInterval;

    ID3D11InputLayout* mInputLayout;

    XMFLOAT4X4 mView;
    XMFLOAT4X4 mProj;

    float mTheta;
    float mPhi;
    float mRadius;

    POINT mLastMousePos;

    float mKeyTimer = 0.0f;
    Triangle m_RedTriangle = Triangle(1.0f, Colors::Red);
    Triangle m_BlueTriangle = Triangle(1.0f, Colors::Blue);
    Triangle m_OccludingTriangle = Triangle(1.0f, XMVectorSet(0.0f, 0.0f, 0.0f, 0.1f));

public:
    Assignment3(HINSTANCE hInstance);
    ~Assignment3();

    bool Init();
    void OnResize();
    void UpdateScene(float dt);
    void DrawScene();

    void OnMouseDown(WPARAM btnState, int x, int y);
    void OnMouseUp(WPARAM btnState, int x, int y);
    void OnMouseMove(WPARAM btnState, int x, int y);

private:
    ID3DX11Effect* InitialiseShader(const std::wstring& a_FilePath);
    void BuildVertexLayout(ID3DX11Effect* a_ReferenceShader);
};