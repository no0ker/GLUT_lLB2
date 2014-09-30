#include <stdlib.h>
#include <gl/glut.h>
#include <iostream>
#include "Polygon.h"
#include "Line.h"
#include "Square.h"
#include "Parent.h"

int window_width = 500;
int window_height = 250;

Parent * parent;
Line line;


/* эта функция управляет всем выводом на экран */
void display(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1,1,1,1);
	//line.draw();
	//parent->draw();
	////////////////
    Point otr[2];
	otr[0].x = 50;
	otr[0].y = 250;

	otr[1].x = 50;
	otr[1].y = 30;
	Point tmp[2];
	tmp[0].x = 0;
	tmp[0].y = 100;
	tmp[1].x = 500;
	tmp[1].y = 100;
	glBegin (GL_LINES);
		glColor3f(250,250,0); 
		glVertex2d(otr[0].x, otr[0].y);
		glColor3f(250,250,0); 
		glVertex2d(otr[1].x, otr[1].y);

		glColor3f(250,0,255); 
		glVertex2d(tmp[0].x, tmp[0].y);
		glColor3f(250,0,255); 
		glVertex2d(tmp[1].x, tmp[1].y);
    glEnd ();
	
	
	Point z;
	
	
	z.x = (otr[1].x - otr[0].x)*(tmp[0].y - otr[0].y)/(otr[1].y - otr[0].y) + otr[0].x;
	z.y = tmp[0].y;
	
    glBegin (GL_LINES);
		glColor3f(0,250,250); 
		glVertex2d(z.x, z.y);
		glColor3f(0,250,250); 
		glVertex2d(tmp[1].x, tmp[1].y);
	glEnd();
	

	glFinish ();
}

void testA(){
	//char pMatrix[500][250];
	/*for(int i=0; i<window_width; ++i){
		for(int j=0; j<window_height; ++j){
			pMatrix[i][j] = 0;
		}
	}*/

	//glBegin (GL_POINTS);
	//for(int i=0; i<window_width; ++i){
		//for(int j=0; j<window_height; ++j){
			//glColor3f(pMatrix[i][j], pMatrix[i][j], 0); 
			//glVertex2d(i, j);
		//}
	//}
    //glEnd ();
	
	display();
}


/* Функция вызывается при изменении размеров окна */
void reshape(GLint w, GLint h){
	window_width = w;
	window_height = h;

    /* устанавливаем размеры области отображения */
    glViewport(0, 0, w, h);

    /* ортографическая проекция */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, 0, h, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void mouse(int button, int state, int ax, int ay){
	if(button == GLUT_LEFT_BUTTON && state == GLUT_UP){
		//parent->addPoint(ax, window_height - ay);
		//display();
		testA();
	}
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_UP){
		/*line.set_point(ax, window_height - ay);
		parent->citio(&line);
		display();*/
	}
}

int main(int argc, char *argv[]){
	setlocale(LC_ALL, "Russian");

	
	/*
	while(true){
		std::cout << "Пожалуйста, выберите, алгоритм отсечения отрезка \n";
		std::cout << "\n 1. алгоритм отсечения Кируса-Бека \n 2. алгоритм отсечения методом средней точки \n";
		int i;
		std::cin >> i;
		if(i==1){
			parent = new Polygon;
			break;
		}
		if(i==2){
			parent = new Square;
			break;
		}
	}
	*/
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(window_width, window_height);
	glutInitWindowPosition(100,100);
	
	glutCreateWindow("LB #1");

    glutDisplayFunc(display);
	glutMouseFunc(mouse);
    glutReshapeFunc(reshape);

    glutMainLoop();
	
	return 0;
}

