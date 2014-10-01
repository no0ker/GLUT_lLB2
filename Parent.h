#pragma once
#include "Line.h"

class Parent{
	public:
		virtual void citio(Line * line_in){};
		virtual void addPoint(double x, double y){};
		virtual void draw(void){};
		virtual void fill(int, Point){};
};