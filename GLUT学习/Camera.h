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
    struct {
        Vector3F Pos;
        Vector3F Target;
        Vector3F Up;
    } m_camera;
    Matrix4F m_persProj;
    Matrix4F WVP;//world+View+Projection
    public:
        Camera() {
            //setPerspectiveProj(160.0f, 1.f, 0.3f, 1.0f);
            initScale(1,1,1);
        }
        void initScale(float ScaleX, float ScaleY, float ScaleZ) {
            isDirty = true;
            m_scale = {ScaleX,ScaleY,ScaleZ};
        }
        void initWorldPos(float x, float y, float z) {
            isDirty = true;
            m_worldPos = { x,y,z };
        }

        void initRotate(float RotateX, float RotateY, float RotateZ) {
            isDirty = true;
            m_rotateInfo = { ToRadian(-RotateX),ToRadian(-RotateY),ToRadian(-RotateZ) };
        }

        void setPerspectiveProj(float FOV,float aspectRatio,float zNear, float zFar) {
            isDirty = true;
            
            const float ar = aspectRatio;//横纵比
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
        void setCemera(const Vector3F& Target, const Vector3F& Up) {
            isDirty = true;
            Vector3F N = Target.unit();//对应新坐标系Z轴
            Vector3F U = Vector3F::cross(Up,Target).unit();//对应新坐标系X轴
            Vector3F V = Vector3F::cross(N,U);//对应新坐标系Y轴
            WVP[0] = Vector4F(U, 0);
            WVP[1] = Vector4F(V, 0);
            WVP[2] = Vector4F(N, 0);
            WVP[3] = Vector4F(0,0,0,1);
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
        const Matrix4F& GetTransByCameraAndPerspective() {
            if (isDirty == false) {
                return m_transformation;
            }
            else {
                m_transformation =  m_persProj * WVP * Matrix4F::Translation(m_worldPos) * Matrix4F::Scaling(m_scale) * Matrix4F::RotationZ(m_rotateInfo.z) * Matrix4F::RotationY(m_rotateInfo.y) * Matrix4F::RotationX(m_rotateInfo.x);
                isDirty = false;
                return m_transformation;
            }
        }
    };

}

