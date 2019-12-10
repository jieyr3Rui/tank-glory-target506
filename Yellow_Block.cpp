#include "Yellow_Block.h"

YELLOW_BLOCK::YELLOW_BLOCK(int newX,int newY):BLOCK(newX,newY){
	health = STDYELLOW_BLOCK_health;
}

YELLOW_BLOCK::YELLOW_BLOCK():BLOCK(){
	health = STDYELLOW_BLOCK_health;
}

YELLOW_BLOCK::~YELLOW_BLOCK(){
	x_pos = STDBLOCK_pos;
	y_pos = STDBLOCK_pos;
}

void YELLOW_BLOCK::show(){
	setfillcolor(RGB(139,117,0));
	solidrectangle(left,top,right,bottom);
	setlinecolor(BLACK);
	line(left,top,right,bottom);
	line(left,bottom,right,top);
}

void YELLOW_BLOCK::hide(){
	setfillcolor(BLACK);
	solidrectangle(left,top,right,bottom);
}