#include"Camera.h"
#include "glut.h"
#include<iostream>
using namespace std;
#define StepSize 1.0
bool lan::Camera::OnKeyboard(int Key,bool spicial)
{
    bool Ret = false;
    if (spicial) {
        switch (Key) {
        case GLUT_KEY_UP:
        {
            auto face = Face();
            m_pos += (face * StepSize);
            m_target += (face * StepSize);
            Ret = true;
        }
        break;
        case GLUT_KEY_DOWN:
        {
            auto face = Face();
            m_pos -= (face * StepSize);
            m_target -= (face * StepSize);
            Ret = true;
        }
        break;
        case GLUT_KEY_LEFT:
        {

            Vector3F Left = Vector3F::cross(Face(), m_up);//Unity是左手坐标系
            Left.normalized();
            Left *= StepSize;
            m_pos += Left;
            m_target += Left;
            Ret = true;
        }
        break;

        case GLUT_KEY_RIGHT:
        {
            Vector3F Right = Vector3F::cross(m_up, Face());
            Right.normalized();
            Right *= StepSize;
            m_pos += Right;
            m_target += Right;
            Ret = true;
        }
        break;
        }
    }else{
        switch (Key) {
        case 'w':
        {
            auto face = Face();
            m_pos += (face * StepSize);
            m_target += (face * StepSize);
            Ret = true;
        }
        break;

        case 's':
        {
            auto face = Face();
            m_pos -= (face * StepSize);
            m_target -= (face * StepSize);
            Ret = true;
        }
        break;

        case 'a':
        {

            Vector3F Left = Vector3F::cross(Face(), m_up);//Unity是左手坐标系
            Left.normalized();
            Left *= StepSize;
            m_pos += Left;
            m_target += Left;
            Ret = true;
        }
        break;

        case 'd':
        {
            Vector3F Right = Vector3F::cross(m_up, Face());
            Right.normalized();
            Right *= StepSize;
            m_pos += Right;
            m_target += Right;
            Ret = true;
        }
        break;
        case 'q':
            m_pos += (GetUp() * StepSize);
            m_target += (GetUp() * StepSize);
            break;
        case 'e':
            m_pos -= (GetUp() * StepSize);
            m_target -= (GetUp() * StepSize);
            break;
        }
    }
    return Ret;
}