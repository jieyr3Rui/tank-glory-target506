#include "Tower.h"

TOWER::TOWER(int newX,int newY,bool newId):TANK(newX,newY,WHITE){

	if (newId == 1)
		health = STDTOWER_me_health;
	else health = STDTOWER_enemy_health;
	id = newId;
	load = 0;
}

TOWER::TOWER():TANK(){

	id = 0;
	load = 0;
}
TOWER::~TOWER(){
}

void TOWER::be_attacked(int power){
	health -= power;
}


void TOWER::show(){
	setfillcolor(WHITE);
	fillcircle(x_pos,y_pos,30);

	if(who()){
		setfillcolor(GREEN);
		setlinecolor(GREEN);
		fillcircle(x_pos,y_pos,10);
		circle(x_pos,y_pos, STDTOWER_effectiveRange);
		
		setlinecolor(WHITE);
		rectangle(x_pos - STDTOWER_HealthLen/2 ,
				  y_pos + STDTOWER_HealthPos - STDTOWER_HealthHig/2,
				  x_pos + STDTOWER_HealthLen/2,
				  y_pos + STDTOWER_HealthPos + STDTOWER_HealthHig/2);
		if(who())setfillcolor(GREEN);
		else setfillcolor(RED);
		fillrectangle(x_pos - STDTOWER_HealthLen/2,
					  y_pos + STDTOWER_HealthPos - STDTOWER_HealthHig/2,
					  x_pos - STDTOWER_HealthLen/2 + (int)(((float)health / (float)STDTOWER_me_health) * (float)STDTOWER_HealthLen),
					  y_pos + STDTOWER_HealthPos + STDTOWER_HealthHig/2);
	}

	else{
		setfillcolor(RED);
		setlinecolor(RED);
		fillcircle(x_pos,y_pos,10);
		circle(x_pos,y_pos, STDTOWER_effectiveRange);
		
		setlinecolor(WHITE);
		rectangle(x_pos - STDTOWER_HealthLen/2 ,
				  y_pos + STDTOWER_HealthPos - STDTOWER_HealthHig/2,
				  x_pos + STDTOWER_HealthLen/2,
				  y_pos + STDTOWER_HealthPos + STDTOWER_HealthHig/2);
		if(who())setfillcolor(GREEN);
		else setfillcolor(RED);
		fillrectangle(x_pos - STDTOWER_HealthLen/2,
					  y_pos + STDTOWER_HealthPos - STDTOWER_HealthHig/2,
					  x_pos - STDTOWER_HealthLen/2 + (int)(((float)health / (float)STDTOWER_enemy_health) * (float)STDTOWER_HealthLen),
					  y_pos + STDTOWER_HealthPos + STDTOWER_HealthHig/2);
	}


	
}