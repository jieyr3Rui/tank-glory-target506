/*********PLANE CLASS CPP*********
by:jieyr
*********************************/
#include "Tank.h"
#include <vector>
TANK::TANK(int newX, int newY, COLORREF newColor){
	x_pos        = newX;
	y_pos        = newY;
	theta        = STDTANK_angle;
	xy_speed     = STDTANK_xy_speed;
	rotate_speed = STDTANK_rotate_speed;
	Tank_Color  = newColor;
	load = 0;

	//if(Tank_Point != NULL) delete [] Tank_Point;
	//Tank_Point = new POINT [8];
}

TANK::TANK(){
	x_pos        = 1;
	y_pos        = 1;
	theta        = STDTANK_angle;
	xy_speed     = STDTANK_xy_speed;
	rotate_speed = STDTANK_rotate_speed;
	Tank_Color  = STDTANK_Color;
	load = 0;
	//if(Tank_Point != NULL) delete [] Tank_Point;
	//Tank_Point = new POINT [8];
}

TANK::~TANK(){
	//if(Tank_Point != NULL) delete [] Tank_Point;
}

void TANK::show(){
	/*
	(Tank_Point + 0)->x = Tank_Point0_X(theta) + x_pos;
	(Tank_Point + 0)->y = Tank_Point0_Y(theta) + y_pos;

	(Tank_Point + 1)->x = Tank_Point1_X(theta) + x_pos;
	(Tank_Point + 1)->y = Tank_Point1_Y(theta) + y_pos;

	(Tank_Point + 2)->x = Tank_Point2_X(theta) + x_pos;
	(Tank_Point + 2)->y = Tank_Point2_Y(theta) + y_pos;

	(Tank_Point + 3)->x = Tank_Point3_X(theta) + x_pos;
	(Tank_Point + 3)->y = Tank_Point3_Y(theta) + y_pos;

	(Tank_Point + 4)->x = Tank_Point4_X(theta) + x_pos;
	(Tank_Point + 4)->y = Tank_Point4_Y(theta) + y_pos;

	(Tank_Point + 5)->x =  ( 30 * cosf(theta) -  10 * sinf(theta)) + x_pos;
	(Tank_Point + 5)->y = Tank_Point5_Y(theta) + y_pos;

	(Tank_Point + 6)->x = Tank_Point6_X(theta) + x_pos;
	(Tank_Point + 6)->y = Tank_Point6_Y(theta) + y_pos;

	(Tank_Point + 7)->x = Tank_Point7_X(theta) + x_pos;
	(Tank_Point + 7)->y = Tank_Point7_Y(theta) + y_pos;

    setfillcolor(WHITE);
	setlinecolor(BLACK);
	fillpolygon	(Tank_Point, 8);*/
	setfillcolor(WHITE); //大圆
	fillcircle(x_pos ,y_pos ,30);

	setfillcolor(RED); //枪口小圆
	fillcircle(get_fire_x(),get_fire_y(),2);

	setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 16); // 设置线条样式为宽度 10 的实线，端点是平的 
	setlinecolor(RED);
	line(x_pos ,y_pos ,x_pos - (int)(50.0 * sinf(theta)),y_pos+ (int)(50.0 *cosf(theta)));
	setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 1);
}

void TANK::hide(){
	 setfillcolor(BLACK);
	 setlinecolor(BLACK);
	 //fillpolygon(Tank_Point, 8);
}

void TANK::moveto(int newX,int newY){

	x_pos = newX;
	y_pos = newY;

}

void TANK::move(int x_move,int y_move){
	moveto(x_pos + x_move * STDTANK_xy_speed ,y_pos + y_move * STDTANK_xy_speed);
}

void TANK::rotate(float new_rotate){

	theta += new_rotate * STDTANK_rotate_speed;

}

void TANK::correct(){
	hide();
	theta = STDTANK_angle;
	show();
}

int TANK::get_x(){
	return x_pos;
}

int TANK::get_y(){
	return y_pos;
}

float TANK::get_theta(){
	return theta;
}

int TANK::get_fire_x(){
	return TANK_fire_x(theta);
}

int TANK::get_fire_y(){
	return TANK_fire_y(theta);
}

float TANK::get_fire_theta(){
	return (theta + (float)1.573);
}

void TANK::correct_theta(int newx_pos,int newy_pos){
	float dis = powf((newx_pos - x_pos) * (newx_pos - x_pos) + (newy_pos - y_pos) * (newy_pos - y_pos),0.5);
	theta = acosf((float)(newx_pos - x_pos)/dis);
	if(newy_pos <= y_pos) theta *= -1;
	theta -= (float)1.573; //correct theta
}