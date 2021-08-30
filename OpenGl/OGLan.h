#pragma once
#include"glut.h"
#include<vector>
#define paint Pen::getInstance()
class OGLan
{
public:
	OGLan(int& argc,char** argv);
	~OGLan();
	//增加一个窗口，之前的窗口效果不变，以后所有设置均处理新的窗口
	int createWindow(const char* title="title");
	void initWindowSize(int width,int height);
	void initWindowPosition(int x,int y);
	//显示为2D画面，0，0还是0，0，设置显示的坐标范围
	void set2DRange(GLdouble width, GLdouble height);
	void exec();
	void initDisplayMode(GLuint mode);
};
//画笔类，单例类，会自动绘制其中有的东西
class Pen{
	static  Pen* obj;
	std::vector<std::pair<double, double>> allPoint;
	std::vector<std::pair<std::pair<double, double>, std::pair<double, double>>> allLine;
	std::vector<std::tuple<double,double,double>> allCircle;
	std::vector<std::tuple<double, double, double>> allFullCircle;
	std::vector<std::tuple<double, double, double>> allFivePointedStart;
	void drawAllPoint();
	void drawAllLine();
	//用多少边行来近似圆
	const double PI = acos(-1.0);
	static const int circleAccuracy=20;
	void drawAllCircle();
	//用于绘制的函数
	static void draw();
	friend class OGLan;
public:
	static Pen* getInstance();
	//使用单例类来绘制内容
	void drawPointd(GLdouble x, GLdouble y);
	void drawLined(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2);
	void drawCircle(GLdouble x, GLdouble y, GLdouble r);
	void fullCircle(GLdouble x, GLdouble y, GLdouble r);
	void drawFivePointedStar(GLdouble x, GLdouble y, GLdouble r, GLdouble rotate);
	//A*sin(ax+b)
	void drawSin(GLdouble x,GLdouble y,GLdouble A,GLdouble a,GLdouble b);



};