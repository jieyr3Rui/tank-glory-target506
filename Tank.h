/*****************PLANE CLASS*************
by:jieyr

****************************************/
#ifndef TANK_H
#define TANK_H

#include "graphics.h"
#include "Bullet.h"
#include <iostream>
#include <vector>
#include <math.h>
#define STDTANK_xy_speed 3       
#define STDTANK_rotate_speed (float)0.45
#define STDTANK_angle (float)0.0
#define STDTANK_Color WHITE
#define STDTANK_radius 60
#define TANK_fire_x(angle) (x_pos - (int)(58.0 * sinf(angle)))
#define TANK_fire_y(angle) (y_pos + (int)(58.0 * cosf(angle)))
//Pointi_X(theta) = x * cos(theta) - y * sin(theta) STD shape:
#define Tank_Point0_X(angle)   (-10 * cosf(angle) -  40 * sinf(angle)) //( -10,  40)
#define Tank_Point1_X(angle)   (-10 * cosf(angle) -  10 * sinf(angle)) //( -10,  10)
#define Tank_Point2_X(angle)   (-30 * cosf(angle) -  10 * sinf(angle)) //( -50,  10)
#define Tank_Point3_X(angle)   (-30 * cosf(angle) +  30 * sinf(angle)) //( -50, -30)
#define Tank_Point4_X(angle)   ( 30 * cosf(angle) +  30 * sinf(angle)) //(  50, -30)
#define Tank_Point5_X(andle)   ( 30 * cosf(angle) -  10 * sinf(angle)) //(  50,  10)
#define Tank_Point6_X(angle)   ( 10 * cosf(angle) -  10 * sinf(angle)) //(  10,  10)
#define Tank_Point7_X(angle)   ( 10 * cosf(angle) -  40 * sinf(angle)) //(  10,  40)
//Pointi_Y(theta) = x * sin(theta) + y * cos(theta) STD shape:
#define Tank_Point0_Y(angle)   (-10 * sinf(angle) +  40 * cosf(angle))
#define Tank_Point1_Y(angle)   (-10 * sinf(angle) +  10 * cosf(angle))
#define Tank_Point2_Y(angle)   (-30 * sinf(angle) +  10 * cosf(angle))
#define Tank_Point3_Y(angle)   (-30 * sinf(angle) -  30 * cosf(angle))
#define Tank_Point4_Y(angle)   ( 30 * sinf(angle) -  30 * cosf(angle))
#define Tank_Point5_Y(angle)   ( 30 * sinf(angle) +  10 * cosf(angle))
#define Tank_Point6_Y(angle)   ( 10 * sinf(angle) +  10 * cosf(angle))
#define Tank_Point7_Y(angle)   ( 10 * sinf(angle) +  40 * cosf(angle))


class TANK{
	protected:
		int            x_pos;          //the position of centroid 
		int            y_pos;
	    float          theta;          //the angle: plane and std | 
		int         xy_speed;		  
		float   rotate_speed;
		COLORREF  Tank_Color;
		int			  fire_x;
		int           fire_y;
	public:
		/**************constuctor and distuctor********/
		TANK(int newX, int newY, COLORREF newColor);
		TANK();
		~TANK();
		/*****************show and move****************/
		//POINT*    Tank_Point;      //Boundary point
		int load;
		void show();
		void hide();
		void moveto(int newX,int newY);
		void move(int x_move,int y_move);
		void rotate(float new_rotate);
		void correct();
		int get_x();
		int get_y();
		float get_theta();
		int get_fire_x();
		int get_fire_y();
		float get_fire_theta();
		void correct_theta(int newx_pos,int newy_pos);
};
#endif
