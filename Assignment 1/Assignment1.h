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
	/// <summary>
	/// The rotation variable in the FX shader, to allow the tesselation shader for rotating the prism
	/// </summary>
	ID3DX11EffectScalarVariable* mfxRotation;

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

    float mTheta;
    float mPhi;
    float mRadius;

    POINT mLastMousePos;	
	/// <summary>
	/// The n-prism rendered
	/// </summary>
	Prism mPrism = Prism(3, 3.0f, XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));
	/// <summary>
	/// The elapsed time in seconds since a key has been pressed
	/// </summary>
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
	/// <summary>
	/// Builds the initial geometry buffers for the Prism to use
	/// </summary>
	void BuildGeometryBuffers();
    void BuildFX();
    void BuildVertexLayout();
	/// <summary>
	/// Creates the rasterizer states to allow switching between wireframe and regular drawing
	/// </summary>
	void CreateRasterizerStates();	
	/// <summary>
	/// Updates the geometry buffers, for when the prism has changed shape
	/// </summary>
	void UpdateGeometry();
};