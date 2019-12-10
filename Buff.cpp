#include "Buff.h"

BUFF::BUFF(int newX,int newY,int newId){
	x_pos = newX;
	y_pos = newY;
	id = newId;
	left = x_pos - STDBUFF_width / 2;
	right = x_pos + STDBUFF_width / 2;
	top = y_pos - STDBUFF_width / 2;
	bottom = y_pos + STDBUFF_width / 2;
}

void BUFF::show(){
	if(id == STDBUFF_red)  { setfillcolor(LIGHTRED);  fillrectangle(left,top,right,bottom);}
	if(id == STDBUFF_blue) { setfillcolor(LIGHTBLUE); fillrectangle(left,top,right,bottom);}
	if(id == STDBUFF_redbullet){
		setlinecolor(WHITE);
		rectangle(left,top,right,bottom);
		setfillcolor(LIGHTRED);
		fillcircle(x_pos,y_pos,STDBUFF_width / 2);
		line(left,top,right,bottom);
		line(left,bottom,right,top);
	}
	if(id == STDBUFF_bluebullet){
		setlinecolor(WHITE);
		rectangle(left,top,right,bottom);
		setfillcolor(LIGHTBLUE);
		fillcircle(x_pos,y_pos,STDBUFF_width / 2);
		line(left,top,right,bottom);
		line(left,bottom,right,top);
	}
}

bool BUFF::judge_pick(int tankX,int tankY){
	 return (tankX <= right && tankX >= left && tankY <= bottom && tankY >= top);
}