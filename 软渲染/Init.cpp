#include"Init.h"
#include"Color3B.h"
namespace lan {
	const Color3B Color3B::WHITE{ 255,255,255 };
	const Color3B Color3B::BLACK{ 0,0,0 };
	const Color3B Color3B::BLUE{0,0,255};
}

std::ostream& operator<<(std::ostream& o, lan::Color3B color) {
	std::cout << "¡¾" << color.r << "," << color.g << "," << color.b << "¡¿";
	return o;
}

InitSDL* InitSDL::instance=new InitSDL();