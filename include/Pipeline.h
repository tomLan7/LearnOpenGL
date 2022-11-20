#pragma once
#include"Vector3F.h"
#include"Matrix4F.h"
#include<iostream>
#include"Camera.h"
namespace lan {
    /*
    * ��ģ�͡���Դ������������ӵ�����
    * CPU�޳�����������Ⱦ˳����Ⱦ˳����ȾĿ�꣬��Ⱦģʽ��DrawCall
    */
    class Pipeline
    {
        Vector3F worldScale;
        Vector3F worldOffset;
        Vector3F worldRotation;
        Matrix4F worldTransformation;

        static Camera main_camera;
        Matrix4F m_persProj;
        bool isPersProjTransDirty = false;

        Matrix4F transformation;
    public:
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

        /// �����ǽǶ�
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
            main_camera=Camera(position, Face,Up);
        }
        //û��͸�Ӻ����
        Matrix4F GetTransNoProj() {
            return getWorldTransform();
        }
        //����͸�ӱ任��û�����
        const Matrix4F& GetTransByPerspective() {
            return m_persProj;
        }
        //��������任����͸��
        Matrix4F GetCameraTransform() {
            return main_camera.CameraTransformation();
        }
        //͸�Ӻ����
        Matrix4F GetTransByCameraAndPerspective() {
            Matrix4F ct=GetCameraTransform();//�������췽ʽ�浽ct������
            Matrix4F pt = GetTransByPerspective();//�������췽ʽ�浽pt������
            return pt*ct;//�ɹ�
        }
        static void SpecialKeyboardCB(int Key, int x, int y)
        {
            std::cout << "key��"<<Key<<"��x��"<<x<<"��y��"<<y << std::endl;
            main_camera.OnKeyboard(Key);
        }
    };

}

