/***********BULLET CLASS CPP********
by jieyr
***********************************/

#include "Bullet.h"

BULLET::BULLET(int newX,int newY,float newTheta,COLORREF newColor,int type){
	init_x = newX;
	init_y = newY;
	x_pos  = newX;
	y_pos  = newY;
	theta  = newTheta;
	xy_speed = STDBULLET_xy_speed;
	Bullet_Color = newColor;
	count = 1;
	whose = type;
	if(newColor == RED) power = STDBULLET_RED_power;
	else if (newColor == BLUE) power = STDBULLET_BLUE_power;
	else power = 0;
	//if(Bullet_Point != NULL) delete [] Bullet_Point;
	//Bullet_Point = new POINT [3];
}

BULLET::BULLET(){
	init_x       = 1;
	init_y       = 1;
	x_pos        = 1;
	y_pos        = 1;
	theta        = STDBULLET_angle;
	xy_speed     = STDBULLET_xy_speed;
	Bullet_Color = STDBULLET_Color;
	count = 1;
	power = 0;
	whose = 0;
	//if(Bullet_Point != NULL) delete [] Bullet_Point;
	//Bullet_Point = new POINT [3];
} 

BULLET::~BULLET(){
	//if(Bullet_Point != NULL)delete [] Bullet_Point;
}

void BULLET::show(){
	setfillcolor(Bullet_Color);
	solidcircle(x_pos,y_pos,10);
	/*(Bullet_Point + 0)->x = Bullet_Point0_X(theta) + x_pos;
	(Bullet_Point + 0)->y = Bullet_Point0_Y(theta) + y_pos;

	(Bullet_Point + 1)->x = Bullet_Point1_X(theta) + x_pos;
	(Bullet_Point + 1)->y = Bullet_Point1_Y(theta) + y_pos;

	(Bullet_Point + 2)->x = Bullet_Point2_X(theta) + x_pos;
	(Bullet_Point + 2)->y = Bullet_Point2_Y(theta) + y_pos;

    setfillcolor(Bullet_Color);
	setlinecolor(Bullet_Color);
	fillpolygon	(Bullet_Point, 3);*/
}

void BULLET::hide(){
	clearcircle(x_pos,y_pos,10);
	/*setfillcolor(BLACK);
	setlinecolor(BLACK);
	fillpolygon(Bullet_Point, 3);*/
}



void BULLET::move(){
	x_pos = init_x + count * cosf(theta) * STDBULLET_xy_speed;
	y_pos = init_y + count * sinf(theta) * STDBULLET_xy_speed;
	count++;
}

int BULLET::get_maxdis(){
	return (Bullet_Color == RED) ? STDBULLET_RED_count : STDBULLET_BLUE_count;
}