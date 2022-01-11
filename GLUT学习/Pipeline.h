#pragma once
#include"Vector3F.h"
#include"Matrix4F.h"
#include<iostream>
#include"Camera.h"
namespace lan {
    class Pipeline
    {
        Vector3F worldScale;
        Vector3F worldOffset;
        Vector3F worldRotation;
        Matrix4F worldTransformation;
        bool isWorldTransDirty = false;

        static Camera main_camera;
        Matrix4F m_persProj;
        bool isPersProjTransDirty = false;

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
                ScaleTrans = Matrix4F::Scale(worldScale);
                RotateTrans = Matrix4F::Rotate(worldRotation);
                TranslationTrans = Matrix4F::Translate(worldOffset);
                worldTransformation = TranslationTrans * RotateTrans * ScaleTrans;
            }
            return worldTransformation;
        }

        void initPerspectiveProj(float FOV,float aspectRatio,float zNear, float zFar) {
            isPersProjTransDirty = true;
            m_persProj = Matrix4F::PersProjTransform(FOV,aspectRatio,zNear,zFar);
        }
        
        void initCamera(const Vector3F& position,const Vector3F& Target, const Vector3F& Up) {
            main_camera=Camera(position,Target,Up);
        }
        
        const Matrix4F& GetTransNoProj() {
            return worldTransformation;
        }
        //单纯透视变换，没有相机
        const Matrix4F& GetTransByPerspective() {
            return m_persProj;
        }
        //单纯相机变换，不透视
        Matrix4F GetCameraTransform() {
            return main_camera.CameraTransformation();
        }
        //透视和相机
        Matrix4F GetTransByCameraAndPerspective() {
            Matrix4F ct=GetCameraTransform();//拷贝构造方式存到ct变量中
            Matrix4F pt = GetTransByPerspective();//拷贝构造方式存到pt变量中
            return pt*ct;//成功
        }
        static void SpecialKeyboardCB(int Key, int x, int y)
        {
            main_camera.OnKeyboard(Key);
        }
    };

}

