#pragma once
#include"Vector3F.h"
#include"Matrix4F.h"
#include<iostream>
#include"Camera.h"
namespace lan {
    /*
    * 有模型、光源、摄像机、粒子等数据
    * CPU剔除，合批，渲染顺序，渲染顺序，渲染目标，渲染模式，DrawCall
    */
    class Pipeline
    {
        Vector3F worldScale;
        Vector3F worldOffset;
        Vector3F worldRotation;
        Matrix4F worldTransformation;

        Camera main_camera;
        Matrix4F m_persProj;
        bool isPersProjTransDirty = false;

        Matrix4F transformation;
    public:
        Camera& getMainCamera() {
            return main_camera;
        }

        Pipeline() {
            //setPerspectiveProj(30.0f, 1.f, 0.3f, 1.0f);

            initWorldRotate(0, 0, 0);
            initWorldScale(1, 1, 1);
            initWorldOffset(0, 0, 0);
        }
        void initWorldScale(float ScaleX, float ScaleY, float ScaleZ) {
            worldScale = {ScaleX,ScaleY,ScaleZ};
        }
        void initWorldOffset(float x, float y, float z) {
            worldOffset = { x,y,z };
        }

        /// 参数是角度
        void initWorldRotate(float RotateX, float RotateY, float RotateZ) {
            worldRotation = { ToRadian(RotateX), ToRadian(RotateY), ToRadian(RotateZ) };
        }
        void initWorldRotate(Vector3F xyz) {
            initWorldRotate(xyz.x,xyz.y,xyz.z);
        }

        Matrix4F getWorldTransform() {
                Matrix4F ScaleTrans, RotateTrans, TranslationTrans;
                ScaleTrans = Matrix4F::Scale(worldScale);
                RotateTrans = Matrix4F::Rotate(worldRotation);
                TranslationTrans = Matrix4F::Translate(worldOffset);
                worldTransformation = TranslationTrans * RotateTrans * ScaleTrans;
            return worldTransformation;
        }
        //
        void initPerspectiveProj(float FOV,float aspectRatio,float zNear, float zFar) {
            isPersProjTransDirty = true;
            m_persProj = Matrix4F::PersProjTransform(FOV,aspectRatio,zNear,zFar);
        }

        void initCamera(const Vector3F& position,const Vector3F& Face, const Vector3F& Up) {
            main_camera=Camera(position, position+Face,Up);
        }
        //没有透视和相机
        Matrix4F GetTransNoProj() {
            return getWorldTransform();
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
        void SpecialKeyboardCB(int Key, int x, int y)
        {
            //std::cout << "key："<<Key<<"和x："<<x<<"和y："<<y << std::endl;
            getMainCamera().OnKeyboard(Key,true);
        }
        void ASCIIKeyboardCB(unsigned char Key, int x, int y)
        {
            //std::cout << "key：" << Key << "和x：" << x << "和y：" << y << std::endl;
            getMainCamera().OnKeyboard(Key,false);
        }
    };

}

