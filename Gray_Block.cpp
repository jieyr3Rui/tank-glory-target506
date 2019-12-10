#include "Gray_Block.h"

GRAY_BLOCK::GRAY_BLOCK(int newX,int newY):BLOCK(newX,newY){
	health = STDGRAY_BLOCK_health;
}

GRAY_BLOCK::GRAY_BLOCK():BLOCK(){
	health = STDGRAY_BLOCK_health;
}

GRAY_BLOCK::~GRAY_BLOCK(){
	x_pos = STDBLOCK_pos;
	y_pos = STDBLOCK_pos;
}

void GRAY_BLOCK::show(){
	setfillcolor(DARKGRAY);
	solidrectangle(left,top,right,bottom);
	setlinecolor(BLACK);
	line(left,top,right,bottom);
	line(left,bottom,right,top);
}

void GRAY_BLOCK::hide(){
	setfillcolor(BLACK);
	solidrectangle(left,top,right,bottom);
}