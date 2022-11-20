#pragma once
#include"Vector3F.h"
#include"Matrix4F.h"
namespace lan {
    //可以把其他范围变换到标准设备坐标系中。
    class Camera {
        //摄像机位置
        Vector3F m_pos;
        //面朝方向
        Vector3F m_target;
        //上方向
        Vector3F m_up;

        float horizontalAngle;
        float verticalAngle;

    public:
        Camera() = default;
        Camera(const Vector3F& Pos, const Vector3F& Target, const Vector3F& Up) :m_pos(Pos), m_target(Target), m_up(Up) {

        }

        float clamp(float x,float min,float max) {
            if (x < min) {
                x = min;
            }else
            if (x > max) {
                x = max;
            }
        }

        /// <param name="horizontalAngle">水平角360度都可以</param>
        /// <param name="verticalAngle">垂直角，限制在90度到0度。</param>
        void setHVAngle(float horizontalAngle, float verticalAngle) {
            horizontalAngle = fmodf(horizontalAngle, 360);
            verticalAngle = clamp(verticalAngle, 0, 90);

        }
        bool OnKeyboard(int Key);
        const Vector3F& GetPos() const {
            return m_pos;
        }
        const Vector3F& GetTarget() const {
            return m_target;
        }
        const Vector3F& GetUp() const {
            return m_up;
        }
        Matrix4F CameraTransformation() {
            Matrix4F face=Matrix4F::FaceTo(m_target, m_up);
            Matrix4F postionOffset = Matrix4F::Translate(-m_pos);
            Matrix4F resultMat = face * postionOffset;
            return resultMat;
        }
    };
}
