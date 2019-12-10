#include "Grass.h"

GRASS::GRASS(int newX,int newY,int width ,int lenth){
	x_pos  = newX;
	y_pos  = newY;
	left   = x_pos - width/2;
	right  = x_pos + width/2;
	top    = y_pos - lenth/2;
	bottom = y_pos + lenth/2;
	width  = STDBLOCK_width_2 * 2;
}
GRASS::GRASS():BLOCK(){
	x_pos  = STDBLOCK_pos;
	y_pos  = STDBLOCK_pos;
	left   = x_pos - STDBLOCK_width_2;
	right  = x_pos + STDBLOCK_width_2;
	top    = y_pos - STDBLOCK_width_2;
	bottom = y_pos + STDBLOCK_width_2;
	width  = STDBLOCK_width_2 * 2;
}
GRASS::~GRASS(){
	x_pos = STDBLOCK_pos;
	y_pos = STDBLOCK_pos;
}

void GRASS::show(){
	setfillcolor(GREEN);
	solidrectangle(left,top,right,bottom);
}

void GRASS::hide(){
	setfillcolor(BLACK);
	solidrectangle(left,top,right,bottom);
}
