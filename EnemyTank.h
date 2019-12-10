/***********EnemyTank class****
by jieyr
*****************************/
#ifndef ENEMYTANK_H
#define ENEMYTANK_H
#define STDTANK_xy_speed 3
#include "Tank.h"
#include "graphics.h"

#define INIT_modifier 1
#define STDENEMYTANK_xy_speed 2
#define STDENEMYTANK_HealthPos -50
#define STDENEMYTANK_HealthLen 80
#define STDENEMYTANK_HealthHig 20
#define STDENEMYTANK_health 300
#define STDENEMYTANK_move_dis 50

#define STDENEMYTANK_id_patrolA 1
#define STDENEMYTANK_id_patrolB 2
#define STDENEMYTANK_id_patrolC 3
#define STDENEMYTANK_id_AKbase  4
#define STDENEMYTANK_id_AKme    5

#define STDENEMYTANK_state_patrolA  1
#define STDENEMYTANK_state_patrolB  2
#define STDENEMYTANK_state_patrolC  3
#define STDNEMEYTANK_state_AKbase   4
#define STDENEMYTANK_state_AKme     5
//6个巡逻坐标点
#define STDENEMYTANK_patrolA_x1 1200
#define STDENEMYTANK_patrolA_y1 600
#define STDENEMYTANK_patrolA_x2 1400
#define STDENEMYTANK_patrolA_y2 600
#define STDENEMYTANK_patrolB_x1 1800
#define STDENEMYTANK_patrolB_y1 1400
#define STDENEMYTANK_patrolB_x2 1900
#define STDENEMYTANK_patrolB_y2 1300
#define STDENEMYTANK_patrolC_x1 2600
#define STDENEMYTANK_patrolC_y1 1800
#define STDENEMYTANK_patrolC_x2 2600
#define STDENEMYTANK_patrolC_y2 2000


#define Move_pointA_x 200
#define Move_pointA_y 200

#define Move_pointB_x 1600
#define Move_pointB_y 1600

#define Move_pointC_x 3000
#define Move_pointC_y 3000


class ENEMYTANK:public TANK{
protected:
	int damage_modifier;
	int health;
	int x_move_len;
	int y_move_len;
	int aim_x;
	int aim_y;
	int id;
	int state;
	int next_x;
	int next_y;
public:
	ENEMYTANK(int newX,int newY,COLORREF newColor,int newId,int newState);
	ENEMYTANK();
	~ENEMYTANK();
	void be_attacked(int power);
	bool if_alive();
	void moveto_direct(int new_xpos,int new_ypos);//暂时性动作
	void attack(int goal_x,int goal_y);
	int get_xmove(){return x_move_len;}
	int get_ymove(){return y_move_len;}
	void set_move(int newX,int newY){x_move_len = newX;y_move_len = newY;}
	void set_aim(int newaim_x,int newaim_y);
	int get_aimx(){return aim_x;}
	int get_aimy(){return aim_y;}
	void moveto_aim();//持续性地移动到aim_x 和aim_y
	void show();
	int get_hit_left  (int dis);
	int get_hit_right (int dis);
	int get_hit_bottom(int dis); 
	int get_hit_top   (int dis);
	
	int get_id(){return id;}
	int get_state(){return state;}
	void set_state(int newState){state = newState;}
	bool if_patrolA(){return ((x_pos >= STDENEMYTANK_patrolA_x1 && x_pos <= STDENEMYTANK_patrolA_x2) && (y_pos == STDENEMYTANK_patrolA_y1));}
	bool if_patrolB(){return ((x_pos >= STDENEMYTANK_patrolB_x1 && x_pos <= STDENEMYTANK_patrolB_x2) && ((x_pos + y_pos) == (STDENEMYTANK_patrolB_x1 + STDENEMYTANK_patrolB_y1) ));}
	bool if_patrolC(){return ((y_pos >= STDENEMYTANK_patrolC_y1 && y_pos <= STDENEMYTANK_patrolC_y2) && (x_pos == STDENEMYTANK_patrolC_x1));}
	void set_next(int new_x,int new_y){next_x = new_x;next_y = new_y;}
};
#endif