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
	
	/// <summary>
	/// The blue triangel rendered on the screen
	/// </summary>
	Triangle m_BlueTriangle = Triangle(1.0f, XMVectorSet(0.0f, 0.0f, 1.0f, 1.0f));
	
	/// <summary>
	/// The partially transparent yellow triangle
	/// </summary>
	Triangle m_YellowTriangle = Triangle(1.0f, XMVectorSet(1.0f, 1.0f, 0.0f, 0.5f));
	
	/// <summary>
	/// The triangle occluding the other two triangles partially
	/// </summary>
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
	/// <summary>
	/// Initialises the shader at the given file path
	/// </summary>
	/// <param name="a_FilePath">The path to the shader </param>
	/// <returns> The resource handle to the shader </returns>
	ID3DX11Effect* InitialiseShader(const std::wstring& a_FilePath);
	
	/// <summary>
	/// Builds the vertex layout using the given reference shader
	/// </summary>
	/// <remarks> 
	/// Reference shader is necessary since Direct3D does not allow building
	/// an input layout without one
	/// </remarks>
	/// <param name="a_ReferenceShader">The a_ reference shader.</param>
	void BuildVertexLayout(ID3DX11Effect* a_ReferenceShader);
};