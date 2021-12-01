#pragma once
#include<Vector3F.h>
namespace lan {
	struct  HomogeneousCoordinates4F :Vector3F
	{
		float w = 0.f;//齐次坐标透视系数
		HomogeneousCoordinates4F() = default;

		HomogeneousCoordinates4F(float x, float y, float z, float w) :lan::Vector3F(x, y, z) {
			this->w = w;
		}

		HomogeneousCoordinates4F(Vector3F vec, float w):Vector3F(vec){
			this->w = w;
		}

		HomogeneousCoordinates4F(const lan::HomogeneousCoordinates4F&) = default;

		void setValue(float x, float y, float z, float w) {
			lan::Vector3F::setValue(x, y, z);
			this->w = w;
		}

		//一些操作

		HomogeneousCoordinates4F unit()const {
			return *this / length();
		}

		HomogeneousCoordinates4F operator-()const {
			return *this * -1;
		}
		void perspectiveDivision() {
			if (w != 0) {
				*this /= w;
			}
		}
		//四则运算
		HomogeneousCoordinates4F operator+(const HomogeneousCoordinates4F& vec)const {
			return HomogeneousCoordinates4F(x + vec.x, y + vec.y, z + vec.z,w+vec.w);
		}

		HomogeneousCoordinates4F& operator+=(const HomogeneousCoordinates4F& vec) {
			x += vec.x;
			y += vec.y;
			z += vec.z;
			w += vec.w;
			return *this;
		}
		HomogeneousCoordinates4F operator-(const HomogeneousCoordinates4F& vec)const {
			return HomogeneousCoordinates4F(x - vec.x, y - vec.y, z - vec.z,w-vec.w);
		}

		HomogeneousCoordinates4F& operator-=(const HomogeneousCoordinates4F& vec) {

			return *this += (-vec);
		}

		HomogeneousCoordinates4F& operator*=(float factor) {
			x *= factor;
			y *= factor;
			z *= factor;
			w *= factor;
			return *this;
		}

		HomogeneousCoordinates4F operator*(float factor) const {
			auto tem = *this;
			tem *= factor;
			return tem;
		}
		float operator*(HomogeneousCoordinates4F vec)const {
			return x * vec.x + y * vec.y + z * vec.z+w*vec.w;
		}

		HomogeneousCoordinates4F& operator/=(float factor) {
			*this *= (1 / factor);
			return *this;
		}

		HomogeneousCoordinates4F operator/(float factor)const {
			auto tem = *this;
			tem /= factor;
			return tem;
		}
		float operator[](size_t index)const {
			switch (index)
			{
			case 0:
				return x;
			case 1:
				return y;
			case 2:
				return z;
			case 3:
				return w;
			default:
				throw "异常的向量索引";
				return 0;
				break;
			}
		}
		float& operator[](size_t index){
			switch (index)
			{
			case 0:
				return x;
			case 1:
				return y;
			case 2:
				return z;
			case 3:
				return w;
			default:
				
				break;
			}
			throw "异常的向量索引";
		}
		std::string toString()const {
			std::ostringstream str;
			str << "[" << x << "," << y << "," << z <<","<<w<< "]";
			return str.str();
		}
	};
	typedef HomogeneousCoordinates4F Vector4F;
}
static std::ostream& operator<<(std::ostream& out, const lan::HomogeneousCoordinates4F& vec) {
	out << vec.toString();
	return out;
}