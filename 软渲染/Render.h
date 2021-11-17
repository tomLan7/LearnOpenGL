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
			//计算斜率，沿着x算还是y算
			float m = ((endY - startY) / (float)(endX - startX));
			if (fabs(m) <= 1) {//根据斜率绝对值是否大于1，决定是否变更x和y轴。变更的目的是让坡度放缓。
				float b = startY - startX * m;
				for (auto xi = startX; xi <= endX; xi++) {
					int yi = roundf(xi * m + b);
					drawPoint(xi, yi);
				}
			}
			else {
				float a = startX - startY / m;
				for (auto yi = startY; yi <= endY;yi++) {
					int xi = roundf(yi / m + a);
					drawPoint(xi, yi);
				}
			}
			
		}
		void drawLineByDDA(int startX, int startY, int endX, int endY) {
			float m = ((endY - startY) / (float)(endX - startX));
			if (fabs(m) <= 1) {//计算斜率，沿着x算还是y算
				float yi = startY;
				for (int xi = startX; xi <= endX; xi+=1) {
					yi += m;//每次增加的数值
					drawPoint(xi, roundf(yi));
				}
			}
			else {
				float xi = startX;
				float dx = 1/m;
				for (int yi = startY; yi <= endY; yi += 1) {
					xi += dx;
					drawPoint(roundf(xi), yi);
				}
			}
		}
		void drawLineByBresenham(int startX,int startY,int endX,int endY) {
			float m = ((endY - startY) / (float)(endX - startX));
			float b = startY - startX * m;
			int xi=startX;
			int yi=startY;
			float dlower=m* (xi + 1) + b - yi;
			float dupper = yi + 1 - m * (xi + 1) - b;
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
