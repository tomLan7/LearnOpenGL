#pragma once
#include"glut.h"
#include<vector>
#define paint Pen::getInstance()
class OGLan
{
public:
	OGLan(int& argc,char** argv);
	~OGLan();
	//����һ�����ڣ�֮ǰ�Ĵ���Ч�����䣬�Ժ��������þ������µĴ���
	int createWindow(const char* title="title");
	void initWindowSize(int width,int height);
	void initWindowPosition(int x,int y);
	//��ʾΪ2D���棬0��0����0��0��������ʾ�����귶Χ
	void set2DRange(GLdouble width, GLdouble height);
	void exec();
	void initDisplayMode(GLuint mode);
};
//�����࣬�����࣬���Զ����������еĶ���
class Pen{
	static  Pen* obj;
	std::vector<std::pair<double, double>> allPoint;
	std::vector<std::pair<std::pair<double, double>, std::pair<double, double>>> allLine;
	std::vector<std::tuple<double,double,double>> allCircle;
	std::vector<std::tuple<double, double, double>> allFullCircle;
	std::vector<std::tuple<double, double, double>> allFivePointedStart;
	void drawAllPoint();
	void drawAllLine();
	//�ö��ٱ���������Բ
	const double PI = acos(-1.0);
	static const int circleAccuracy=20;
	void drawAllCircle();
	//���ڻ��Ƶĺ���
	static void draw();
	friend class OGLan;
public:
	static Pen* getInstance();
	//ʹ�õ���������������
	void drawPointd(GLdouble x, GLdouble y);
	void drawLined(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2);
	void drawCircle(GLdouble x, GLdouble y, GLdouble r);
	void fullCircle(GLdouble x, GLdouble y, GLdouble r);
	void drawFivePointedStar(GLdouble x, GLdouble y, GLdouble r, GLdouble rotate);
	//A*sin(ax+b)
	void drawSin(GLdouble x,GLdouble y,GLdouble A,GLdouble a,GLdouble b);



};