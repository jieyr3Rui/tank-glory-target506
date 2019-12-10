#include "Floor.h"

FLOOR::FLOOR(int newX,int newY,int width ,int lenth){
	health = STDYELLOW_BLOCK_health;
	x_pos  = newX;
	y_pos  = newY;
	left   = x_pos - width/2;
	right  = x_pos + width/2;
	top    = y_pos - lenth/2;
	bottom = y_pos + lenth/2;
	//width  = STDBLOCK_width_2 * 2;
}
FLOOR::FLOOR():BLOCK(){
	x_pos  = STDBLOCK_pos;
	y_pos  = STDBLOCK_pos;
	left   = x_pos - STDBLOCK_width_2;
	right  = x_pos + STDBLOCK_width_2;
	top    = y_pos - STDBLOCK_width_2;
	bottom = y_pos + STDBLOCK_width_2;
	width  = STDBLOCK_width_2 * 2;
}
FLOOR::~FLOOR(){
	x_pos = STDBLOCK_pos;
	y_pos = STDBLOCK_pos;
}

void FLOOR::show(){
	setfillcolor(RGB(255,246,143));
	solidrectangle(left,top,right,bottom);
}

void FLOOR::hide(){
	setfillcolor(BLACK);
	solidrectangle(left,top,right,bottom);
}
