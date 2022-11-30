#pragma once
#include"Vector3F.h"
#include"Matrix4F.h"
#include "ConstantDef.h"
namespace lan {
    //可以把其他范围变换到标准设备坐标系中。
    class Camera {
        //摄像机位置
        Vector3F m_pos;
        //目标点，不是面朝方向
        Vector3F m_target;//默认的上方向是0,0,1，也就是仿照unity，z正方向向前
        //上方向
        Vector3F m_up;//默认的上方向是0,1,0，也就是仿照unity，y轴向上
        /// <summary>
        /// 俯仰角Pitch、偏航角Yaw和滚转角Roll
        /// </summary>
        float horizontalAngle;
        float verticalAngle;
        static constexpr float MAXHorizontalAngle=360.f;
        static constexpr float MinHorizontalAngle = 0.f;
        static constexpr float MaxVerticalAngle = 90.f;
        static constexpr float MinVerticalAngle = -90.f;


    public:
        Camera() = default;
        Camera(const Vector3F& Pos, const Vector3F& Target, const Vector3F& Up) :m_pos(Pos), m_target(Target), m_up(Up) {

        }


        /// <param name="horizontalAngle">水平角360度都可以</param>
        /// <param name="verticalAngle">垂直角，限制在90度到0度。</param>
        void setHVAngle(float horizontalAngle, float verticalAngle) {
            horizontalAngle = fmodf(horizontalAngle, MAXHorizontalAngle- MinHorizontalAngle)+MinHorizontalAngle;
            verticalAngle = clamp(verticalAngle, MinVerticalAngle, MaxVerticalAngle);
            auto faceLengh=Face().length();
            auto newFaceVec = Vector3F(sinf(horizontalAngle * Deg2Rad), sinf(verticalAngle * Deg2Rad), cosf(horizontalAngle * Deg2Rad));
            newFaceVec.normalized();
            m_target = m_pos+ newFaceVec* faceLengh;
            std::cout << "实际的h"<<horizontalAngle<<"实际的v"<<verticalAngle << std::endl;
            std::cout<<toString()<<std::endl;
        }
        bool OnKeyboard(int Key,bool spicial);
        const Vector3F& GetPos() const {
            return m_pos;
        }
        const Vector3F& GetTarget() const {
            return m_target;
        }
        const Vector3F& GetUp() const {
            return m_up;
        }

        /// 获得面朝向量
        const Vector3F Face() {
            return m_target - m_pos;
        }

        Matrix4F CameraTransformation() {
            Matrix4F face=Matrix4F::FaceTo(Face(), m_up);
            Matrix4F postionOffset = Matrix4F::Translate(-m_pos);
            Matrix4F resultMat = face * postionOffset;
            return resultMat;
        }

        std::string toString() {
            std::ostringstream str;
            str << "[camera,pos:" << m_pos << ",target:" << m_target << ",up:" << m_up << "]";
            return str.str();
        }
    };
}
