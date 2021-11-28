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
	};
}
