#include "Triangle.h"

Triangle::Triangle(float a_Base, XMVECTOR a_Color)
{
    XMStoreFloat4(&m_Color, a_Color);
}
