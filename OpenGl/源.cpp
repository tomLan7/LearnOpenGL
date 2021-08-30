#include<iostream>
#include<stdlib.h>
#include<functional>
#include"OGLan.h"
int c=100;
void it() {
	
		//glColor3f(0, 0, 0);

		glBegin(GL_LINES);
		glVertex2i(10, 20);
		glVertex2i(100, 120);
		glVertex2i(10, 15);
		glVertex2i(20, 145);
		c == 100 ? c = 50 : c = 100;

		glEnd();
		glFlush();
}

int main(int argc,char**argv) {
	OGLan o(argc,argv);
	o.createWindow("nihao");
	o.set2DRange(200,500);
	auto pen = Pen::getInstance();
	pen->drawLined(10,20,100,120);
	pen->drawLined(10, 15, 20, 145);
	o.exec();
	
	
}