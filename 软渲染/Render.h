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
		//����ֱ�߷���ȥ����
		void drawLineByEquation(int startX,int startY,int endX,int endY) {
			//����б�ʣ�����x�㻹��y��
			float m = ((endY - startY) / (float)(endX - startX));
			if (fabs(m) <= 1) {//����б�ʣ�����x�㻹��y��
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
			if (fabs(m) <= 1) {//����б�ʣ�����x�㻹��y��
				float yi = startY;
				for (int xi = startX; xi <= endX; xi+=1) {
					yi += m;
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
