#pragma once
#include"Vector3F.h"
#include"Matrix4F.h"
namespace lan {
    class Camera {
        Vector3F m_pos;
        Vector3F m_target;
        Vector3F m_up;
    public:
        Camera() = default;
        Camera(const Vector3F& Pos, const Vector3F& Target, const Vector3F& Up) :m_pos(Pos), m_target(Target), m_up(Up) {

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
