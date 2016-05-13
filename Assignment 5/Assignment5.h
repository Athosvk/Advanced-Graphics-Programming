#include <Common/d3dApp.h>

#include "Box.h"
#include "Phone.h"

class Assignment5 : public D3DApp
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
	/// The dice in the scene that is to be 'recorded' by the phone's camera
	/// </summary>
	Box m_Box = Box(XMVectorSet(1.0f, 1.0f, 1.0f, 0.0f), L"Assets/Textures/Dice.png");	
	/// <summary>
	/// The phone recording the contents of the scene through it's camera
	/// </summary>
	Phone m_Phone;

public:
    Assignment5(HINSTANCE hInstance);
    ~Assignment5();

    bool Init();
    void OnResize();
    void UpdateScene(float dt);
	
	/// <summary>
	/// Draws the scene to the display of the phone
	/// </summary>
	void drawToDisplay();
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