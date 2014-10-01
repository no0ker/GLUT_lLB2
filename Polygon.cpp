#include "Polygon.h"
#include "Line.h"
#include <gl/glut.h>


Polygon::Polygon(){
	for(int i=0; i<pMx; ++i){
		for(int j=0; j<pMy; ++j){
			pMatrix[i][j] = 0;
		}
	}
}

Polygon::~Polygon(void)
{
	std::vector<Point>::iterator i;
	for(i=points.begin(); i<points.end(); ++i)
		delete &(*i);
}

void Polygon::addPoint(double x, double y){
	Point* tmp = new Point;
	tmp->x = x;
	tmp->y = y;
	points.push_back(*tmp);

	if(is_Convex() == false)
		points.pop_back();
	else 
		add_Normals();
}

void Polygon::draw(void){
	
	glBegin(GL_LINE_LOOP);
		std::vector<Point>::iterator i;
		for(i = points.begin(); i<points.end(); ++i){
			glColor3f(1.0, 0.25, 0.0); 
			glVertex2d(i->x, i->y);
		}
	glEnd();
	/* ��������� �������� - ������������ � �������
	glBegin(GL_LINES);
	for(
		std::vector<Point>::iterator i_points = points.begin(), 
		i_points_normal = points_normal.begin();
		i_points_normal < points_normal.end();
		++i_points, ++i_points_normal
	){	
		glVertex2f(i_points->x, i_points->y);
		glVertex2f(i_points_normal->x, i_points_normal->y);
	}
	glEnd();
	*/

	// ��������� �������
	glBegin (GL_POINTS);
	for(int i=0; i<pMx; ++i){
		for(int j=0; j<pMy; ++j){
			if(pMatrix[i][j] == 1){
				glColor3f(0, 125, 0); 
				glVertex2d(i, j);
			}
		}
	}
    glEnd ();
	
}




void Polygon::citio(Line* line_in)
/*
 *  ��������� �������� ��������� ������-����
 *  �� ������������� ��������� ��������������
 *
 */

{  int   ii, visible, kw;
   float xn, yn, dx, dy, r;
   float CB_t0, CB_t1;          /* ��������� ������ ������� */
   float Qx, Qy;                /* ��������� ����� ����� */
   float Nx, Ny;                /* ������������� � ����� */
   float Pn, Qn;                /**/
   
   line_in->cropped_point_from.x = line_in->point_from.x;
   line_in->cropped_point_from.y = line_in->point_from.y;

   line_in->cropped_point_to.x = line_in->point_to.x;
   line_in->cropped_point_to.y = line_in->point_to.y;

   kw = points.size() - 1;
   visible = 1;
   CB_t0 = 0;  CB_t1 = 1;
   dx = line_in->point_to.x - line_in->point_from.x;
   dy = line_in->point_to.y - line_in->point_from.y;
   
   xn = line_in->point_from.x;
   yn = line_in->point_from.y;

   
   for (ii=0; ii<=kw; ++ii) {   /* ���� �� ������ ���� */
      /* ��������� ����� ����� */
	   Qx = xn - points[ii].x;
	   Qy = yn - points[ii].y;
      /* �������������� � ����� */
	   Nx = points_normal[ii].x - points[ii].x;
	   Ny = points_normal[ii].y - points[ii].y;
      Pn= dx*Nx + dy*Ny;        /* ��������� ������������ */
      Qn= Qx*Nx + Qy*Ny;

/* ������ ������������ */
      if (Pn == 0) {            /* ������ ����� ��� ����� */
         if (Qn < 0) {
			 visible= 0;  break; 
		 }
      } else {
         r= -Qn/Pn;
         if (Pn < 0) {          /* ����� �������� ������� t */
            if (r < CB_t0) {
				visible= 0;  
				break; 
			}
            if (r < CB_t1) CB_t1= r;
         } else {               /* ����� ������� ������� t */
            if (r > CB_t1) {
				visible= 0;  
				break; 
			}
            if (r > CB_t0) CB_t0= r;
         }
      }
   }
   if (visible) {
      if (CB_t0 > CB_t1) visible= 0; else {
         if (CB_t0 > 0) {
			 line_in->cropped_point_from.x =xn + CB_t0*dx;
			 line_in->cropped_point_from.y = yn + CB_t0*dy;
         }
         if (CB_t1 < 1) {
			 line_in->cropped_point_to.x = xn + CB_t1*dx;
			 line_in->cropped_point_to.y = yn + CB_t1*dy;
         }
      }
   }

   if(visible==0){
		line_in->cropped_point_from.x=0;
		line_in->cropped_point_from.y=0;
		line_in->cropped_point_to.x=0;
		line_in->cropped_point_to.y=0;
   }

}  

