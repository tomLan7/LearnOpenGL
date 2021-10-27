#pragma once
#include"Panel.h"
#include"Color3B.h"
#include"Vector3.h"
namespace lan {
	class Render
	{
		Panel panel;
		void setDrawColor(Color3B color) {
			panel.setDrawColor(color);
		}
		Color3B getDrawColor(Color3B color) {
			return panel.getDrawColor();
		}
		void drawPoint(int x,int y) {
			try {
				panel.setPix(x, y);
			}
			catch (...) {

			}
		}
		void drawPoint(Vector3F vec) {
			drawPoint(vec.x,vec.y);
		}
	};
}
