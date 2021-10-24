#pragma once
namespace lan {
	//代表一个窗口，一个窗口可以加载一个Panel或多个Panel，并当Panel更新时自动刷新显示。——观察者模式
	class Window
	{
		SDL_Window* window;
		Window();
	};

}

