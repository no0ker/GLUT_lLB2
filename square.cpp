#include "Square.h"
#include <cmath>
#include <iostream>
#include <gl/glut.h>

Square::Square(){
	flag = 0;
}

void Square::addPoint(double x, double y){
	if(flag==0){
		left_down.x = x;
		left_down.y = y;
		flag = 1;
	} else {
		right_top.x = x;
		right_top.y = y;
		flag = 0;
	}
	if(left_down.x > right_top.x){
		Point tmp;
		tmp.x = left_down.x;
		tmp.y = left_down.y;

		left_down.x = right_top.x;
		left_down.y = right_top.y;

		right_top.x = tmp.x;
		right_top.y = tmp.y;

		if(flag == 0)
			flag = 1;
		else
			flag = 0;
	}
}


void Square::draw(){
	glBegin(GL_LINE_LOOP);
		glColor3f(1.0, 0.25, 0.0); 
		glVertex2d(left_down.x, left_down.y);

		glColor3f(1.0, 0.25, 0.0); 
		glVertex2d(left_down.x, right_top.y);

		glColor3f(1.0, 0.25, 0.0); 
		glVertex2d(right_top.x, right_top.y);

		glColor3f(1.0, 0.25, 0.0); 
		glVertex2d(right_top.x, left_down.y);
	glEnd();
}

void Square::citio(Line * line_in){
	Line result;
	reccur_citio(line_in, &result);
	line_in->cropped_point_from = result.point_from;
	line_in->cropped_point_to = result.point_to;
}


int Square::reccur_citio(Line * line_in, Line * line_result){
	
	// функция "мечения" линии
	add_flag_to_point(line_in);
	// назначить метки обеим концам отрезка
	// если отрезок длиной ноль. возвращаем нуль.
	// тривиально видимый. 
	if( line_in->flag_from == 0 && line_in->flag_to == 0){
		line_result->point_from = line_in->point_from;
		line_result->point_to = line_in->point_to;
		//std::cout << "\t trivial visible  ";
		return 1;
	}
	//тривиально невидимый
	if((line_in->flag_from & line_in->flag_to) != 0){
		//std::cout << "\t trivial invisible  ";
		return 0;
	}
	// "непонятный отрезок"
	// если отрезок единичной длины, то игнорируем его.
	
	if( 
		(line_in->point_from.x - line_in->point_to.x) <= 1
		&&
		(line_in->point_from.x - line_in->point_to.x) >= -1
		&&
		(line_in->point_from.y - line_in->point_to.y) <= 1
		&&
		(line_in->point_from.y - line_in->point_to.y) >= -1
	)
	{
		return 0;
	}

	Line first;
	Line first_result;
	int first_flag = 0;
	Line two;
	Line two_result;
	int two_flag = 0;
	Point mid;
	mid.x = (line_in->point_from.x + line_in->point_to.x)/2;
	mid.y = (line_in->point_from.y + line_in->point_to.y)/2;

	first.point_from.x = line_in->point_from.x;
	first.point_from.y = line_in->point_from.y;
	first.point_to.x = mid.x;
	first.point_to.y = mid.y;

	two.point_from.x = mid.x;
	two.point_from.y = mid.y;
	two.point_to.x = line_in->point_to.x;
	two.point_to.y = line_in->point_to.y;

	// делим пополам и в рекурсию
	first_flag = reccur_citio(&first, &first_result);
	two_flag = reccur_citio(&two, &two_result);

	// соединяем полученные результаты.
	if(first_flag == 1 && two_flag ==1 ){

		if(
			first_result.point_from.x == two_result.point_from.x 
			&&
			first_result.point_from.y == two_result.point_from.y
		){
			line_result->point_from.x = first_result.point_to.x;
			line_result->point_from.y = first_result.point_to.y;
			line_result->point_to.x = two_result.point_to.x;
			line_result->point_to.y = two_result.point_to.y;
		}

		if(
			first_result.point_from.x == two_result.point_to.x 
			&&
			first_result.point_from.y == two_result.point_to.y 
		){
			line_result->point_from.x = first_result.point_to.x;
			line_result->point_from.y = first_result.point_to.y;
			line_result->point_to.x = two_result.point_from.x;
			line_result->point_to.y = two_result.point_from.y;
		}

		if(
			first_result.point_to.x == two_result.point_from.x 
			&&
			first_result.point_to.y == two_result.point_from.y 
		){
			line_result->point_from.x = first_result.point_from.x;
			line_result->point_from.y = first_result.point_from.y;
			line_result->point_to.x = two_result.point_to.x;
			line_result->point_to.y = two_result.point_to.y;
		}

		if(
			first_result.point_to.x == two_result.point_to.x 
			&&
			first_result.point_to.y == two_result.point_to.y 
		){
			line_result->point_from.x = first_result.point_from.x;
			line_result->point_from.y = first_result.point_from.y;
			line_result->point_to.x = two_result.point_from.x;
			line_result->point_to.y = two_result.point_from.y;
		}

		return 1;
	}

	if(first_flag == 1){
		line_result->point_from.x = first_result.point_from.x;
		line_result->point_from.y = first_result.point_from.y;
		line_result->point_to.x = first_result.point_to.x;
		line_result->point_to.y = first_result.point_to.y;
		return 1;
	}

	if(two_flag == 1){
		line_result->point_from.x = two_result.point_from.x;
		line_result->point_from.y = two_result.point_from.y;
		line_result->point_to.x = two_result.point_to.x;
		line_result->point_to.y = two_result.point_to.y;
		return 1;
	}

	return 0;
}

void Square::add_flag_to_point(Line * line_in){
	int x_min, x_max, y_min, y_max;

	if(left_down.x > right_top.x){
		x_max = left_down.x;
		x_min = right_top.x;
	} else {
		x_max = right_top.x;
		x_min = left_down.x;
	}

	if(left_down.y > right_top.y){
		y_max = left_down.y;
		y_min = right_top.y;
	} else {
		y_max = right_top.y;
		y_min = left_down.y;
	}
	

	if(line_in->point_from.x >= x_min)
		line_in->flag_from &= ~(1<<3);
	else
		line_in->flag_from |= (1<<3);


	if(line_in->point_from.x <= x_max)
		line_in->flag_from &= ~(1<<2);
	else
		line_in->flag_from |= (1<<2);


	if(line_in->point_from.y >= y_min)
		line_in->flag_from &= ~(1<<1);
	else
		line_in->flag_from |= (1<<1);


	if(line_in->point_from.y <= y_max)
		line_in->flag_from &= ~(1<<0);
	else
		line_in->flag_from |= (1<<0);



	if(line_in->point_to.x >= x_min)
		line_in->flag_to &= ~(1<<3);
	else
		line_in->flag_to |= (1<<3);


	if(line_in->point_to.x <= x_max)
		line_in->flag_to &= ~(1<<2);
	else
		line_in->flag_to |= (1<<2);


	if(line_in->point_to.y >= y_min)
		line_in->flag_to &= ~(1<<1);
	else
		line_in->flag_to |= (1<<1);


	if(line_in->point_to.y <= y_max)
		line_in->flag_to &= ~(1<<0);
	else
		line_in->flag_to |= (1<<0);

}