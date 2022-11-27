#pragma once
#include"Vector3F.h"
#include"Matrix4F.h"
#include "ConstantDef.h"
namespace lan {
    //���԰�������Χ�任����׼�豸����ϵ�С�
    class Camera {
        //�����λ��
        Vector3F m_pos;
        //Ŀ��㣬�����泯����
        Vector3F m_target;//Ĭ�ϵ��Ϸ�����0,0,1��Ҳ���Ƿ���unity��z��������ǰ
        //�Ϸ���
        Vector3F m_up;//Ĭ�ϵ��Ϸ�����0,1,0��Ҳ���Ƿ���unity��y������
        /// <summary>
        /// ������Pitch��ƫ����Yaw�͹�ת��Roll
        /// </summary>
        float horizontalAngle;
        float verticalAngle;
        static constexpr float MAXHorizontalAngle=360.f;
        static constexpr float MinHorizontalAngle = 0.f;
        static constexpr float MaxVerticalAngle = 90.f;
        static constexpr float MinVerticalAngle = 0.f;


    public:
        Camera() = default;
        Camera(const Vector3F& Pos, const Vector3F& Target, const Vector3F& Up) :m_pos(Pos), m_target(Target), m_up(Up) {

        }


        /// <param name="horizontalAngle">ˮƽ��360�ȶ�����</param>
        /// <param name="verticalAngle">��ֱ�ǣ�������90�ȵ�0�ȡ�</param>
        void setHVAngle(float horizontalAngle, float verticalAngle) {
            horizontalAngle = fmodf(horizontalAngle, MAXHorizontalAngle- MinHorizontalAngle)+MinHorizontalAngle;
            verticalAngle = clamp(verticalAngle, MinVerticalAngle, MaxVerticalAngle);
            auto faceLengh=Face().length();
            auto newFaceVec = Vector3F(sinf(horizontalAngle * Deg2Rad), sinf(verticalAngle * Deg2Rad), cosf(horizontalAngle * Deg2Rad));
            newFaceVec.normalized();
            m_target = m_pos+ newFaceVec* faceLengh;
            std::cout << "ʵ�ʵ�h"<<horizontalAngle<<"ʵ�ʵ�v"<<verticalAngle << std::endl;
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
        
        /// ����泯����
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
