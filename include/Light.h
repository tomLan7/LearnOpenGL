#pragma once
#include"Vector3F.h"
namespace lan {
	struct DirectionalLight
	{
		Vector3F Color;
		//�����⣬ȡֵ��Χ0~1
		float AmbientIntensity;
		Vector3F Direction;
		//������ǿ�ȣ�ȡֵ��Χ0~1
		float DiffuseIntensity;
	};
}
