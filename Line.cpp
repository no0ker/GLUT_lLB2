#include "Line.h"
#include <GL\glut.h>

Line::Line(void)
{
	flag = 0;
	point_from.x = 0;
	point_from.y = 0;
	flag_from = 0;
	flag_to = 0;
}


Line::~Line(void)
{
}

void Line::set_point(int x, int y){
	if(flag==1){
		point_from.x = x;
		point_from.y = y;
		flag = 0;
	} else {
		point_to.x = x;
		point_to.y = y;
		flag = 1;
	}

}

void Line::draw(){
	glBegin(GL_LINES);
		glColor3f(1.0, 1.0, 0); 
		glVertex2d(point_from.x, point_from.y);
		glVertex2d(point_to.x, point_to.y);

		glColor3f(0.3, 1.0, 0.3);
		glVertex2f(cropped_point_from.x, cropped_point_from.y);
		glColor3f(0.3, 1.0, 0.3);
		glVertex2f(cropped_point_to.x, cropped_point_to.y);
	glEnd();
}
