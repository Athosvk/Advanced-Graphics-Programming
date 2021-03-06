#include <Common/d3dApp.h>

#include "Quad.h"

class Assignment6 : public D3DApp
{
private:
    ID3D11InputLayout* mInputLayout;

    XMFLOAT4X4 mView;
    XMFLOAT4X4 mProj;

    float mTheta;
    float mPhi;
    float mRadius;

    POINT mLastMousePos;	
	/// <summary>
	/// The quad to render the shader on
	/// </summary>
	Quad m_Quad;

public:
    Assignment6(HINSTANCE hInstance);
    ~Assignment6();

    bool Init();
    void OnResize();
    void UpdateScene(float dt);
    void DrawScene();

    void OnMouseDown(WPARAM btnState, int x, int y);
    void OnMouseUp(WPARAM btnState, int x, int y);
    void OnMouseMove(WPARAM btnState, int x, int y);

private:
	/// <summary>
	/// Initialises/creates the shader at the given file path, to be used for rendering
	/// </summary>
	/// <param name="a_FilePath">The path to the shader file </param>
	/// <returns> The handle to the shader </returns>
    ID3DX11Effect* InitialiseShader(const std::wstring& a_FilePath);
    void BuildVertexLayout(ID3DX11Effect* a_ReferenceShader);
};