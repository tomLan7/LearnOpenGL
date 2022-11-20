#pragma once
#include"Vector3F.h"
#include"Matrix4F.h"
namespace lan {
    //���԰�������Χ�任����׼�豸����ϵ�С�
    class Camera {
        //�����λ��
        Vector3F m_pos;
        //�泯����
        Vector3F m_target;
        //�Ϸ���
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

        /// <param name="horizontalAngle">ˮƽ��360�ȶ�����</param>
        /// <param name="verticalAngle">��ֱ�ǣ�������90�ȵ�0�ȡ�</param>
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
