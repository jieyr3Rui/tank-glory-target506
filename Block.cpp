#include "Block.h"

BLOCK::BLOCK(int newX,int newY){
	x_pos  = newX;
	y_pos  = newY;
	left   = x_pos - STDBLOCK_width_2;
	right  = x_pos + STDBLOCK_width_2;
	top    = y_pos - STDBLOCK_width_2;
	bottom = y_pos + STDBLOCK_width_2;
	width  = STDBLOCK_width_2 * 2;
}

BLOCK::BLOCK(){
	x_pos  = STDBLOCK_pos;
	y_pos  = STDBLOCK_pos;
	left   = x_pos - STDBLOCK_width_2;
	right  = x_pos + STDBLOCK_width_2;
	top    = y_pos - STDBLOCK_width_2;
	bottom = y_pos + STDBLOCK_width_2;
	width  = STDBLOCK_width_2 * 2;
}

BLOCK::~BLOCK(){
	x_pos = STDBLOCK_pos;
	y_pos = STDBLOCK_pos;
}

void BLOCK::show(){
	setfillcolor(YELLOW);
	solidrectangle(left,top,right,bottom);
}

void BLOCK::hide(){
	setfillcolor(BLACK);
	solidrectangle(left,top,right,bottom);
}

int BLOCK::get_hit_left(int dis){
	return left - dis;
}

int BLOCK::get_hit_right(int dis){
	return right + dis;
}

int BLOCK::get_hit_top(int dis){
	return top - dis;
}

int BLOCK::get_hit_bottom(int dis){
	return bottom + dis;
}