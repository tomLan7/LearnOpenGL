#pragma once
#include<iostream>
namespace lan {

#define M_Pi 3.14159f
#define PiOver2 (M_Pi/2)
#define ToRadian(x) ((x) * M_Pi / 180.0f)
#define ToDegree(x) ((x) * 180.0f / M_Pi)
#define Deg2Rad (M_Pi/180.f)
#define Rad2Deg (180.f/M_Pi)
	
	//���Ƕ�������-pi��pi������
	inline float wrapPi(float theta) {
		while (theta > PiOver2)
			theta -= M_Pi;
		while (theta < PiOver2)
			theta += M_Pi;
		return theta;
	}
}
