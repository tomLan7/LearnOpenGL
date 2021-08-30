#include "OGLan.h"
#include<tuple>
using namespace std;

OGLan::OGLan(int& argc, char** argv)
{
	glutInit(&argc,argv);
}


OGLan::~OGLan()
{
}

void OGLan::initWindowSize(int width, int height)
{
	glutInitWindowSize(width, height);
	set2DRange(width,height);
}

void OGLan::initWindowPosition(int x, int y)
{
	glutInitWindowPosition(x, y);
}

void OGLan::set2DRange(GLdouble width, GLdouble height)
{
	glMatrixMode(GL_PROJECTION);
	
}
void OGLan::exec()
{
	glutMainLoop();
}
void OGLan::initDisplayMode(GLuint mode)
{
	glutInitDisplayMode(mode);

}
int OGLan::createWindow(const char * title)
{
	int rtn= glutCreateWindow(title);
	glutDisplayFunc(&Pen::draw);
	return rtn;
}

void Pen::drawAllPoint()
{
	glBegin(GL_POINTS);
	for (auto i:allPoint) {
		glVertex2d(i.first,i.second);
	}
	glEnd();
}

void Pen::drawAllLine()
{

	glBegin(GL_LINES);
	for (auto i : allLine) {	
		glVertex2d(i.first.first, i.first.second);
		glVertex2d(i.second.first, i.second.second);
	}
	glEnd();
}

void Pen::drawAllCircle()
{
	for (auto i :allCircle) {
		glBegin(GL_LINE_LOOP);
		//printf("x:%fy:%fr:%f\n",get<0>(i), get<1>(i),get<2>(i));
		//printf("accuracy:%d\n",circleAccuracy);
		double unit = 2 * PI / circleAccuracy;//基本弧度
		//printf("unit:%f\n", unit);
		for (int j = 0; j < circleAccuracy;j++) {
			double currentRadio = j * unit;//当前弧度，从[0~2*PI)
			//printf("current:%f\n",currentRadio);
			//printf("x:%fy:%f\n", get<0>(i) + get<2>(i) * cos(currentRadio), get<1>(i) + get<2>(i) * sin(currentRadio));
			glVertex2d(get<0>(i) + get<2>(i) * cos(currentRadio), get<1>(i) + get<2>(i) * sin(currentRadio));
		}
		glEnd();
	}
	
	glFlush();
	
	for (auto i :allFullCircle) {
		glBegin(GL_TRIANGLE_FAN);
		//printf("x:%fy:%fr:%f\n",get<0>(i), get<1>(i),get<2>(i));
		//printf("accuracy:%d\n",circleAccuracy);
		glVertex2d(get<0>(i), get<1>(i));
		//使用极坐标系
		double unit = 2 * PI / circleAccuracy;//基本弧度
		//printf("unit:%f\n", unit);
		for (int j = 0; j < circleAccuracy; j++) {
			double currentRadio = j * unit;//当前弧度，从[0~2*PI)
			//printf("current:%f\n",currentRadio);
			//printf("x:%fy:%f\n", get<0>(i) + get<2>(i) * cos(currentRadio), get<1>(i) + get<2>(i) * sin(currentRadio));
			glVertex2d(get<0>(i) + get<2>(i) * cos(currentRadio), get<1>(i) + get<2>(i) * sin(currentRadio));
		}
		glVertex2d(get<0>(i) + get<2>(i) * cos(0), get<1>(i) + get<2>(i) * sin(0));
		glEnd();
	}
	
	glFlush();
}

Pen* Pen::getInstance()
{
	return obj;
}

void Pen::drawPointd(GLdouble x, GLdouble y)
{
	allPoint.push_back(std::make_pair(x,y));
}
void Pen::drawLined(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2)
{
	allLine.push_back(std::make_pair(std::make_pair(x1,y1), std::make_pair(x2,y2)));
}

void Pen::drawCircle(GLdouble x, GLdouble y, GLdouble r)
{
	allCircle.push_back(std::make_tuple(x,y,r));
}

void Pen::fullCircle(GLdouble x, GLdouble y, GLdouble r)
{
	allFullCircle.push_back(std::make_tuple(x,y,r));
}

void Pen::drawFivePointedStar(GLdouble x, GLdouble y,GLdouble z, GLdouble rotate)
{
	//思路，求出弧度，然后绘制点，根据五角星特点依次连线。
}

void Pen::drawSin(GLdouble x, GLdouble y, GLdouble A, GLdouble a, GLdouble b)
{
}

void Pen::draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	getInstance()->drawAllLine();
	getInstance()->drawAllPoint();
	getInstance()->drawAllCircle();
	glFlush();
	
}
Pen* Pen::obj = new Pen;