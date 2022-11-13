#include"Camera.h"
#include "glut.h"

#define StepSize 1.0
bool lan::Camera::OnKeyboard(int Key)
{
    bool Ret = false;

    switch (Key) {

    case GLUT_KEY_UP:
    {
        m_pos += (m_target * StepSize);
        Ret = true;
    }
    break;

    case GLUT_KEY_DOWN:
    {
        m_pos -= (m_target * StepSize);
        Ret = true;
    }
    break;

    case GLUT_KEY_LEFT:
    {
        
        Vector3F Left = Vector3F::cross(m_target,m_up);
        Left.unit();
        Left *= StepSize;
        m_pos += Left;
        Ret = true;
    }
    break;

    case GLUT_KEY_RIGHT:
    {
        Vector3F Right = Vector3F::cross(m_up, m_target);
        Right.normalized();
        Right *= StepSize;
        m_pos += Right;
        Ret = true;
    }
    break;
    }

    return Ret;
}