void Polygon::add_Normals(void){
	if(points.size()>1){
		int mod_x, mod_y;
		
		if(lines_is_right){
			mod_x = 1;
			mod_y = -1;
		} else {
			mod_x = -1;
			mod_y = 1;
		}
			
		Point tmp, tmp2;
		int size = points.size();
		
		if(points_normal.size()>=2)
			points_normal.pop_back();

		if(points.size()==3){
			double dx = mod_x * (points[1].y - points[0].y);
			double dy = mod_y * (points[1].x - points[0].x);

			points_normal[0].x = points[0].x + dx;
			points_normal[0].y = points[0].y + dy;
		}

		double dx = mod_x * (points[size-1].y - points[size-2].y);
		double dy = mod_y * (points[size-1].x - points[size-2].x);

		tmp.x = points[size-2].x + dx;
		tmp.y = points[size-2].y + dy;

		points_normal.push_back(tmp);


		dx = mod_x * ( points[0].y - points[size-1].y );
		dy = mod_y * ( points[0].x - points[size-1].x );

		tmp2.x = points[size-1].x + dx;
		tmp2.y = points[size-1].y + dy;

		points_normal.push_back(tmp2);
	}
}



bool Polygon::is_Convex(void){
	int right = 0;
	int left = 0;
	
	double dx_prev, dy_prev, dx_next, dy_next;
	
	int size = points.size();
	if(size<=2)
		return true;

	for(int i=0; i<size; ++i){
		
		if(i!=0 && i!=size-1){
			dx_next = points[i+1].x - points[i].x;
			dy_next = points[i+1].y - points[i].y;
			dx_prev = points[i].x - points[i-1].x;
			dy_prev = points[i].y - points[i-1].y;			
		}

		if(i==0){
			dx_prev = points[0].x - points[size-1].x;
			dy_prev = points[0].y - points[size-1].y;
			dx_next = points[1].x - points[0].x;
			dy_next = points[1].y - points[0].y;	
		}

		if(i==size-1){
			dx_next = points[0].x - points[size-1].x;
			dy_next = points[0].y - points[size-1].y;
			dx_prev = points[size-1].x - points[size-2].x;
			dy_prev = points[size-1].y - points[size-2].y;			
		}
		
		int tmp = dx_prev * dy_next - dy_prev * dx_next;
		if(tmp>0)
			++left;
		else
			++right;
	}

	if(left!=0 && right!=0) 
		return false;
	else {
		if(right!=0)
			lines_is_right = true;
		else 
			lines_is_right = false;
		return true;
	}
}

void Polygon::fill(int i){
	
	if(i==1){
		if(points.size()>=2){
			Line l;
			l.point_to = points[0];
			for(int i = 1; i<points.size(); ++i){
				l.point_from = l.point_to;
				l.point_to = points[i];
				fillOnEdges(l);
			}
			l.point_from = l.point_to;
			l.point_to = points[0];
			fillOnEdges(l);
		}
	}
}


void Polygon::fillOnEdges(Line line_in){
	Line line_inner = line_in;
	
	if(line_inner.point_to.y < line_inner.point_from.y){
		Point tmp;
		tmp.x = line_inner.point_from.x;
		tmp.y = line_inner.point_from.y;
		line_inner.point_from.x = line_inner.point_to.x;
		line_inner.point_from.y = line_inner.point_to.y;
		line_inner.point_to.x = tmp.x;
		line_inner.point_to.y = tmp.y;
	}
	
	for(int y = line_inner.point_from.y; y <= line_inner.point_to.y; ++y){
		Point z;
		z.y = y;
		z.x = intersect(y, line_inner);
		for(int i = z.x; i < pMx; ++i){
			if (pMatrix[i][(int)z.y] == 0)
				pMatrix[i][(int)z.y] = 1;
			else
				pMatrix[i][(int)z.y] = 0;
		}
	}	
}

int Polygon::intersect(int y, Line poly){
	return (poly.point_to.x - poly.point_from.x)*(y - poly.point_from.y) / (poly.point_to.y - poly.point_from.y) + poly.point_from.x;
}
