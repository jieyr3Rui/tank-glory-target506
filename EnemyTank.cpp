#include "EnemyTank.h"

ENEMYTANK::ENEMYTANK(int newX,int newY, COLORREF newColor,int newId,int newState):TANK(newX,newY,newColor){
	health = STDENEMYTANK_health;
	damage_modifier = 1;
	id = newId;
	state = newState;
}

ENEMYTANK::ENEMYTANK():TANK(){
	health = STDENEMYTANK_health;
	health = 300;
	damage_modifier = 1;
	id = 0;
	state = 0;
}

ENEMYTANK::~ENEMYTANK(){
	health = 0;
	damage_modifier = 1;

}

void ENEMYTANK::moveto_direct(int newx_pos,int newy_pos){
	int ans_x,ans_y;
	
	float dis = powf((newx_pos - x_pos) * (newx_pos - x_pos) + (newy_pos - y_pos) * (newy_pos - y_pos),0.5);
	theta = acosf((float)(newx_pos - x_pos)/dis);
	if(newy_pos <= y_pos) theta *= -1;
	theta -= (float)1.573;
//	if(dis >= 200){
		if(x_pos <= newx_pos - STDENEMYTANK_xy_speed) ans_x =  x_pos + STDENEMYTANK_xy_speed;
		else if(x_pos >= newx_pos + STDENEMYTANK_xy_speed) ans_x = x_pos - STDENEMYTANK_xy_speed;
		else ans_x = newx_pos;
	
		if(y_pos <= newy_pos - STDENEMYTANK_xy_speed ) ans_y = y_pos + STDENEMYTANK_xy_speed;
		else if(y_pos >= newy_pos + STDENEMYTANK_xy_speed) ans_y = y_pos - STDENEMYTANK_xy_speed;
		else ans_y = newy_pos;
		x_move_len = ans_x - x_pos;
		y_move_len = ans_y - y_pos;

//	}
//	else {
//		x_move_len = 0;
//		y_move_len = 0;
//	}
	//float dis = powf((newx_pos - x_pos) * (newx_pos - x_pos) + (newy_pos - y_pos) * (newy_pos - y_pos),0.5);
	
	//if((newx_pos - x_pos) * (newy_pos - y_pos) < 0)theta = -1.0 * abs(theta);
	//else theta = abs(theta);
}


void ENEMYTANK::attack(int newx_pos,int newy_pos){
	float dis = powf((newx_pos - x_pos) * (newx_pos - x_pos) + (newy_pos - y_pos) * (newy_pos - y_pos),0.5);

	theta = acosf((float)(newx_pos - x_pos)/dis);
	if(newy_pos <= y_pos) theta *= -1;
	theta -= (float)1.573; //correct theta

	if(dis >= 300.0)moveto_direct(newx_pos,newy_pos);
	else {x_move_len = 0;y_move_len = 0;}
}

void ENEMYTANK::be_attacked(int power){
	health -= power;
}

bool ENEMYTANK::if_alive(){
	return (health > 0);
}

void ENEMYTANK::set_aim(int newaim_x,int newaim_y){
	aim_x = newaim_x;
	aim_y = newaim_y;
}

void ENEMYTANK::moveto_aim(){
	correct_theta(aim_x,aim_y);
	moveto_direct(aim_x,aim_y);
}

void ENEMYTANK::show(){
	setfillcolor(WHITE); //大圆
	fillcircle(x_pos ,y_pos ,30);

	setfillcolor(RED); //枪口小圆
	fillcircle(get_fire_x(),get_fire_y(),2);

	setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 16); // 设置线条样式为宽度 10 的实线，端点是平的 
	setlinecolor(LIGHTRED);
	line(x_pos ,y_pos ,x_pos - (int)(50.0 * sinf(theta)),y_pos+ (int)(50.0 *cosf(theta)));
	setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 1);

	setlinecolor(WHITE);
	rectangle(x_pos - STDENEMYTANK_HealthLen/2,
			  y_pos + STDENEMYTANK_HealthPos - STDENEMYTANK_HealthHig/2,
			  x_pos + STDENEMYTANK_HealthLen/2,
			  y_pos + STDENEMYTANK_HealthPos + STDENEMYTANK_HealthHig/2);
	setfillcolor(RED);
	fillrectangle(x_pos - STDENEMYTANK_HealthLen/2,
			      y_pos + STDENEMYTANK_HealthPos - STDENEMYTANK_HealthHig/2,
			      x_pos - STDENEMYTANK_HealthLen/2 + (int)((float)((float)health / (float)STDENEMYTANK_health) * (float)STDENEMYTANK_HealthLen),
			      y_pos + STDENEMYTANK_HealthPos + STDENEMYTANK_HealthHig/2);
}

int ENEMYTANK::get_hit_left  (int dis){
	return x_pos - dis;
}
int ENEMYTANK::get_hit_right (int dis){
	return x_pos + dis;
}
int ENEMYTANK::get_hit_bottom(int dis){
	return y_pos + dis;
}
int ENEMYTANK::get_hit_top   (int dis){
	return y_pos - dis;
}

