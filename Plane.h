/*****************PLANE CLASS*************
by:jieyr

****************************************/
#ifndef PLANE_H
#define PLANE_H

#include "graphics.h"
#include <iostream>
#include <math.h>

#define STD_xy_speed 5       
#define STD_rotate_speed 0.1
#define Init_angle 0.0
#define Default_Color WHITE
//Pointi_X(theta) = x * cos(theta) - y * sin(theta)
#define Point0_X(angle)   (  0 * cosf(angle) - 150 * sinf(angle))
#define Point1_X(angle)   (-30 * cosf(angle) -   0 * sinf(angle))
#define Point2_X(angle)   (-90 * cosf(angle) +  30 * sinf(angle))
#define Point3_X(angle)   ( 90 * cosf(angle) +  30 * sinf(angle))
#define Point4_X(angle)   ( 30 * cosf(angle) -   0 * sinf(angle))

#define Point0_Y(angle)   (  0 * sinf(angle) + 150 * cosf(angle))
#define Point1_Y(angle)   (-30 * sinf(angle) +   0 * cosf(angle))
#define Point2_Y(angle)   (-90 * sinf(angle) -  30 * cosf(angle))
#define Point3_Y(angle)   ( 90 * sinf(angle) -  30 * cosf(angle))
#define Point4_Y(angle)   ( 30 * sinf(angle) +   0 * cosf(angle))


class PLANE{
	protected:
		int x_pos;            //the position of centroid 
		int y_pos;
	    float theta;          //the angle: plane and std | 
		int xy_speed;		  
		float rotate_speed;
		POINT* Plane_Point;   //Boundary point 
		COLORREF Plane_Color;
	public:
		/**************constuctor and distuctor********/
		PLANE(int newX, int newY, COLORREF newColor);
		PLANE();
		~PLANE();
		/*****************show and move****************/
		void show();
		void hide();
		void moveto(int newX,int newY);
		void move(int x_move,int y_move);
		void rotate(float new_rotate);
		void correct();
};
#endif
