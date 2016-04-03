#pragma once
#include "Box.h"
#include "Quad.h"

class Phone
{
private:
    Box m_Box = Box(XMVectorSet(0.4f, 1.0f, 0.1f, 0.0f), L"Assets/Textures/Phone.png");
    ID3DX11Effect* m_Shader;
    Quad m_Display = Quad(XMVectorSet(0.32f, 0.7f, 0.0f, 0.0f), L"Assets/Textures/Display.png");

public:
    Phone();
    ~Phone();

    void setShader(ID3DX11Effect* a_Shader);
    void initialise(ID3D11Device* a_Device);
    void draw(ID3D11DeviceContext* a_Context, CXMMATRIX a_ViewProjection);
};

