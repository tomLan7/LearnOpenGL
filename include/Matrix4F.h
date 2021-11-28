#pragma once
#include"HomogeneousCoordinates4F.h"
namespace lan {
	struct Matrix4F {
		HomogeneousCoordinates4F data[4];//4个列向量，分别对应该矩阵的新坐标基
		Matrix4F() = default;
		Matrix4F(HomogeneousCoordinates4F d1, HomogeneousCoordinates4F d2, HomogeneousCoordinates4F d3, HomogeneousCoordinates4F d4) {
			data[0] = d1;
			data[1] = d2;
			data[2] = d3;
			data[3] = d4;
		}
		HomogeneousCoordinates4F operator*(const HomogeneousCoordinates4F& vec) {
			HomogeneousCoordinates4F result;
			for (int i = 0; i < sizeof(data)/sizeof(data[0]);i++) {
				result+=data[i] * vec[i];
			}
			return result;
		}
		static Matrix4F Translation(Vector3F translate) {
			return Matrix4F{ {1,0,0,0},{0,1.f,0,0},{0,0,1.f,0},{translate,1} };
		}
		static Matrix4F Scaling(Vector3F scale) {
			return Matrix4F{ {scale.x,0,0,0},{0,scale.y,0,0},{0,0,scale.z,0},{0,0,0,1} };
		}
		//绕轴逆时针旋转
		static Matrix4F RotationX(float radian) {
			Vector3F newY = { 0,1,0 };
			Vector3F newZ = { 0,0,1 };
			newY.rotateX(-radian);
			newZ.rotateX(-radian);
			return Matrix4F({ 1,0,0,0 }, { newY, 0 }, { newZ,0 }, { 0,0,0,1 });
		}
		static Matrix4F RotationY(float radian) {
			Vector3F newZ = { 0,0,1 };
			Vector3F newX = { 1,0,0 };
			newZ.rotateY(-radian);
			newX.rotateY(-radian);
			return Matrix4F({ newX,0 }, {0,1,0, 0 }, {newZ,0 }, { 0,0,0,1 });
		}
		static Matrix4F RotationZ(float radian) {
			Vector3F newX = { 1,0,0 };
			Vector3F newY = { 0,1,0 };
			newX.rotateZ(-radian);
			newY.rotateZ(-radian);
			return Matrix4F({ newX,0 }, { newY, 0 }, { 0,0,1,0 }, { 0,0,0,1 });
		}
	};
}
