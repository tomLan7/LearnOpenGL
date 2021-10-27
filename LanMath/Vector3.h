#pragma once
#include<cmath>
#include<ostream>
#include<string>
#include<sstream>
namespace lan {
	struct Vector3F
	{
		float x=0.f;
		float y=0.f;
		float z=0.f;
		Vector3F() = default;

		Vector3F(float x, float y, float z){
			setValue(x,y,z);
		}

		Vector3F(const Vector3F&) = default;

		void setValue(float x, float y, float z) {
			this->x = x;
			this->y = y;
			this->z = z;
		}

		//一些操作

		auto length()const{
			return powf(powf(x,2)+powf(y,2) + powf(z, 2),0.5);
		}

		Vector3F unit()const {
			return *this / length();
		}

		Vector3F operator-()const {
			return *this * -1;
		}

		//四则运算
		Vector3F operator+(const Vector3F& vec)const {
			return Vector3F(x + vec.x, y + vec.y, z + vec.z);
		}

		Vector3F& operator+=(const Vector3F& vec) {
			x *= vec.x;
			y *= vec.y;
			z *= vec.z;
			return *this;
		}
		Vector3F operator-(const Vector3F& vec)const {
			return Vector3F(x - vec.x, y - vec.y, z - vec.z);
		}

		Vector3F& operator-=(const Vector3F& vec) {
		
			return *this+=(-vec);
		}

		Vector3F& operator*=(float factor) {
			x *= factor;
			y *= factor;
			z *= factor;
			return *this;
		}

		Vector3F operator*(float factor) const {
			auto tem = *this;
			tem *= factor;
			return tem;
		}
		float operator*(Vector3F vec)const {
			return x * vec.x + y * vec.y + z * vec.z;
		}

		Vector3F& operator/=(float factor) {
			*this *= (1 / factor);
			return *this;
		}

		Vector3F operator/(float factor)const {
			auto tem = *this;
			tem /= factor;
			return tem;
		}

		//静态方法，这些方法适合该方式调用比较直观
		static float distant(const Vector3F& a, const Vector3F& b) {
			return (a - b).length();
		}
		static Vector3F cross(const Vector3F& a,const Vector3F& b) {
			return Vector3F(a.y*b.z-a.z*b.y,a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x);
		}
		//a投影到b上
		static Vector3F projection(const Vector3F& a, const Vector3F& b) {
			return b.unit()* ((a * b) / b.length());
		}
		//获得a到b的夹角余弦
		static float angleCos(const Vector3F& a, const Vector3F& b) {
			return (a* b) / (a.length() * b.length());
		}

		//根据入射光线和法线求反射光线
		static Vector3F reflect(const Vector3F& incident, const Vector3F& normal) {
			return incident+projection(-incident, normal)*2;
		}

		static const Vector3F zero;

		std::string toString()const {
			std::ostringstream str;
			str << "[" << x << "," << y << "," << z << "]";
			return str.str();
		}
	};
	
}
static std::ostream& operator<<(std::ostream& out, const lan::Vector3F& vec) {
	out << vec.toString();
	return out;
}