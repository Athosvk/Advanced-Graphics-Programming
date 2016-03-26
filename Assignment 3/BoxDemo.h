#include <memory>

class BoxApp : public D3DApp
{
private:
    static const float KeyProcessInterval;

    ID3DX11Effect* m_OccludingShader = nullptr;
    ID3DX11Effect* m_OccludedShader = nullptr;
    ID3DX11EffectMatrixVariable* mfxWorldViewProj;

    ID3D11InputLayout* mInputLayout;

    XMFLOAT4X4 mWorld;
    XMFLOAT4X4 mView;
    XMFLOAT4X4 mProj;

    float mTheta;
    float mPhi;
    float mRadius;

    POINT mLastMousePos;

    float mKeyTimer = 0.0f;

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
    ID3DX11Effect* InitialiseShader(const std::wstring& a_FilePath);
    void BuildVertexLayout();
};