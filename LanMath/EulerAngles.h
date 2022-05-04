#pragma once
#include<Quaternion.h>
#include<Matrix4F.h>
#include<ConstantDef.h>
namespace lan {

	//heading-pitch-bankŷ����  y,x,z?
	struct EulerAngles
	{

		float heading;//y�ᡣ�ϡ�
		float pitch;//x�ᣬ�ҡ�����
		float bank;//z�ᡣ�������
		EulerAngles() = default;
		EulerAngles(float h, float p, float b){
			heading = h;
			pitch = p;
			bank = b;
		}
		void identity() {
			pitch = bank = heading = 0.0f;
		}
		//ȷ��ŷ���Ǵ������Ƽ��У��磺heading��bank����+180��-180֮�䣬pitch������90��-90֮�䡣
		void canonize() {
			pitch = std::min(PiOver2,pitch);
			pitch = std::max(-PiOver2, pitch);
			
			if (fabsf(pitch) == PiOver2) {
				heading += bank;
				bank = 0;
			}
			bank=wrapPi(bank);
			heading = wrapPi(heading);
		}
		void fromObjectToInertialQuaternion(const Quaternion& q) {

		}
		void fromInertialToObjectQuaternion(const Quaternion& q) {

		}

		void fromObjectToWorldMatrix(const Matrix4F& m);
		void fromWorldToObjectMatrix(const Matrix4F& m);

		void fromRotationMatrix(const Matrix4F& rotation);
		static const EulerAngles Identity;
	};
}

