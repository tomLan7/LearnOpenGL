#pragma once
#include"Vector3F.h"
#include"Matrix4F.h"
#include<iostream>
namespace lan {

    class Pipeline
    {
        Vector3F worldScale;
        Vector3F worldOffset;
        Vector3F worldRotation;
        Matrix4F worldTransformation;
        bool isWorldTransDirty = false;

        struct {
            Vector3F Pos;
            Vector3F Target;
            Vector3F Up;
        } m_camera;
        Matrix4F m_persProj;
        Matrix4F cameraTransformation;
        bool isCemeraTransDirty=false;

        Matrix4F transformation;
    public:
        Pipeline() {
            //setPerspectiveProj(30.0f, 1.f, 0.3f, 1.0f);
        }
        void initScale(float ScaleX, float ScaleY, float ScaleZ) {
            isWorldTransDirty = true;
            worldScale = {ScaleX,ScaleY,ScaleZ};
        }
        void initWorldOffset(float x, float y, float z) {
            isWorldTransDirty = true;
            worldOffset = { x,y,z };
        }

        void initRotate(float RotateX, float RotateY, float RotateZ) {
            isWorldTransDirty = true;
            worldRotation = { ToRadian(RotateX),ToRadian(RotateY),ToRadian(RotateZ) };
        }

        Matrix4F getWorldTransform() {
            if (isWorldTransDirty) {
                isWorldTransDirty = false;
                Matrix4F ScaleTrans, RotateTrans, TranslationTrans;
                ScaleTrans = Matrix4F::Scaling(worldScale);
                RotateTrans = Matrix4F::Rotation(worldRotation);
                TranslationTrans = Matrix4F::Translation(worldOffset);
                worldTransformation = TranslationTrans * RotateTrans * ScaleTrans;
            }
            return worldTransformation;
        }

        void initPerspectiveProj(float FOV,float aspectRatio,float zNear, float zFar) {
            isCemeraTransDirty = true;
            m_persProj = Matrix4F::PersProjTransform(FOV,aspectRatio,zNear,zFar);
        }
        
        void initCamera(const Vector3F& position,const Vector3F& Target, const Vector3F& Up) {
            isCemeraTransDirty = true;
            m_camera.Pos = position;
            m_camera.Target = Target;
            m_camera.Up = Up;
        }
        const Matrix4F& GetCameraTransform() {
            if (isCemeraTransDirty) {
                isCemeraTransDirty = false;
                cameraTransformation=m_persProj* Matrix4F::FaceTo(m_camera.Target, m_camera.Up)* Matrix4F::Translation(-m_camera.Pos);
            }
            return cameraTransformation;
        }
        const Matrix4F& GetTransNoProj() {
            return worldTransformation;
        }
        const Matrix4F& GetTransByPerspective() {
            return m_persProj;
        }
        const Matrix4F& GetTransByCameraAndPerspective() {
            return GetCameraTransform();
        }
    };

}

