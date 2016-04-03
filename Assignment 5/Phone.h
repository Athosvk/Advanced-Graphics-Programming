#pragma once
#include "Box.h"

class Phone
{
private:
    Box m_Box = Box(XMVectorSet(0.4f, 1.0f, 0.1f, 0.0f), L"Assets/Textures/Phone.png");
    ID3DX11Effect* m_Shader;

public:
    Phone();
    ~Phone();

    void setShader(ID3DX11Effect* a_Shader);
    void initialise(ID3D11Device* a_Device);
    void draw(ID3D11DeviceContext* a_Context, CXMMATRIX a_ViewProjection);
};

