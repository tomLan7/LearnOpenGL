#pragma once
#include"Vector3F.h"
#include"Matrix4F.h"
#include<iostream>
namespace lan {
    class Camera
    {
#define M_PI 3.14159f
#define ToRadian(x) ((x) * M_PI / 180.0f)
#define ToDegree(x) ((x) * 180.0f / M_PI)
        Vector3F m_scale;
        Vector3F m_worldPos;
        Vector3F m_rotateInfo;
        Matrix4F m_transformation;

        bool isDirty = false;
    public:
        Matrix4F m_persProj;
        void Scale(float ScaleX, float ScaleY, float ScaleZ) {
            isDirty = true;
            m_scale = {ScaleX,ScaleY,ScaleZ};
        }
        void WorldPos(float x, float y, float z) {
            isDirty = true;
            m_worldPos = { x,y,z };
        }

        void Rotate(float RotateX, float RotateY, float RotateZ) {
            isDirty = true;
            m_rotateInfo = { ToRadian(-RotateX),ToRadian(-RotateY),ToRadian(-RotateZ) };
        }

        void SetPerspectiveProj(float FOV,float aspectRatio,float zNear, float zFar) {
            isDirty = true;
            
            const float ar = aspectRatio;//ºá×Ý±È
            const float zRange = zNear - zFar;
            const float tanHalfFOV = tanf(ToRadian(FOV / 2.0));

            m_persProj[0][0] = 1.0f / (tanHalfFOV * ar);
            m_persProj[0][1] = 0.0f;
            m_persProj[0][2] = 0.0f;
            m_persProj[0][3] = 0.0f;

            m_persProj[1][0] = 0.0f;
            m_persProj[1][1] = 1.0f / tanHalfFOV;
            m_persProj[1][2] = 0.0f;
            m_persProj[1][3] = 0.0f;

            m_persProj[2][0] = 0.0f;
            m_persProj[2][1] = 0.0f;
            m_persProj[2][2] = (-zNear - zFar) / zRange;
            m_persProj[2][3] = 1.0f;

            m_persProj[3][0] = 0.0f;
            m_persProj[3][1] = 0.0f;
            m_persProj[3][2] = 2.0f * zFar * zNear / zRange;
            m_persProj[3][3] = 0.0f;
        }
        const Matrix4F& GetTransNoProj() {
            if (isDirty == false) {
                return m_transformation;
            }
            else {
                m_transformation= Matrix4F::Translation(m_worldPos)* Matrix4F::Scaling(m_scale)* Matrix4F::RotationZ(m_rotateInfo.z)*Matrix4F::RotationY(m_rotateInfo.y)*Matrix4F::RotationX(m_rotateInfo.x);
                isDirty = false;
                return m_transformation;
            } 
        }
        const Matrix4F& GetTransByPerspective() {
            if (isDirty == false) {
                return m_transformation;
            }
            else {
                m_transformation= m_persProj*Matrix4F::Translation(m_worldPos)* Matrix4F::Scaling(m_scale)* Matrix4F::RotationZ(m_rotateInfo.z)*Matrix4F::RotationY(m_rotateInfo.y)*Matrix4F::RotationX(m_rotateInfo.x);
                isDirty = false;
                return m_transformation;
            }
        }
    };

}

