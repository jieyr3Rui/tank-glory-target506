#include "Big_Block.h"

BIG_BLOCK::BIG_BLOCK(int newX,int newY,int width ,int lenth){
	health = STDYELLOW_BLOCK_health;
	x_pos  = newX;
	y_pos  = newY;
	left   = x_pos - width/2;
	right  = x_pos + width/2;
	top    = y_pos - lenth/2;
	bottom = y_pos + lenth/2;
	//width  = STDBLOCK_width_2 * 2;
}
BIG_BLOCK::BIG_BLOCK():BLOCK(){
	x_pos  = STDBLOCK_pos;
	y_pos  = STDBLOCK_pos;
	left   = x_pos - STDBLOCK_width_2;
	right  = x_pos + STDBLOCK_width_2;
	top    = y_pos - STDBLOCK_width_2;
	bottom = y_pos + STDBLOCK_width_2;
	width  = STDBLOCK_width_2 * 2;
}
BIG_BLOCK::~BIG_BLOCK(){
	x_pos = STDBLOCK_pos;
	y_pos = STDBLOCK_pos;
}

void BIG_BLOCK::show(){
	setfillcolor(WHITE);
	solidrectangle(left,top,right,bottom);
}

void BIG_BLOCK::hide(){
	setfillcolor(BLACK);
	solidrectangle(left,top,right,bottom);
}
