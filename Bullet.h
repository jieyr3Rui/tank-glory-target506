/************BULLET CLASS*********
by:jieyr
**********************************/
#ifndef BULLET_H
#define BULLET_H

#include "graphics.h"
#include <math.h>
#include <iostream>

#define STDBULLET_xy_speed 9
#define STDBULLET_angle 0
#define STDBULLET_Color BLUE
#define STDBULLET_BLUE_power 50
#define STDBULLET_BLUE_count 30
#define STDBULLET_RED_power 100
#define STDBULLET_RED_count 60
#define STDBULLET_me 1
#define STDBULLET_enemy 0
//Pointi_X(theta) = x * cos(theta) - y * sin(theta) STD shape:
#define Bullet_Point0_X(angle)   (  0 * cosf(angle) -  20 * sinf(angle))
#define Bullet_Point1_X(angle)   ( -7 * cosf(angle) -   0 * sinf(angle))
#define Bullet_Point2_X(angle)   (  7 * cosf(angle) -   0 * sinf(angle))
//Pionti_Y(theta) = x * sin(theta) + y * sin(theta) STD shape:
#define Bullet_Point0_Y(angle)   (  0 * sinf(angle) +  20 * cosf(angle))
#define Bullet_Point1_Y(angle)   ( -7 * sinf(angle) +   0 * cosf(angle))
#define Bullet_Point2_Y(angle)   (  7 * sinf(angle) +   0 * cosf(angle))



class BULLET{
	protected:
		int             x_pos;          //the position of centroid 
		int             y_pos;
		int            init_x;
		int            init_y;
	    float           theta;          //the angle: bullet and std  
		int          xy_speed;
		int             count;
		int             power;
		COLORREF Bullet_Color;
		
	public:
		/************constuctor and distuctor****************/
		BULLET(int newX,int newY,float newTheta,COLORREF newColor,int type);
		BULLET();
		~BULLET();
		/********************show and move******************/
		void show();
		void hide();
		void moveto(int newX,int newY);
		void move();
		/*******************get function*****************/
		int get_x(){return x_pos;};
		int get_y(){return y_pos;};
		int get_count(){return count;} //count 
		int get_power(){return power;}
		int get_maxdis();
		int             whose;
};

#endif