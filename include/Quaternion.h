#pragma once
#include<cmath>
#include <Vector3F.h>
#include<ConstantDef.h>
namespace lan {
	struct Quaternion
	{
		float x = 0;
		float y = 0;
		float z = 0;
		float w = 1;
		Quaternion(float x,float y,float z,float w) {
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}
		Quaternion(Vector3F v, float w) {
			this->x = v.x;
			this->y = v.y;
			this->z = v.z;
			this->w = w;
		}
		/// <summary>
		/// 当rate为0结果为a，当rate为1结果为b
		/// </summary>
		static Quaternion Lerp(const Quaternion& a,const Quaternion& b, float rate) {
			return Quaternion(a.x+(b.x-a.x)*rate, a.y + (b.y - a.y) * rate, a.z + (b.z - a.z) * rate, a.w + (b.w - a.w) * rate);
		}

		//共轭
		Quaternion Conjugate() {
			return Quaternion{ -x,-y,-z,w };
		}
		//相反数代表相同的角位移。一个角度加上360°也不会改变q的角位移
		Quaternion operator-() {
			return Quaternion{ -x,-y,-z,-w };
		}


		float Length() {
			return std::powf(std::powf(x, 2) + std::powf(y, 2) + std::powf(z, 2) + std::powf(w, 2),0.5);
		}

		Quaternion Inverse() {
			return Conjugate() / Length();
		}

		Quaternion operator/(float rate) {
			return Quaternion{ x / rate, y / rate, z / rate, w / rate };
		}
		//待测试
		Quaternion operator^(float exponent) {
			float alpha=acos(w);
			float newAlpha = alpha * exponent;
			float newW = cos(newAlpha);
			float mult = sin(newAlpha) / sin(alpha);
			float newX =x* mult;
			float newY =y* mult;
			float newZ =z* mult;
			return Quaternion{newX,newY,newZ,newW};
		}
		//待测试
		Quaternion operator*(Quaternion other) {
			Vector3F v1(x,y,z);
			float w1 = w;
			Vector3F v2(other.x,other.y,other.z);
			float w2 = other.w;
			Vector3F newV=Vector3F::cross(v2,v1)+v2*w1+v1*w2;
			float newW = w1 * w2  - (v1 * v2);
			return Quaternion(newV,newW);
		}
		//待测试
		static float dot(Quaternion a, Quaternion b) {

			Vector3F v1(a.x, a.y, a.z);
			Vector3F v2(b.x, b.y, b.z);
			return a.w * b.w + v1 * v2;
		}
		//待测试，不是最优方法
		static Quaternion slerp(Quaternion start, Quaternion end, float r) {
			return start*((start.Inverse()*end)^r);
		}

		Vector3F  toEuler() {
			double roll=0, pitch=0, yaw=0;
			toEulerAngle(x,y,z,w,roll,pitch,yaw);
			return Vector3F(roll,pitch,yaw);
		}

		//一般推荐y,x,z旋转方式转换为欧拉角。
		//CSDN https://blog.csdn.net/zisuina_2/article/details/102568015
		static void toEulerAngle(const double x, const double y, const double z, const double w, double& roll, double& pitch, double& yaw)
		{
			// roll (x-axis rotation)
			double sinr_cosp = +2.0 * (w * x + y * z);
			double cosr_cosp = +1.0 - 2.0 * (x * x + y * y);
			roll = atan2(sinr_cosp, cosr_cosp);

			// pitch (y-axis rotation)
			double sinp = +2.0 * (w * y - z * x);
			if (fabs(sinp) >= 1)
				pitch = copysign(M_Pi / 2, sinp); // use 90 degrees if out of range
			else
				pitch = asin(sinp);

			// yaw (z-axis rotation)
			double siny_cosp = +2.0 * (w * z + x * y);
			double cosy_cosp = +1.0 - 2.0 * (y * y + z * z);
			yaw = atan2(siny_cosp, cosy_cosp);
			//    return yaw;
		}

		static Quaternion fromEulerAngle(float x,float y,float z) {
			//使用顺序，y，x,z
			Quaternion q_x(sin(x / 2 * Deg2Rad), 0, 0, cos(x / 2 * Deg2Rad));
			Quaternion q_y(0, sin(y / 2 * Deg2Rad), 0, cos(y / 2 * Deg2Rad));
			Quaternion q_z(0, 0, sin(z / 2 * Deg2Rad), cos(z / 2 * Deg2Rad));
			return q_y * q_x * q_z;
		}

		std::string toString()const {
			return "["+std::to_string(x)+","+ std::to_string(y)+","+ std::to_string(z)+","+ std::to_string(w) +"]";
		}
	};

	static std::ostream& operator<<(std::ostream& out, const Quaternion& other) {
		out << other.toString();
		return out;
	}
}
