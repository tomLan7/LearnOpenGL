#pragma once
#include"Vector3F.h"
namespace lan {
	struct DirectionalLight
	{
		Vector3F Color;
		//环境光，取值范围0~1
		float AmbientIntensity;
		Vector3F Direction;
		//漫反射强度，取值范围0~1
		float DiffuseIntensity;
	};
}
