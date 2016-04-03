#include <Common/d3dApp.h>

#include "Triangle.h"

class Assignment3 : public D3DApp
{
private:
    ID3D11InputLayout* mInputLayout;

    XMFLOAT4X4 mView;
    XMFLOAT4X4 mProj;

    float mTheta;
    float mPhi;
    float mRadius;

    POINT mLastMousePos;

    Triangle m_BlueTriangle = Triangle(1.0f, XMVectorSet(0.0f, 0.0f, 1.0f, 1.0f));
    Triangle m_YellowTriangle = Triangle(1.0f, XMVectorSet(1.0f, 1.0f, 0.0f, 0.5f));
    Triangle m_OccludingTriangle = Triangle(1.0f, XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f));

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