#pragma once
#include"Panel.h"
#include"Color3B.h"
#include"Vector3.h"
namespace lan {
	class Render
	{
		Panel& panel;
	public:
		Render(Panel* panel):panel(*panel){
			
		}

		Render(Panel& panel) :panel(panel) {

		}
		void setDrawColor(Color3B color) {
			panel.setDrawColor(color);
		}
		Color3B getDrawColor(Color3B color) {
			return panel.getDrawColor();
		}
		//依靠直线方程去计算
		void drawLineByEquation(int startX,int startY,int endX,int endY) {
			float m = ((endY - startY) / (float)(endX - startX));

			float b = startY - startX * m;

			for (auto xi = startX; xi <= endX; xi++){
				int yi=roundf(xi*m+b);
				drawPoint(xi,yi);
			}
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
		void flush() {
			panel.flush();
		}
	};
}
