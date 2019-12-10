#include "MyTank.h"

MYTANK::MYTANK(int newX,int newY,COLORREF newColor):TANK(newX,newY,newColor){
	score = 0;
	alive = STDMYTANK_alive;
	health = STDMYTANK_health;
	money = STDMYTANK_money;
	experience = STDMYTANK_range;
	range = STDMYTANK_experience;
	redbullet_Num = 0;
	bluebullet_Num = 0;
	redbuff_Tim = 0;
	bluebuff_Tim = 0;
	load = 0;
}

MYTANK::MYTANK():TANK(){
	score = 0;
	alive = STDMYTANK_death;
	health = STDMYTANK_health;
	money = STDMYTANK_money;
	experience = STDMYTANK_range;
	range = STDMYTANK_experience;
	load = 0;
}

MYTANK::~MYTANK(){
	alive = STDMYTANK_death;
	health = STDMYTANK_health;
	money = STDMYTANK_money;
	experience = STDMYTANK_range;
	range = STDMYTANK_experience;
}

void MYTANK::range_exp(){
	if(experience <= 50)range = 1;
	if(experience > 50 && experience <= 200)range = 2;
	if(experience > 200)range = 3;
}

void MYTANK::destroy_block(){
	money += 1;
	experience += 5;
	range_exp();
	score += 20;
}

void MYTANK::destroy_tank(){
	money += 20;
	experience += 20;
	score += 100;
}

void MYTANK::destroy_tower(){
	score += 300;
}


void MYTANK::be_attacked(int power){
	health -= power;
	if(health <= 0) die();
}

void MYTANK::die(){
	alive = STDMYTANK_death;
}

void MYTANK::judge_move(YELLOW_BLOCK yellow){

}
void MYTANK::show(){
	
	setfillcolor(WHITE); //大圆
	fillcircle(x_pos ,y_pos ,30);
	setfillcolor(LIGHTBLUE);
	if(if_bluebuff())fillcircle(x_pos,y_pos,10);
	setfillcolor(RED); //枪口小圆

	if(if_redbullet()) fillcircle(get_fire_x(),get_fire_y(),6);
	
	if(!if_redbullet())fillcircle(get_fire_x(),get_fire_y(),2);


	setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 16); // 设置线条样式为宽度 10 的实线，端点是平的 
	setlinecolor(LIGHTRED);
	line(x_pos ,y_pos ,x_pos - (int)(50.0 * sinf(theta)),y_pos+ (int)(50.0 *cosf(theta)));
	setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 1);

	setlinecolor(WHITE);
	rectangle(x_pos - STDMYTANK_HealthLen/2,
			  y_pos + STDMYTANK_HealthPos - STDMYTANK_HealthHig/2,
			  x_pos + STDMYTANK_HealthLen/2,
			  y_pos + STDMYTANK_HealthPos + STDMYTANK_HealthHig/2);
	setfillcolor(GREEN);
	fillrectangle(x_pos - STDMYTANK_HealthLen/2,
			      y_pos + STDMYTANK_HealthPos - STDMYTANK_HealthHig/2,
			      x_pos - STDMYTANK_HealthLen/2 + (int)((float)((float)health / (float)STDMYTANK_health) * (float)STDMYTANK_HealthLen),
			      y_pos + STDMYTANK_HealthPos + STDMYTANK_HealthHig/2);
	show_state();
	setlinecolor(GREEN);
	rectangle(400,2700,500,2800);
}


void MYTANK::show_state(){
		settextstyle(28, 0, _T("楷体"));
		char c1[5];
		sprintf(c1, "%d", get_score());//将整形a转换成字符串
		char c2[5];
		sprintf(c2, "%d", get_health());//将整形a转换成字符串
		outtextxy(x_pos -50,y_pos - 50,c1);
		outtextxy(x_pos +50,y_pos - 50,c2);

}
void MYTANK::pick_buff(int buff_type){

	if(buff_type == STDBUFF_red)redbuff_Tim += 10000;
	if(buff_type == STDBUFF_blue)bluebuff_Tim += 10000;
	if(buff_type == STDBUFF_redbullet)redbullet_Num = 10;
	if(buff_type == STDBUFF_bluebullet)bluebullet_Num = 10;
	
}

void MYTANK::buff_fade_load(){
	load++;
	redbuff_Tim -= (redbuff_Tim > 0);
	bluebuff_Tim -= (bluebuff_Tim >0);
	
}

void MYTANK::fire_aBullet(COLORREF bulletColor){
	if(bulletColor == RED)redbullet_Num -= (redbullet_Num > 0);
	if(bulletColor == BLUE)bluebullet_Num -= (bluebullet_Num > 0);
}

void MYTANK::heal(){
	if (x_pos >= 400 && x_pos <= 500 && y_pos >= 2700 && y_pos <= 2800){
		health +=(health <= 4999)*2;
	}
}
