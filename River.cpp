#include "River.h"
RIVER::RIVER(int newX,int newY,int width ,int lenth){
	x_pos  = newX;
	y_pos  = newY;
	left   = x_pos - width/2;
	right  = x_pos + width/2;
	top    = y_pos - lenth/2;
	bottom = y_pos + lenth/2;
	width  = STDBLOCK_width_2 * 2;
}
RIVER::RIVER():BLOCK(){
	x_pos  = STDBLOCK_pos;
	y_pos  = STDBLOCK_pos;
	left   = x_pos - STDBLOCK_width_2;
	right  = x_pos + STDBLOCK_width_2;
	top    = y_pos - STDBLOCK_width_2;
	bottom = y_pos + STDBLOCK_width_2;
	width  = STDBLOCK_width_2 * 2;
}
RIVER::~RIVER(){
	x_pos = STDBLOCK_pos;
	y_pos = STDBLOCK_pos;
}

void RIVER::show(){
	setfillcolor(RGB( 0,191,255));
	solidrectangle(left,top,right,bottom);
}

void RIVER::hide(){
	setfillcolor(BLACK);
	solidrectangle(left,top,right,bottom);
}
