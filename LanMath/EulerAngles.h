#pragma once
#include<Quaternion.h>
#include<Matrix4F.h>
#include<ConstantDef.h>
namespace lan {

	//heading-pitch-bank欧拉角  y,x,z?
	struct EulerAngles
	{

		float heading;//y轴。上。
		float pitch;//x轴，右。俯角
		float bank;//z轴。向摄像机
		EulerAngles() = default;
		EulerAngles(float h, float p, float b){
			heading = h;
			pitch = p;
			bank = b;
		}
		void identity() {
			pitch = bank = heading = 0.0f;
		}
		//确保欧拉角处于限制集中，如：heading和bank限制+180到-180之间，pitch限制在90到-90之间。
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

