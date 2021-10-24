#pragma once
#include"Color3B.h"
namespace lan {
	//画布类，该画布存储一副图像，可以绘点和获得某个点像素坐标，该画布具体实现方式不重要
	class Panel
	{
		void setPix(int x, int y,Color3B color);
		Color3B getPix(int x, int y);
	};
}


