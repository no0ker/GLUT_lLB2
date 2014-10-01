#pragma once
#include <vector>
#include "Point.h"
#include "Line.h"
#include "Parent.h"

class Polygon : public Parent
{
public:
	~Polygon(void);
	Polygon();

	virtual void addPoint(double x, double y);
	virtual void draw(void);
	virtual void citio(Line* line_in);
	virtual void fill(int, Point);

	std::vector<Point> points;
	std::vector<Point> points_normal;
	
private:
	bool lines_is_right;
	void add_Normals(void);
	bool is_Convex(void);
	int static const pMx = 1000;
	int static const pMy = 1000;
	char pMatrix[pMx][pMy];
	void fillOnEdges(Line, int);
	int Polygon::intersect(int, Line);
	int Polygon::intersect_ox(int, Line);
	int mid();
	void clear();
};

