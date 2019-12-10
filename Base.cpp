#include "Base.h"

BASE::BASE(int newX,int newY,bool newId){
	x_pos = newX;
	y_pos = newY;
	id = newId;
	health = STDBASE_health;
}

BASE::BASE(){
	x_pos = 40;
	y_pos = 400;
	id = 0;
	health = STDBASE_health;
}

BASE::~BASE(){
	health = 0;
}

bool BASE::whos(){return id;}

void BASE::show(){
	if(whos())setfillcolor(LIGHTBLUE);
	else setfillcolor(MAGENTA);
	fillcircle(x_pos,y_pos,30);

	setlinecolor(WHITE);
	rectangle(x_pos - STDBASE_HealthLen/2,
			  y_pos + STDBASE_HealthPos - STDBASE_HealthHig/2,
			  x_pos + STDBASE_HealthLen/2,
			  y_pos + STDBASE_HealthPos + STDBASE_HealthHig/2);
	if(whos())setfillcolor(GREEN);
	else setfillcolor(RED);
	fillrectangle(x_pos - STDBASE_HealthLen/2,
			      y_pos + STDBASE_HealthPos - STDBASE_HealthHig/2,
			      x_pos - STDBASE_HealthLen/2 + (int)((float)((float)health / (float)STDBASE_health) * (float)STDBASE_HealthLen),
			      y_pos + STDBASE_HealthPos + STDBASE_HealthHig/2);
}

void BASE::be_attacked(int power){
	health -= (power>health) ? (power - health) : power;
}