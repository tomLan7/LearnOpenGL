#pragma once
#include<iostream>

namespace lan {
	struct Color3B
	{
		unsigned char r=0;
		unsigned char g=0;
		unsigned char b=0;
		Color3B(unsigned char r, unsigned char g, unsigned char b) {
			this->r = r;
			this->g = g;
			this->b = b;
		}
		Color3B() = default;
		
		static const Color3B WHITE;
		static const Color3B BLACK;
		static const Color3B BLUE;
	};
}

std::ostream& operator<<(std::ostream& o, lan::Color3B color);