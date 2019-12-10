#include "graphics.h"
#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include "Tank.h"
#include "MyTank.h"
#include "Block.h"
#include "Yellow_Block.h"
#include "Big_Block.h"
#include "River.h"
#include "Gray_Block.h"
#include "EnemyTank.h"
#include "Judge_Shoot.h"
#include "Base.h"
#include "Floor.h"
#include "Grass.h"
#include "Tower.h"
#include "Buff.h"
#include <vector>
#include <ctime>
#include <cmath>

#pragma comment (lib,"MSIMG32.lib")

using namespace std;

#define  KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0) 

#define Screen_width 3200
#define Screen_high 3200
#define move_space_left 400
#define move_space_right 2800
#define move_space_top 400
#define move_space_bottom 2800
#define s sqrt(2)

int count_5ms = 0;
int count = 0;
int counttime = 0;
void count_game(){
	count_5ms++;
	if(count_5ms >= 33){
		count++;
		counttime++;			////////counttime为游戏总时间
		count_5ms = 0;
	}
}

int create_buff_tim = 0;
int create_bufftower_timA = 0;
int create_bufftower_timB = 0;
int create_bufftower_timC = 0;
int create_bufftower_timD = 0;
int create_AKbase = 0;


IMAGE buffer(Screen_width,Screen_high);

vector <BULLET> blue_bullet;
vector <BULLET>::iterator it_bluebullet;
vector <BULLET> red_bullet;
vector <BULLET>::iterator it_redbullet;

vector <YELLOW_BLOCK> yellow_block;
vector <YELLOW_BLOCK>::iterator it_yellow;
vector <GRAY_BLOCK> gray_block;
vector <GRAY_BLOCK>::iterator it_gray;
vector <BIG_BLOCK> big_block;
vector <BIG_BLOCK>::iterator it_big;
vector <ENEMYTANK> enemytank;
vector <ENEMYTANK>::iterator it_enemy;
vector <ENEMYTANK>::iterator it_enemy2;//judge move
vector <RIVER> river;
vector <RIVER>::iterator it_river;
vector <GRASS> grass;
vector <GRASS>::iterator it_grass;
vector <TOWER> tower;
vector <TOWER>::iterator it_tower;
vector <FLOOR> floor1;
vector <FLOOR>::iterator it_floor;
vector <BUFF> buff;
vector <BUFF>::iterator it_buff;
vector <BASE> base;
vector <BASE>::iterator it_base;


MYTANK me(800,2400,WHITE);
BASE myBase(600,2600,0);
BASE enemyBase(2600,600,0);

void sleep(int ms)
{
    static clock_t oldclock = clock();      // 静态变量，记录上一次 tick
    oldclock += ms * CLOCKS_PER_SEC / 1000; // 更新 tick
    if (clock() > oldclock)                 // 如果已经超时，无需延时
    {
        oldclock = clock();
    }
    else
        while(clock() < oldclock)           // 延时
        {
            Sleep(1);    // 释放 CPU 控制权，降低 CPU 占用率
        }
}

int get_distance(int x1,int y1,int x2,int y2){ //两点距离公式
	float dis = powf((float) ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)), 0.5);
	return (int)dis;
}





//要取得[a,b]的随机整数，使用(rand() % (b-a+1))+ a;
//create a random yellow block
void create_yellow_block(int M_left,int M_right,int M_top, int M_bottom){//随机产生个块
	int newX = (rand() % (M_right - M_left + 1)) + M_left;
	int newY = (rand() % (M_bottom - M_top + 1)) + M_top;
	YELLOW_BLOCK aYellow_Block(newX,newY);
	yellow_block.push_back(aYellow_Block);
}

void create_gray_block(int M_left,int M_right,int M_top, int M_bottom){//随机产生个块
	int newX = (rand() % (M_right - M_left + 1)) + M_left;
	int newY = (rand() % (M_bottom - M_top + 1)) + M_top;
	GRAY_BLOCK aGray_Block(newX,newY);
	gray_block.push_back(aGray_Block);
}

void create_buff(int M_left,int M_right,int M_top, int M_bottom){//
	int newX = (rand() % (M_right - M_left + 1)) + M_left;
	int newY = (rand() % (M_bottom - M_top + 1)) + M_top;
	int random_number = (rand() % 4 + 1);
	BUFF abuff(newX,newY,STDBUFF_red);
	buff.push_back(abuff);
}


void me_Fire_B(){ //
	if(me.if_bluebullet()){
		BULLET newBullet1(me.get_fire_x(),me.get_fire_y(),me.get_fire_theta(),BLUE,STDBULLET_me);//我发蓝色子弹
		BULLET newBullet2(me.get_fire_x(),me.get_fire_y(),me.get_fire_theta() - 0.4,BLUE,STDBULLET_me);
		BULLET newBullet3(me.get_fire_x(),me.get_fire_y(),me.get_fire_theta() + 0.4,BLUE,STDBULLET_me);
		blue_bullet.push_back(newBullet1);
		blue_bullet.push_back(newBullet2);
		blue_bullet.push_back(newBullet3);
		me.fire_aBullet(BLUE);
	}
}

void me_Fire_R(){ //我发红色子弹
	if(me.if_redbullet()){ 
		BULLET newBullet(me.get_fire_x(),me.get_fire_y(),me.get_fire_theta(),RED,STDBULLET_me);
		red_bullet.push_back(newBullet);
		me.fire_aBullet(RED);
	}
}

void me_Fire_A(){//A
	BULLET newBullet1(me.get_fire_x(),me.get_fire_y(),me.get_fire_theta(),BLUE,STDBULLET_me);
	blue_bullet.push_back(newBullet1);
}

void tower_Fire(){
	for(it_tower = tower.begin();it_tower != tower.end();it_tower++){
		it_tower->load++;
		if(get_distance(me.get_x(),me.get_y(),it_tower->get_x(),it_tower->get_y()) <=  STDTOWER_effectiveRange && it_tower->load >= 30 && (!it_tower->who())){
			it_tower->correct_theta(me.get_x(),me.get_y());
			BULLET newBullet(it_tower->get_fire_x(),it_tower->get_fire_y(),it_tower->get_fire_theta(),BLUE,STDBULLET_enemy);
			blue_bullet.push_back(newBullet);
			it_tower->load = 0;
		}
		if(it_tower->who()){
			for(it_enemy = enemytank.begin();it_enemy != enemytank.end();it_enemy++){
				if(get_distance(it_tower->get_x(),it_tower->get_y(),it_enemy->get_x(),it_enemy->get_y()) <= STDTOWER_effectiveRange && it_tower->load >=30){
					it_tower->correct_theta(it_enemy->get_x(),it_enemy->get_y());
					BULLET newBullet(it_tower->get_fire_x(),it_tower->get_fire_y(),it_tower->get_fire_theta(),BLUE,STDBULLET_me);
					blue_bullet.push_back(newBullet);
					it_tower->load = 0;
				}
			}
		}
	}
}


void enemy_Fire_R(int attack_x,int attack_y){
	for(it_enemy = enemytank.begin();it_enemy != enemytank.end();it_enemy++){
		it_enemy->load ++;
		if(it_enemy->load >= 30 && 
			get_distance(attack_x,attack_y,it_enemy->get_x(),it_enemy->get_y()) <= 300){
			BULLET newBullet(it_enemy->get_fire_x(),it_enemy->get_fire_y(),it_enemy->get_fire_theta(),RED,STDBULLET_enemy);
			red_bullet.push_back(newBullet);
			it_enemy->load = 0;
		}

	}
}


void create_midroad(){
	int i=0,j=0,k;
	for (k=0;k<=200;k+=30){
		for (i=800+k,j=2200+k;i<=2200+k&&j>=800+k;i+=60,j-=60){
			FLOOR floor3(i,j,30,30);
			floor1.push_back(floor3);
		}
	}
}

void create_road(int left,int top, int right,int bottom){

	int i=0,j=0;
	if ((right - left) < (bottom - top)){
		for (i = top ;i < bottom;i+=45){
			for (j=0;j<7;j+=3){
				int a = left + floor((rand() % ( right - left)));
				FLOOR floor2(a,i,30,30);
				floor1.push_back(floor2);
			}
		}
	}

	else {
		for (i = left ;i < right ;i+=45){
			for (j=0;j<7;j+=3){
				int a = top + floor((rand() % ( bottom - top)));
				FLOOR floor2(i,a,30,30);
				floor1.push_back(floor2);
			}
		}
	}
}



/**********************************boundary set*************************/

void create_boundary(){
	int t = 0;

	BIG_BLOCK Big_Block1(200,1600,400,3200); big_block.push_back(Big_Block1);//left
	BIG_BLOCK Big_Block3(1600,200,2400,400);big_block.push_back(Big_Block3);//top
	BIG_BLOCK Big_Block4(3000,1600,400,3200);big_block.push_back(Big_Block4);//right
	BIG_BLOCK Big_Block2(1600,3000,2400,400); big_block.push_back(Big_Block2);//bottom
	



	/*for (t = 0 ; t < 80; t++){
		GRAY_BLOCK Gray_Block(370+30*t,370);
		gray_block.push_back(Gray_Block);
	}
	for (t = 0 ; t < 80; t++){
		GRAY_BLOCK Gray_Block(370,370+30*t);
		gray_block.push_back(Gray_Block);
	}
	for (t = 0 ; t < 80; t++){
		GRAY_BLOCK Gray_Block(2830,370+30*t);
		gray_block.push_back(Gray_Block);
	}
	for (t = 0 ; t < 80; t++){
		GRAY_BLOCK Gray_Block(370+30*t,2830);
		gray_block.push_back(Gray_Block);
	}*/
	
}
	



/***************create base**************************/

void create_base(){


	/*************************Tower************************/

	TOWER myTower1(600,2300,STDTOWER_me); tower.push_back(myTower1);
	TOWER myTower2(900,2600,STDTOWER_me); tower.push_back(myTower2);
	TOWER myTower3(900,2300,STDTOWER_me); tower.push_back(myTower3);
	TOWER myTower4(600,1600,STDTOWER_me); tower.push_back(myTower4);
	TOWER myTower5(600,1100,STDTOWER_me); tower.push_back(myTower5);
	TOWER myTower6(1600,2600,STDTOWER_me); tower.push_back(myTower6);
	TOWER myTower7(2100,2600,STDTOWER_me); tower.push_back(myTower7);
	TOWER myTower8(1200,2000,STDTOWER_me); tower.push_back(myTower8);
	TOWER myTower9(1450,1750,STDTOWER_me); tower.push_back(myTower9);

	TOWER enemyTower1(2300,600,STDTOWER_enemy); tower.push_back(enemyTower1);
	TOWER enemyTower2(2600,900,STDTOWER_enemy); tower.push_back(enemyTower2);
	TOWER enemyTower3(2300,900,STDTOWER_enemy); tower.push_back(enemyTower3);
	TOWER enemyTower4(1600,600,STDTOWER_enemy); tower.push_back(enemyTower4);
	TOWER enemyTower5(1100,600,STDTOWER_enemy); tower.push_back(enemyTower5);
	TOWER enemyTower6(2600,1600,STDTOWER_enemy); tower.push_back(enemyTower6);
	TOWER enemyTower7(2600,2100,STDTOWER_enemy); tower.push_back(enemyTower7);
	TOWER enemyTower8(2000,1200,STDTOWER_enemy); tower.push_back(enemyTower8);
	TOWER enemyTower9(1750,1450,STDTOWER_enemy); tower.push_back(enemyTower9);
	/***********our base*************/

	
	base.push_back(myBase);


	int z;
/*	for (z=0;z<3;z++)
	{
		YELLOW_BLOCK aYellow_Block(15+30*z,310); 
		yellow_block.push_back(aYellow_Block);
	}

	for (z=0;z<=6;z++)
	{
		YELLOW_BLOCK aYellow_Block(105,310+30*z);
		yellow_block.push_back(aYellow_Block);
	}

	for (z=0;z<3;z++)
	{
		YELLOW_BLOCK aYellow_Block(15+30*z,490);
		yellow_block.push_back(aYellow_Block);
	}*/

	for (z=0;z<=7;z++)
	{
		GRAY_BLOCK aGray_Block(500,2500+30*z);
		gray_block.push_back(aGray_Block);
	}

	for (z=0;z<=7;z++)
	{
		GRAY_BLOCK aGray_Block(500+30*z,2710);
		gray_block.push_back(aGray_Block);
	}

	for (z=0;z<=7;z++)
	{
		GRAY_BLOCK aGray_Block(500+30*z,2500);
		gray_block.push_back(aGray_Block);
	}
	for (z=0;z<=7;z++)
	{
		GRAY_BLOCK aGray_Block(710,2500+30*z);
		gray_block.push_back(aGray_Block);
	} 

	/***********enemy's base***********/



	base.push_back(enemyBase);

	for (z=0;z<=7;z++)
	{
		GRAY_BLOCK aGray_Block(2500+30*z,500);
		gray_block.push_back(aGray_Block);
	}

	for (z=0;z<=7;z++) 
	{
		GRAY_BLOCK aGray_Block(2710,500+30*z);
		gray_block.push_back(aGray_Block);
	}

	for (z=0;z<=7;z++)
	{
		GRAY_BLOCK aGray_Block(2500,500+30*z);
		gray_block.push_back(aGray_Block);
	}
	for (z=0;z<=7;z++)
	{
		GRAY_BLOCK aGray_Block(2500+30*z,710);
		gray_block.push_back(aGray_Block);
	}

}

/******************************set scene*******************************/

void set_scene(){
	int i=0;

	FLOOR ground1(700,2500,600,600);floor1.push_back(ground1);
	FLOOR ground2(2500,700,600,600);floor1.push_back(ground2);
	FLOOR ground3(1100,1100,500,500);floor1.push_back(ground3);
	FLOOR ground4(2100,2100,500,500);floor1.push_back(ground4);
			
	RIVER river1(825,1575,50,1250);          river.push_back(river1);
	RIVER river2(1575,825,1250,50);          river.push_back(river2);
	RIVER river3(2370,1625,50,1250);          river.push_back(river3);
	RIVER river4(1625,2370,1250,50);          river.push_back(river4);

	for (i=0;i<650;i+=30){
		YELLOW_BLOCK yellow_block_middle(800+i,2200-i);
		yellow_block.push_back(yellow_block_middle);
	}
	for (i=800;i<1400;i+=30){
		YELLOW_BLOCK yellow_block_middle(800+i,2200-i);
		yellow_block.push_back(yellow_block_middle);
	}
	for (i=0;i<650;i+=30){
		YELLOW_BLOCK yellow_block_middle(1000+i,2400-i);
		yellow_block.push_back(yellow_block_middle);
	}
	for (i=800;i<1400;i+=30){
		YELLOW_BLOCK yellow_block_middle(1000+i,2400-i);
		yellow_block.push_back(yellow_block_middle);
	}
	
	GRASS grass1(1000,1600,200,400);         grass.push_back(grass1);
	GRASS grass2(1600,1000,400,200);         grass.push_back(grass2);
	GRASS grass3(2200,1600,200,400);         grass.push_back(grass3);
	GRASS grass4(1600,2200,400,200);         grass.push_back(grass4);

	ENEMYTANK patrol1(1400,600,GREEN,1,1);enemytank.push_back(patrol1);
	ENEMYTANK patrol2(1800,1400,GREEN,2,2);enemytank.push_back(patrol2);
	ENEMYTANK patrol3(2600,1800,GREEN,3,3);enemytank.push_back(patrol3);

	TOWER enemyTower1(1350,1000,STDTOWER_enemy); tower.push_back(enemyTower1);
	TOWER enemyTower2(1000,1350,STDTOWER_enemy); tower.push_back(enemyTower2);
	TOWER enemyTower3(2200,1850,STDTOWER_enemy); tower.push_back(enemyTower3);
	TOWER enemyTower4(1850,2200,STDTOWER_enemy); tower.push_back(enemyTower4);

	BIG_BLOCK defense1(925,1350,40,100);big_block.push_back(defense1);
	BIG_BLOCK defense2(1075,1350,40,100);big_block.push_back(defense2);
	BIG_BLOCK defense3(1350,925,100,40);big_block.push_back(defense3);
	BIG_BLOCK defense4(1350,1075,100,40);big_block.push_back(defense4);	
	BIG_BLOCK defense5(2275,1850,40,100);big_block.push_back(defense5);
	BIG_BLOCK defense6(2125,1850,40,100);big_block.push_back(defense6);
	BIG_BLOCK defense7(1850,2275,100,40);big_block.push_back(defense7);
	BIG_BLOCK defense8(1850,2125,100,40);big_block.push_back(defense8);

	//ENEMYTANK patrol4(2300,2000,GREEN,3,3);enemytank.push_back(patrol4);


	/******************************middle defense***********************/
/*	int i,j=0;
	for(i=0;i<6;i=i+2){
		for (j=0;j<10;j++){
		YELLOW_BLOCK yellow_block_left(360+30*i,265+30*j);
		yellow_block.push_back(yellow_block_left);
		}
	}
	for(i=2;i<7;i=i+2){
		for (j=0;j<10;j++){
		YELLOW_BLOCK yellow_block_right(995+30*i,265+30*j);
		yellow_block.push_back(yellow_block_right);
		}
	}*/
	/**************************our trenches*************************/
/*	for(i=0;i<5;i++){
		GRAY_BLOCK gray_block_left_trench(300,50+30*i);
		gray_block.push_back(gray_block_left_trench);
	}
	for(i=0;i<5;i++){
		GRAY_BLOCK gray_block_left_trench(250,100+30*i);
		gray_block.push_back(gray_block_left_trench);
	}
	/*for(i=0;i<5;i++){
		YELLOW_BLOCK yellow_block_left_trench(200,150+30*i);
		yellow_block.push_back(yellow_block_left_trench);
	}*/
/*	for(i=0;i<5;i++){
		GRAY_BLOCK gray_block_left_trench(300,630+30*i);
		gray_block.push_back(gray_block_left_trench);
	}
	for(i=0;i<5;i++){
		GRAY_BLOCK gray_block_left_trench(250,580+30*i);
		gray_block.push_back(gray_block_left_trench);
	}
	/*for(i=0;i<5;i++){
		YELLOW_BLOCK yellow_block_left_trench(200,530+30*i);
		yellow_block.push_back(yellow_block_left_trench);
	}*/
	/*************************enemy's trenches************************/
/*	for(i=0;i<5;i++){
		GRAY_BLOCK gray_block_left_trench(1225,50+30*i);
		gray_block.push_back(gray_block_left_trench);
	}
	for(i=0;i<5;i++){
		GRAY_BLOCK gray_block_left_trench(1275,100+30*i);
		gray_block.push_back(gray_block_left_trench);
	}
	/*for(i=0;i<5;i++){
		YELLOW_BLOCK yellow_block_left_trench(1325,150+30*i);
		yellow_block.push_back(yellow_block_left_trench);
	}*/
/*	for(i=0;i<5;i++){
		GRAY_BLOCK gray_block_left_trench(1225,630+30*i);
		gray_block.push_back(gray_block_left_trench);
	}
	for(i=0;i<5;i++){
		GRAY_BLOCK gray_block_left_trench(1275,580+30*i);
		gray_block.push_back(gray_block_left_trench);
	}
	/*for(i=0;i<5;i++){
		YELLOW_BLOCK yellow_block_left_trench(1325,530+30*i);
		yellow_block.push_back(yellow_block_left_trench);
	}*/
}




/******************************************************************************************************************************/
void me_judge_move(int x_move,int y_move){
	//由于vector 传递参数时一直出错，故直接写
	//	moveto(x_pos + x_move * STDTANK_xy_speed ,y_pos + y_move * STDTANK_xy_speed);
	int trend_x = me.get_x() + x_move * STDTANK_xy_speed;
	int trend_y = me.get_y() + y_move * STDTANK_xy_speed;
	int ans_x = x_move;
	int ans_y = y_move;
	if(trend_x < 10 || trend_x > Screen_width - 10) ans_x = 0;
	if(trend_y < 10 || trend_y > Screen_high  - 10) ans_y = 0;
	/********yellow block*******/
	for(it_yellow = yellow_block.begin();it_yellow != yellow_block.end();it_yellow++){ //for loop judge me and block

		if(trend_x >= it_yellow->get_hit_left  (STDBLOCK_move_dis) &&  //trend (x,y) is in the block
		   trend_x <= it_yellow->get_hit_right (STDBLOCK_move_dis) &&  
		   trend_y <= it_yellow->get_hit_bottom(STDBLOCK_move_dis) &&  
		   trend_y >= it_yellow->get_hit_top   (STDBLOCK_move_dis)) {

			if(me.get_x() <= it_yellow->get_hit_left  (STDBLOCK_move_dis) || //last(x,y) is at the left or right of block
			   me.get_x() >= it_yellow->get_hit_right (STDBLOCK_move_dis)){
				ans_x = 0;
			}

			if(me.get_y() <= it_yellow->get_hit_top   (STDBLOCK_move_dis) ||  //last(x,y) is at the 
			   me.get_y() >= it_yellow->get_hit_bottom(STDBLOCK_move_dis)){
				ans_y = 0;
			}

		}
		if(ans_x == 0 && ans_y == 0)break;
	}
    /***********gray block***********/
	for(it_gray = gray_block.begin();it_gray != gray_block.end();it_gray++){ //for loop judge me and block

		if(trend_x >= it_gray->get_hit_left  (STDBLOCK_move_dis) &&  //trend (x,y) is in the block
		   trend_x <= it_gray->get_hit_right (STDBLOCK_move_dis) &&  
		   trend_y <= it_gray->get_hit_bottom(STDBLOCK_move_dis) &&  
		   trend_y >= it_gray->get_hit_top   (STDBLOCK_move_dis)) {

			if(me.get_x() <= it_gray->get_hit_left  (STDBLOCK_move_dis) || //last(x,y) is at the left or right of block
			   me.get_x() >= it_gray->get_hit_right (STDBLOCK_move_dis)){
				ans_x = 0;
			}

			if(me.get_y() <= it_gray->get_hit_top   (STDBLOCK_move_dis) ||  //last(x,y) is at the 
			   me.get_y() >= it_gray->get_hit_bottom(STDBLOCK_move_dis)){
				ans_y = 0;
			}

		}
		if(ans_x == 0 && ans_y == 0)break;
	}
	/***********big block*************/
	for(it_big = big_block.begin();it_big != big_block.end();it_big++){ //for loop judge me and block

		if(trend_x >= it_big->get_hit_left  (STDBLOCK_move_dis) &&  //trend (x,y) is in the block
		   trend_x <= it_big->get_hit_right (STDBLOCK_move_dis) &&  
		   trend_y <= it_big->get_hit_bottom(STDBLOCK_move_dis) &&  
		   trend_y >= it_big->get_hit_top   (STDBLOCK_move_dis)) {

			if(me.get_x() <= it_big->get_hit_left  (STDBLOCK_move_dis) || //last(x,y) is at the left or right of block
			   me.get_x() >= it_big->get_hit_right (STDBLOCK_move_dis)){
				ans_x = 0;
			}

			if(me.get_y() <= it_big->get_hit_top   (STDBLOCK_move_dis) ||  //last(x,y) is at the 
			   me.get_y() >= it_big->get_hit_bottom(STDBLOCK_move_dis)){
				ans_y = 0;
			}

		}
		if(ans_x == 0 && ans_y == 0)break;
	}
	/*************river ***********/
	for(it_river = river.begin();it_river != river.end();it_river++){ //for loop judge me and block

		if(trend_x >= it_river->get_hit_left  (STDBLOCK_move_dis) &&  //trend (x,y) is in the block
		   trend_x <= it_river->get_hit_right (STDBLOCK_move_dis) &&  
		   trend_y <= it_river->get_hit_bottom(STDBLOCK_move_dis) &&  
		   trend_y >= it_river->get_hit_top   (STDBLOCK_move_dis)) {

			if(me.get_x() <= it_river->get_hit_left  (STDBLOCK_move_dis) || //last(x,y) is at the left or right of block
			   me.get_x() >= it_river->get_hit_right (STDBLOCK_move_dis)){
				ans_x = 0;
			}

			if(me.get_y() <= it_river->get_hit_top   (STDBLOCK_move_dis) ||  //last(x,y) is at the 
			   me.get_y() >= it_river->get_hit_bottom(STDBLOCK_move_dis)){
				ans_y = 0;
			}

		}
		if(ans_x == 0 && ans_y == 0)break;
	}



	me.move(ans_x,ans_y);
		/******************buff*******************/
	for(it_buff = buff.begin();it_buff != buff.end();){
		if(me.get_x() > it_buff->get_x() - 10 &&
		   me.get_x() < it_buff->get_x() + 10 &&
		   me.get_y() > it_buff->get_y() - 10 &&
		   me.get_y() < it_buff->get_y() + 10){
			me.pick_buff(it_buff->get_id());
			it_buff = buff.erase(it_buff);
		}
		else ++it_buff;
	}
	
	me.heal();

}
/*************************************************************************************************************************************/

void move_judge_enemy(){
	int trend_x;
	int trend_y;
	int ans_x;
	int ans_y;
	for(it_enemy = enemytank.begin();it_enemy != enemytank.end();it_enemy++){
		trend_x = it_enemy->get_x() + it_enemy->get_xmove();
		trend_y = it_enemy->get_y() + it_enemy->get_ymove();
		ans_x = it_enemy->get_xmove();
		ans_y = it_enemy->get_ymove();
		/**************yellow block*******************/
		for(it_yellow = yellow_block.begin();it_yellow != yellow_block.end();it_yellow++){

			if(trend_x >= it_yellow->get_hit_left  (STDBLOCK_move_dis) &&  //trend (x,y) is in the block
				trend_x <= it_yellow->get_hit_right (STDBLOCK_move_dis) &&  
				trend_y <= it_yellow->get_hit_bottom(STDBLOCK_move_dis) &&  
				trend_y >= it_yellow->get_hit_top   (STDBLOCK_move_dis)){

					if(it_enemy->get_x() <= it_yellow->get_hit_left  (STDBLOCK_move_dis) || //last(x,y) is at the left or right of block
					   it_enemy->get_x() >= it_yellow->get_hit_right (STDBLOCK_move_dis)){
							ans_x = 0;
					}

					if(it_enemy->get_y() <= it_yellow->get_hit_top   (STDBLOCK_move_dis) ||  //last(x,y) is at the 
					   it_enemy->get_y() >= it_yellow->get_hit_bottom(STDBLOCK_move_dis)){
							ans_y = 0;
					}
			}
		}
		/***********************gray block************************/
		for(it_gray = gray_block.begin();it_gray != gray_block.end();it_gray++){

			if(trend_x >= it_gray->get_hit_left  (STDBLOCK_move_dis) &&  //trend (x,y) is in the block
				trend_x <= it_gray->get_hit_right (STDBLOCK_move_dis) &&  
				trend_y <= it_gray->get_hit_bottom(STDBLOCK_move_dis) &&  
				trend_y >= it_gray->get_hit_top   (STDBLOCK_move_dis)){

					if(it_enemy->get_x() <= it_gray->get_hit_left  (STDBLOCK_move_dis) || //last(x,y) is at the left or right of block
					   it_enemy->get_x() >= it_gray->get_hit_right (STDBLOCK_move_dis)){
							ans_x = 0;
					}

					if(it_enemy->get_y() <= it_gray->get_hit_top   (STDBLOCK_move_dis) ||  //last(x,y) is at the 
					   it_enemy->get_y() >= it_gray->get_hit_bottom(STDBLOCK_move_dis)){
							ans_y = 0;
					}
			}
		}
		/********************big lock**************************/
		for(it_big = big_block.begin();it_big != big_block.end();it_big++){

			if(trend_x >= it_big->get_hit_left  (STDBLOCK_move_dis) &&  //trend (x,y) is in the block
				trend_x <= it_big->get_hit_right (STDBLOCK_move_dis) &&  
				trend_y <= it_big->get_hit_bottom(STDBLOCK_move_dis) &&  
				trend_y >= it_big->get_hit_top   (STDBLOCK_move_dis)){

					if(it_enemy->get_x() <= it_big->get_hit_left  (STDBLOCK_move_dis) || //last(x,y) is at the left or right of block
					   it_enemy->get_x() >= it_big->get_hit_right (STDBLOCK_move_dis)){
							ans_x = 0;
					}

					if(it_enemy->get_y() <= it_big->get_hit_top   (STDBLOCK_move_dis) ||  //last(x,y) is at the 
					   it_enemy->get_y() >= it_big->get_hit_bottom(STDBLOCK_move_dis)){
							ans_y = 0;
					}
			}
		}
		/********************river*************************/
		for(it_river = river.begin();it_river != river.end();it_river++){

			if(trend_x >= it_river->get_hit_left  (STDBLOCK_move_dis) &&  //trend (x,y) is in the block
				trend_x <= it_river->get_hit_right (STDBLOCK_move_dis) &&  
				trend_y <= it_river->get_hit_bottom(STDBLOCK_move_dis) &&  
				trend_y >= it_river->get_hit_top   (STDBLOCK_move_dis)){

					if(it_enemy->get_x() <= it_river->get_hit_left  (STDBLOCK_move_dis) || //last(x,y) is at the left or right of block
					   it_enemy->get_x() >= it_river->get_hit_right (STDBLOCK_move_dis)){
							ans_x = 0;
					}

					if(it_enemy->get_y() <= it_river->get_hit_top   (STDBLOCK_move_dis) ||  //last(x,y) is at the 
					   it_enemy->get_y() >= it_river->get_hit_bottom(STDBLOCK_move_dis)){
							ans_y = 0;
					}
			}
		}
		/*******************************enemy tank************************************/


		for (it_enemy2 = enemytank.begin();it_enemy2 != enemytank.end();it_enemy2++){
			
		if(trend_x >= it_enemy2->get_hit_left  (STDENEMYTANK_move_dis) &&  //trend (x,y) is in the block
			trend_x <= it_enemy2->get_hit_right (STDENEMYTANK_move_dis) &&  
			trend_y <= it_enemy2->get_hit_bottom(STDENEMYTANK_move_dis) &&  
			trend_y >= it_enemy2->get_hit_top   (STDENEMYTANK_move_dis) && 
			 (it_enemy2->get_state() != STDENEMYTANK_state_patrolA) &&
			 (it_enemy2->get_state() != STDENEMYTANK_state_patrolB) && 
			 (it_enemy2->get_state() != STDENEMYTANK_state_patrolC)){

				if(it_enemy->get_x() <= it_enemy2->get_hit_left  (STDENEMYTANK_move_dis) || //last(x,y) is at the left or right of block
				   it_enemy->get_x() >= it_enemy2->get_hit_right (STDENEMYTANK_move_dis)){
						ans_x = 0;
				}

				if(it_enemy->get_y() <= it_enemy2->get_hit_top   (STDENEMYTANK_move_dis) ||  //last(x,y) is at the 
				   it_enemy->get_y() >= it_enemy2->get_hit_bottom(STDENEMYTANK_move_dis)){
						ans_y = 0;	
				}


			}
		}
	

		/*************************************/
		it_enemy->set_move(ans_x,ans_y);
		it_enemy->moveto(it_enemy->get_x() + it_enemy->get_xmove(),it_enemy->get_y() + it_enemy->get_ymove());
	}
}

/****************************************************************************************************************************************/

void JS_bluebullet_yellowblock(){
	bool if_shoot;
			for(it_bluebullet = blue_bullet.begin();it_bluebullet != blue_bullet.end();){
		if_shoot = 0;

		for(it_yellow = yellow_block.begin();it_yellow != yellow_block.end();){
			if(it_bluebullet->get_x() >= it_yellow->get_hit_left  (STDBLOCK_hit_dis) &&  //碰撞判定
			   it_bluebullet->get_x() <= it_yellow->get_hit_right (STDBLOCK_hit_dis) &&  
		       it_bluebullet->get_y() <= it_yellow->get_hit_bottom(STDBLOCK_hit_dis) &&  
			   it_bluebullet->get_y() >= it_yellow->get_hit_top   (STDBLOCK_hit_dis)){
				if_shoot = 1;
				it_yellow = yellow_block.erase(it_yellow);
				break;
			}
			else{
				++it_yellow;
	
			}
		}

		if(if_shoot){
			it_bluebullet = blue_bullet.erase(it_bluebullet);
		}
		else{
			++it_bluebullet;
		}
	}

	
}
void JS_bluebullet_grayblock(){
	bool if_shoot = 0;
	for(it_bluebullet = blue_bullet.begin();it_bluebullet != blue_bullet.end();){
		if_shoot = 0;

		for(it_gray = gray_block.begin();it_gray != gray_block.end();it_gray++){
			if(it_bluebullet->get_x() >= it_gray->get_hit_left  (STDBLOCK_hit_dis) &&  
			   it_bluebullet->get_x() <= it_gray->get_hit_right (STDBLOCK_hit_dis) &&  
		       it_bluebullet->get_y() <= it_gray->get_hit_bottom(STDBLOCK_hit_dis) &&  
			   it_bluebullet->get_y() >= it_gray->get_hit_top   (STDBLOCK_hit_dis)){
				if_shoot = 1;
				break;
			}
		}

		if(if_shoot){
			it_bluebullet = blue_bullet.erase(it_bluebullet);
 
		}
		else{
			++it_bluebullet;
		}
	}
}

void JS_bluebullet_bigblock(){
	bool if_shoot = 0;
	for(it_bluebullet = blue_bullet.begin();it_bluebullet != blue_bullet.end();){
		if_shoot = 0;

		for(it_big = big_block.begin();it_big != big_block.end();it_big++){
			if(it_bluebullet->get_x() >= it_big->get_hit_left  (STDBLOCK_hit_dis) &&  
			   it_bluebullet->get_x() <= it_big->get_hit_right (STDBLOCK_hit_dis) &&  
		       it_bluebullet->get_y() <= it_big->get_hit_bottom(STDBLOCK_hit_dis) &&  
			   it_bluebullet->get_y() >= it_big->get_hit_top   (STDBLOCK_hit_dis)){
				if_shoot = 1;
				break;
			}
		}

		if(if_shoot){
			it_bluebullet = blue_bullet.erase(it_bluebullet);
 
		}
		else{
			++it_bluebullet;
		}
	}
}
void JS_redbullet_yellowblock(){
	bool if_shoot = 0;
	for(it_redbullet = red_bullet.begin();it_redbullet != red_bullet.end();){
		if_shoot = 0;

		for(it_yellow = yellow_block.begin();it_yellow != yellow_block.end();){
			if(it_redbullet->get_x() >= it_yellow->get_hit_left  (STDBLOCK_hit_dis) &&  
			   it_redbullet->get_x() <= it_yellow->get_hit_right (STDBLOCK_hit_dis) &&  
		       it_redbullet->get_y() <= it_yellow->get_hit_bottom(STDBLOCK_hit_dis) &&  
			   it_redbullet->get_y() >= it_yellow->get_hit_top   (STDBLOCK_hit_dis)){
				if_shoot = 1;
				it_yellow = yellow_block.erase(it_yellow);
				break;
			}
			else{
				++it_yellow;
	
			}
		}

		if(if_shoot){
			it_redbullet = red_bullet.erase(it_redbullet);
		}
		else{
			++it_redbullet;
		}
	}
}

void JS_redbullet_grayblock(){
	bool if_shoot = 0;
	for(it_redbullet = red_bullet.begin();it_redbullet != red_bullet.end();){
		if_shoot = 0;

		for(it_gray = gray_block.begin();it_gray != gray_block.end();){
			if(it_redbullet->get_x() >= it_gray->get_hit_left  (STDBLOCK_hit_dis) &&  
			   it_redbullet->get_x() <= it_gray->get_hit_right (STDBLOCK_hit_dis) &&  
		       it_redbullet->get_y() <= it_gray->get_hit_bottom(STDBLOCK_hit_dis) &&  
			   it_redbullet->get_y() >= it_gray->get_hit_top   (STDBLOCK_hit_dis)){
				if_shoot = 1;
				it_gray = gray_block.erase(it_gray);
				break;
			}
			else{
				++it_gray;
	
			}
		}

		if(if_shoot){
			it_redbullet = red_bullet.erase(it_redbullet);

		}
		else{
			++it_redbullet;
		}
	}
	
}

void JS_redbullet_bigblock(){
	bool if_shoot = 0;
	for(it_redbullet = red_bullet.begin();it_redbullet != red_bullet.end();){
		if_shoot = 0;

		for(it_big = big_block.begin();it_big != big_block.end();it_big++){
			if(it_redbullet->get_x() >= it_big->get_hit_left  (STDBLOCK_hit_dis) &&  
			   it_redbullet->get_x() <= it_big->get_hit_right (STDBLOCK_hit_dis) &&  
		       it_redbullet->get_y() <= it_big->get_hit_bottom(STDBLOCK_hit_dis) &&  
			   it_redbullet->get_y() >= it_big->get_hit_top   (STDBLOCK_hit_dis)){
				if_shoot = 1;
				break;
			}
		}

		if(if_shoot){
			it_redbullet = red_bullet.erase(it_redbullet);
 
		}
		else{
			++it_redbullet;
		}
	}
}

void JS_bluebullet_enemy(){
	bool if_shoot = 0;
	for(it_bluebullet = blue_bullet.begin();it_bluebullet != blue_bullet.end();){
		if_shoot = 0;
		
		for(it_enemy = enemytank.begin();it_enemy != enemytank.end();){

			if(get_distance(it_bluebullet->get_x(),it_bluebullet->get_y(),it_enemy->get_x(),it_enemy->get_y()) <=  55 &&
				it_bluebullet->whose == STDBULLET_me){
				if_shoot = 1;
				it_enemy->be_attacked((int)(  (float)(1.0 + (me.if_redbuff() ?  0.5 : 0.0) )  *  (float) (it_bluebullet->get_power()) ) );
				if(!it_enemy->if_alive()){
					it_enemy = enemytank.erase(it_enemy);
					if(it_bluebullet->whose == STDBULLET_me)me.destroy_tank();
				}
				break;
			}
			else ++it_enemy;
		}
		if(if_shoot){
			it_bluebullet = blue_bullet.erase(it_bluebullet);

		}
		else{
			++it_bluebullet;
		}
	}

}

void JS_redbullet_enemy(){
	bool if_shoot = 0;
	for(it_redbullet = red_bullet.begin();it_redbullet != red_bullet.end();){
		if_shoot = 0;
		
		for(it_enemy = enemytank.begin();it_enemy != enemytank.end();){

			if(get_distance(it_redbullet->get_x(),it_redbullet->get_y(),it_enemy->get_x(),it_enemy->get_y()) <=  55 &&
				it_redbullet->whose == STDBULLET_me){
				if_shoot = 1;
				it_enemy->be_attacked((int)(  (float)(1.0 + (me.if_redbuff() ?  0.5 : 0.0) )  *  (float) (it_redbullet->get_power()) ) );
				if(!it_enemy->if_alive()){
					it_enemy = enemytank.erase(it_enemy);
					if(it_redbullet->whose == STDBULLET_me)me.destroy_tank();
				}
				break;
			}
			else ++it_enemy;

		}
		if(if_shoot){
			it_redbullet = red_bullet.erase(it_redbullet);

		}
		else{
			++it_redbullet;
		}
	}
}

void JS_bluebullet_me(){
	bool if_shoot = 0;
	for(it_bluebullet = blue_bullet.begin();it_bluebullet != blue_bullet.end();){
		if(get_distance(it_bluebullet->get_x(),it_bluebullet->get_y(),me.get_x(),me.get_y()) <= 55 && 
			(it_bluebullet->whose != STDBULLET_me)){//shoot
			it_bluebullet = blue_bullet.erase(it_bluebullet);
			me.be_attacked(it_bluebullet->get_power());
		}
		else{
			++it_bluebullet;
		}
	}
}

void JS_redbullet_me(){
	bool if_shoot = 0;
	for(it_redbullet = red_bullet.begin();it_redbullet != red_bullet.end();){
		if(get_distance(it_redbullet->get_x(),it_redbullet->get_y(),me.get_x(),me.get_y()) <= 55 && 
			(it_redbullet->whose != STDBULLET_me)){//shoot
			it_redbullet = red_bullet.erase(it_redbullet);
			me.be_attacked(it_redbullet->get_power());
		}
		else{
			++it_redbullet;
		}
	}
}

void JS_bluebullet_myBase(){
	bool if_shoot = 0;
	for(it_bluebullet = blue_bullet.begin();it_bluebullet != blue_bullet.end();){
		if(get_distance(it_bluebullet->get_x(),it_bluebullet->get_y(),myBase.get_x(),myBase.get_y()) <= 55){//shoot
			it_bluebullet = blue_bullet.erase(it_bluebullet);
			myBase.be_attacked(it_bluebullet->get_power());
		}
		else{
			++it_bluebullet;
		}
	}
}

void JS_redbullet_myBase(){
	bool if_shoot = 0;
	for(it_redbullet = red_bullet.begin();it_redbullet != red_bullet.end();){
		if(get_distance(it_redbullet->get_x(),it_redbullet->get_y(),myBase.get_x(),myBase.get_y()) <= 55){//shoot
			it_redbullet = red_bullet.erase(it_redbullet);
			myBase.be_attacked(it_redbullet->get_power());
		}
		else{
			++it_redbullet;
		}
	}
}

void JS_bluebullet_enemyBase(){
	bool if_shoot = 0;
	for(it_bluebullet = blue_bullet.begin();it_bluebullet != blue_bullet.end();){
		if(get_distance(it_bluebullet->get_x(),it_bluebullet->get_y(),enemyBase.get_x(),enemyBase.get_y()) <= 55){//shoot
			it_bluebullet = blue_bullet.erase(it_bluebullet);
			enemyBase.be_attacked(it_bluebullet->get_power());
		}
		else{
			++it_bluebullet;
		}
	}
}

void JS_redbullet_enemyBase(){
	bool if_shoot = 0;
	for(it_redbullet = red_bullet.begin();it_redbullet != red_bullet.end();){
		if(get_distance(it_redbullet->get_x(),it_redbullet->get_y(),enemyBase.get_x(),enemyBase.get_y()) <= 55){//shoot
			it_redbullet = red_bullet.erase(it_redbullet);
			enemyBase.be_attacked(it_redbullet->get_power());
		}
		else{
			++it_redbullet;
		}
	}
}

void JS_bluebullet_tower(){
	bool if_shoot = 0;
	for(it_bluebullet = blue_bullet.begin();it_bluebullet != blue_bullet.end();){
		if_shoot = 0;
		for(it_tower = tower.begin();it_tower != tower.end();){ 
			if(get_distance(it_bluebullet->get_x(),it_bluebullet->get_y(),it_tower->get_x(),it_tower->get_y()) <= 55){
				if(it_bluebullet->whose == STDBULLET_me && (!it_tower->who())){
					if_shoot = 1;
					it_tower->be_attacked(it_bluebullet->get_power());
				}
				if(it_bluebullet->whose == STDBULLET_enemy && it_tower->who()){
					if_shoot = 1;
					it_tower->be_attacked(it_bluebullet->get_power());
				}
					
			}
			if(!it_tower->if_alive()) {
				if(!it_tower->who()) {
					int buff_id = count % 3 + 1;
					BUFF aBuff(it_tower->get_x(),it_tower->get_y(),buff_id);
					buff.push_back(aBuff);
					if(it_tower->get_x() == STDTOWER_buff_Ax && it_tower->get_y() == STDTOWER_buff_Ay)create_bufftower_timA = count;
					if(it_tower->get_x() == STDTOWER_buff_Bx && it_tower->get_y() == STDTOWER_buff_By)create_bufftower_timB = count;
					if(it_tower->get_x() == STDTOWER_buff_Cx && it_tower->get_y() == STDTOWER_buff_Cy)create_bufftower_timC = count;
					if(it_tower->get_x() == STDTOWER_buff_Dx && it_tower->get_y() == STDTOWER_buff_Dy)create_bufftower_timD = count;
				}
				it_tower = tower.erase(it_tower); 
				if(it_bluebullet->whose == STDBULLET_me)me.destroy_tower();
				break;
			}
			else ++it_tower;
		}
		if(if_shoot)it_bluebullet = blue_bullet.erase(it_bluebullet);
		else ++it_bluebullet;
	}
}

void JS_redbullet_tower(){
	bool if_shoot = 0;
	for(it_redbullet = red_bullet.begin();it_redbullet != red_bullet.end();){
		if_shoot = 0;
		for(it_tower = tower.begin();it_tower != tower.end();){ 
			if(get_distance(it_redbullet->get_x(),it_redbullet->get_y(),it_tower->get_x(),it_tower->get_y()) <= 55){
				if(it_redbullet->whose == STDBULLET_me && (!it_tower->who())){
					if_shoot = 1;
					it_tower->be_attacked(it_redbullet->get_power());
				}
				if(it_redbullet->whose == STDBULLET_enemy && it_tower->who()){
					if_shoot = 1;
					it_tower->be_attacked(it_redbullet->get_power());
				}
					  
			}
			if(!it_tower->if_alive()) {
				if(!it_tower->who()) {                      
					int buff_id = count % 3 + 1;
					BUFF aBuff(it_tower->get_x(),it_tower->get_y(),buff_id);
					buff.push_back(aBuff);
					if(it_tower->get_x() == STDTOWER_buff_Ax && it_tower->get_y() == STDTOWER_buff_Ay)create_bufftower_timA = count;
					if(it_tower->get_x() == STDTOWER_buff_Bx && it_tower->get_y() == STDTOWER_buff_By)create_bufftower_timB = count;
					if(it_tower->get_x() == STDTOWER_buff_Cx && it_tower->get_y() == STDTOWER_buff_Cy)create_bufftower_timC = count;
					if(it_tower->get_x() == STDTOWER_buff_Dx && it_tower->get_y() == STDTOWER_buff_Dy)create_bufftower_timD = count;
				}
				it_tower = tower.erase(it_tower); 
				if(it_redbullet->whose == STDBULLET_me)me.destroy_tower();
				break;
			}
			else ++it_tower;
		}
		if(if_shoot)it_redbullet = red_bullet.erase(it_redbullet);
		else ++it_redbullet;
	}
}

/***************************************************************************************************************************************/
void judge_shoot(){
	JS_bluebullet_yellowblock();
	JS_bluebullet_grayblock();
	JS_bluebullet_bigblock();
	JS_bluebullet_me();
	JS_bluebullet_enemy();
	JS_bluebullet_enemyBase();
	JS_bluebullet_myBase();
	JS_bluebullet_tower();

	JS_redbullet_yellowblock();
	JS_redbullet_grayblock();
	JS_redbullet_bigblock();
	JS_redbullet_me();
	JS_redbullet_enemy();
	JS_redbullet_myBase();
	JS_redbullet_enemyBase();
	JS_redbullet_tower();
}

void me_get_input(){
    	me.buff_fade_load();
		int x_move = 0, y_move = 0;
		float new_rotate = 0.0;
		x_move = 2*(KEY_DOWN('D') - KEY_DOWN('A'));
		y_move = 2*(KEY_DOWN('S') - KEY_DOWN('W'));
		new_rotate = (float)( KEY_DOWN('O') - KEY_DOWN('I') ) * 0.2;
		if(KEY_DOWN('U') && me.load >= (int)(30.0 - ((me.if_bluebuff() ? 10.0 : 0.0)))) {me_Fire_A(); me.load = 0;}
		if(KEY_DOWN('J') && me.load >= (int)(30.0 - ((me.if_bluebuff() ? 10.0 : 0.0)))) {me_Fire_B(); me.load = 0;}
		if(KEY_DOWN('H') && me.load >= (int)(30.0 - ((me.if_bluebuff() ? 10.0 : 0.0)))) {me_Fire_R(); me.load = 0;}

		/************** move and judge **********/
		me_judge_move(x_move,y_move);
		me.rotate(new_rotate);
	
}
void judge_bullet_dis(){
		for(it_bluebullet = blue_bullet.begin(); it_bluebullet != blue_bullet.end();){
            if(it_bluebullet->get_count() >= it_bluebullet->get_maxdis())
            {
                it_bluebullet = blue_bullet.erase(it_bluebullet);
            }
            else
            {
                
				it_bluebullet->move();
				++it_bluebullet;
            }
        }
		/*****************************red************************************/
		for(it_redbullet = red_bullet.begin(); it_redbullet != red_bullet.end();){
            if(it_redbullet->get_count() >= it_redbullet->get_maxdis())
            {
                it_redbullet = red_bullet.erase(it_redbullet);
            }
            else
            {
                
				it_redbullet->move();
				++it_redbullet;
            }
        }
}
int screen_x = 0; int screen_y = 0;
void show(){
	SetWorkingImage(&buffer);// 先在缓冲区绘图
		
		cleardevice(); //clear
		
		//for(it_enemy = enemytank.begin();it_enemy != enemytank.end();it_enemy ++){
		//	it_enemy->show();
		//}
		//Enemy.show(); 
		for(it_floor = floor1.begin();it_floor != floor1.end();it_floor++){
			it_floor->show();
		}
me.show();
		myBase.show();
		enemyBase.show();
		for(it_enemy = enemytank.begin();it_enemy != enemytank.end();it_enemy++){
			it_enemy->show();
		}
		for(it_yellow = yellow_block.begin();it_yellow != yellow_block.end();it_yellow++){
			it_yellow->show();
		}
		for(it_gray = gray_block.begin();it_gray != gray_block.end();it_gray++){
			it_gray->show();
		}
		for(it_big = big_block.begin();it_big != big_block.end();it_big++){
			it_big->show();
		}
		for(it_river = river.begin();it_river != river.end();it_river++){
			it_river->show();
		}
		for(it_bluebullet = blue_bullet.begin();it_bluebullet != blue_bullet.end();it_bluebullet++){
			it_bluebullet->show();
		}
		for(it_redbullet = red_bullet.begin();it_redbullet != red_bullet.end();it_redbullet++){
			it_redbullet->show();
		}
		for(it_grass = grass.begin();it_grass != grass.end();it_grass++){
			it_grass->show();
		}
		for(it_tower = tower.begin();it_tower != tower.end();it_tower++){
			it_tower->show();
		}
		for(it_buff = buff.begin();it_buff != buff.end();it_buff++){
			it_buff->show();
		}
    /*putimage(0,0,&background);
    putpicture(playerx,playery,player);                 // 显示防空车
    vector<PLAYERMISL>::iterator it1;
    vector<PLANE>::iterator it2;
    vector<BOMB>::iterator it3;
    for(it1=misl.begin(); it1!=misl.end(); it1++)
    {
        putpicture(it1->x,it1->y,missile);    // 显示防空导弹
    }
    for(it2=plane.begin(); it2!=plane.end(); it2++)
    {
        putpicture(it2->x,it2->y,planes[it2->type]);    // 显示飞机
    }
    for(it3=bomb.begin(); it3!=bomb.end(); it3++)
    {
        putpicture(it3->x,it3->y,planebomb);    // 显示炸弹
    }
    sprintf(info,"生命值：%d 得分：%d",strength,score);
    outtextxy(0,0,info);   */   // 显示游戏数据

		screen_x +=   2 * (KEY_DOWN('E') - KEY_DOWN('Q'));


		SetWorkingImage();
		putimage(-me.get_x() + 762 ,-me.get_y() + 400,&buffer);   // 把缓冲区绘图内容一次性绘制上去，这样能消除闪烁
}

int enemy_load = 0; 
void debug(){
		enemy_load++;
		
		if(KEY_DOWN('B'))create_yellow_block(20,Screen_width-20,20,Screen_high-20);
		if(KEY_DOWN('V'))create_gray_block  (20,Screen_width-20,20,Screen_high-20);
		//if(KEY_DOWN('K'))create_big_block  (20,Screen_width-20,20,Screen_high-20);/////////buzhidao
		if(KEY_DOWN('C') && enemy_load >= 90) {
			ENEMYTANK aEnemy(300,300,RED,STDENEMYTANK_id_AKme,STDENEMYTANK_state_AKme);
			enemytank.push_back(aEnemy);
			enemy_load = 0;
		}
		if(KEY_DOWN('G')){
			for(it_enemy = enemytank.begin();it_enemy != enemytank.end();it_enemy++){
				it_enemy->attack(me.get_x(),me.get_y());
				
			}
			enemy_Fire_R(me.get_x(),me.get_y());
		}
		else{
			for(it_enemy = enemytank.begin();it_enemy != enemytank.end();it_enemy++){
				it_enemy->set_move(0,0);
			}
		}
		
}


/******************count and load********/


void creat(){//定时创建函数
		//更新巡逻坦克
	if(count % 30  == 0 && count_5ms == 1){
		bool A_patrol = 1, B_patrol = 1,C_patrol = 1;
		for(it_enemy = enemytank.begin();it_enemy != enemytank.end();it_enemy++){
            if(it_enemy->get_id() == STDENEMYTANK_id_patrolA){ A_patrol = 0;}
			if(it_enemy->get_id() == STDENEMYTANK_id_patrolB){ B_patrol = 0;}
			if(it_enemy->get_id() == STDENEMYTANK_id_patrolC){ C_patrol = 0;}
            
		}
		if(A_patrol){
			ENEMYTANK PatrolA(STDENEMYTANK_patrolA_x1,STDENEMYTANK_patrolA_y1,WHITE,STDENEMYTANK_id_patrolA,STDENEMYTANK_state_patrolA);
            enemytank.push_back(PatrolA);
		}
		if(B_patrol){
			ENEMYTANK PatrolB(STDENEMYTANK_patrolB_x1,STDENEMYTANK_patrolB_y1,WHITE,STDENEMYTANK_id_patrolB,STDENEMYTANK_state_patrolB);
			enemytank.push_back(PatrolB);
		}
		if(C_patrol){
			ENEMYTANK PatrolC(STDENEMYTANK_patrolC_x1,STDENEMYTANK_patrolC_y1,WHITE,STDENEMYTANK_id_patrolC,STDENEMYTANK_state_patrolC);
			enemytank.push_back(PatrolC);
		}
	}

		////定时更新直攻基地坦克
	
	if(count % 30  == 0 && count_5ms == 1){
		
		ENEMYTANK BASE_ATTACKER_A(600,600,WHITE,STDENEMYTANK_id_AKbase,STDNEMEYTANK_state_AKbase);
        enemytank.push_back(BASE_ATTACKER_A);

		ENEMYTANK BASE_ATTACKER_B(2600,2600,WHITE,STDENEMYTANK_id_AKbase,STDNEMEYTANK_state_AKbase);
		enemytank.push_back(BASE_ATTACKER_B);

		ENEMYTANK BASE_ATTACKER_C(1800,1400,WHITE,STDENEMYTANK_id_AKbase,STDNEMEYTANK_state_AKbase);
		enemytank.push_back(BASE_ATTACKER_C);
}

		////定时更新攻击我的坦克

	if(count % 30 == 0 && count_5ms == 1){
		
		ENEMYTANK BASE_ATTACKER_A(2200,600,WHITE,STDENEMYTANK_id_AKme,STDENEMYTANK_state_AKme);
        enemytank.push_back(BASE_ATTACKER_A);

		ENEMYTANK BASE_ATTACKER_B(2200,1000,WHITE,STDENEMYTANK_id_AKme,STDENEMYTANK_state_AKme);
		enemytank.push_back(BASE_ATTACKER_B);

		ENEMYTANK BASE_ATTACKER_C(2600,1000,WHITE,STDENEMYTANK_id_AKme,STDENEMYTANK_state_AKme);
		enemytank.push_back(BASE_ATTACKER_C);
}

	//更新bufftowerA
	//buffTowerA
	if((count - create_bufftower_timA) == 30 && count_5ms == 1){
		bool A_buffTower = 1;
		for(it_tower = tower.begin();it_tower != tower.end();it_tower++){
			if((!it_tower->who()) && (it_tower->get_x() == STDTOWER_buff_Ax) && (it_tower->get_y() == STDTOWER_buff_Ay ))
				A_buffTower = 0;
		}
		if(A_buffTower){
			TOWER buffTowerA(STDTOWER_buff_Ax,STDTOWER_buff_Ay,STDTOWER_enemy);
			tower.push_back(buffTowerA);
		}
	}
	//buffTowerB
	if((count - create_bufftower_timB) == 30 && count_5ms == 2){
		bool B_buffTower = 1;
		for(it_tower = tower.begin();it_tower != tower.end();it_tower++){
			if((!it_tower->who()) && (it_tower->get_x() == STDTOWER_buff_Bx) && (it_tower->get_y() == STDTOWER_buff_By ))
				B_buffTower = 0;
		}
		if(B_buffTower){
			TOWER buffTowerB(STDTOWER_buff_Bx,STDTOWER_buff_By,STDTOWER_enemy);
			tower.push_back(buffTowerB);
		}
	}
	//buffTowerC
	if((count - create_bufftower_timC) == 30 && count_5ms == 3){
		bool C_buffTower = 1;
		for(it_tower = tower.begin();it_tower != tower.end();it_tower++){
			if((!it_tower->who()) && (it_tower->get_x() == STDTOWER_buff_Cx) && (it_tower->get_y() == STDTOWER_buff_Cy ))
				C_buffTower = 0;
		}
		if(C_buffTower){
			TOWER buffTowerC(STDTOWER_buff_Cx,STDTOWER_buff_Cy,STDTOWER_enemy);
			tower.push_back(buffTowerC);
		}
	}
	//buffTowerD
	if((count - create_bufftower_timD) == 30 && count_5ms == 4){
		bool D_buffTower = 1;
		for(it_tower = tower.begin();it_tower != tower.end();it_tower++){
			if((!it_tower->who()) && (it_tower->get_x() == STDTOWER_buff_Dx) && (it_tower->get_y() == STDTOWER_buff_Dy ))
				D_buffTower = 0;
		}
		if(D_buffTower){
			TOWER buffTowerD(STDTOWER_buff_Dx,STDTOWER_buff_Dy,STDTOWER_enemy);
			tower.push_back(buffTowerD);
		}
	}
    //

}



void enemy_decision(){ //enemytank决策函数
/*******************************解算出每个敌方坦克的state********************************************************/
	for(it_enemy = enemytank.begin();it_enemy != enemytank.end();it_enemy++){
		//patrolA
		if(it_enemy->get_id() == STDENEMYTANK_id_patrolA){
			if(get_distance(it_enemy->get_x(),it_enemy->get_y(),me.get_x(),me.get_y()) <= 200){     ///如果和我的距离小于200，转为攻击我模式，否则巡逻模式
				it_enemy->set_state(STDENEMYTANK_state_AKme);
			}
			else{
				it_enemy->set_state(STDENEMYTANK_state_patrolA);
			}
		}
		//patrolB
		if(it_enemy->get_id() == STDENEMYTANK_id_patrolB){
			if(get_distance(it_enemy->get_x(),it_enemy->get_y(),me.get_x(),me.get_y()) <= 200){		///如果和我的距离小于200，转为攻击我模式，否则巡逻模式
				it_enemy->set_state(STDENEMYTANK_state_AKme);
			}
			else{
				it_enemy->set_state(STDENEMYTANK_state_patrolB);
			}
		}
		//patrolC
		if(it_enemy->get_id() == STDENEMYTANK_id_patrolC){
			if(get_distance(it_enemy->get_x(),it_enemy->get_y(),me.get_x(),me.get_y()) <= 200){		///如果和我的距离小于200，转为攻击我模式，否则巡逻模式
				it_enemy->set_state(STDENEMYTANK_state_AKme);	
			}
			else{
				it_enemy->set_state(STDENEMYTANK_state_patrolC);
			}
		}
		//AKbase
		if(it_enemy->get_id() == STDENEMYTANK_id_AKbase){
			if(get_distance(it_enemy->get_x(),it_enemy->get_y(),me.get_x(),me.get_y()) <= 200){		///如果和我的距离小于200，转为攻击我模式，否则直攻基地
				it_enemy->set_state(STDENEMYTANK_state_AKme);
			}
			else{
				it_enemy->set_state(STDNEMEYTANK_state_AKbase);
			}
		}
		//AKme
		if(it_enemy->get_id() == STDENEMYTANK_id_AKme){
			if(get_distance(it_enemy->get_x(),it_enemy->get_y(),me.get_x(),me.get_y()) <= 200){		///无论和我的距离是否小于200，均为攻击我模式
				it_enemy->set_state(STDENEMYTANK_state_AKme);
			}
			else{
				it_enemy->set_state(STDENEMYTANK_state_AKme);
			}
		}
	}
/**************************根据state和目前坦克的位置做出决策******************************************/
	for(it_enemy = enemytank.begin();it_enemy != enemytank.end();it_enemy++){
		//攻击我的模式
		if(it_enemy->get_state() == STDENEMYTANK_state_AKme){
			it_enemy->attack(me.get_x(),me.get_y());
			it_enemy->load ++;
			if(it_enemy->load >= 30 && 
				get_distance(me.get_x(),me.get_y(),it_enemy->get_x(),it_enemy->get_y()) <= 300){
				BULLET newBullet(it_enemy->get_fire_x(),it_enemy->get_fire_y(),it_enemy->get_fire_theta(),RED,STDBULLET_enemy);
				red_bullet.push_back(newBullet);
				it_enemy->load = 0;
			}
		}
		//攻击基地的模式
		if(it_enemy->get_state() == STDNEMEYTANK_state_AKbase){
            it_enemy->load++;
			if(get_distance(it_enemy->get_x(),it_enemy->get_y(),myBase.get_x(),myBase.get_y()) <= 200 && it_enemy->load >= 30){
				
				it_enemy->attack(myBase.get_x(),myBase.get_y());
					BULLET newBullet(it_enemy->get_fire_x(),it_enemy->get_fire_y(),it_enemy->get_fire_theta(),RED,STDBULLET_enemy);
					red_bullet.push_back(newBullet);
					it_enemy->load = 0;	

			}
			else{
				bool if_attack = 0;
				for(it_tower = tower.begin();it_tower != tower.end();it_tower++){
					if(get_distance(it_enemy->get_x(),it_enemy->get_y(),it_tower->get_x(),it_tower->get_y()) <= 300 && (it_tower->who())){
						if_attack = 1;
						if(it_enemy->load >= 30){
							it_enemy->attack(it_tower->get_x(),it_tower->get_y());
							BULLET newBullet(it_enemy->get_fire_x(),it_enemy->get_fire_y(),it_enemy->get_fire_theta(),RED,STDBULLET_enemy);
							red_bullet.push_back(newBullet);
							it_enemy->load = 0;	
						}
					}
				}

				if(!if_attack){
					it_enemy->set_aim(myBase.get_x(),myBase.get_y());
					it_enemy->moveto_aim();
				}

			}

		}
		//巡逻模式
		if(it_enemy->get_state() == STDENEMYTANK_state_patrolA){
			if(it_enemy->if_patrolA()){//在巡逻线上
				if(it_enemy->get_x() == STDENEMYTANK_patrolA_x1 && it_enemy->get_y() == STDENEMYTANK_patrolA_y1){//在巡逻1点，则把目标设为巡逻2点
					it_enemy->set_aim(STDENEMYTANK_patrolA_x2,STDENEMYTANK_patrolA_y2);
				}
				if(it_enemy->get_x() == STDENEMYTANK_patrolA_x2 && it_enemy->get_y() == STDENEMYTANK_patrolA_y2){
					it_enemy->set_aim(STDENEMYTANK_patrolA_x1,STDENEMYTANK_patrolA_y1);
				}
			}
			else{                     //不在巡逻线上
				it_enemy->set_aim(STDENEMYTANK_patrolA_x1,STDENEMYTANK_patrolA_y1);
			}
			it_enemy->moveto_aim();
		}
		
		if(it_enemy->get_state() == STDENEMYTANK_state_patrolB){
			if(it_enemy->if_patrolB()){//在巡逻线上
				if(it_enemy->get_x() == STDENEMYTANK_patrolB_x1 && it_enemy->get_y() == STDENEMYTANK_patrolB_y1){//在巡逻1点，则把目标设为巡逻2点
					it_enemy->set_aim(STDENEMYTANK_patrolB_x2,STDENEMYTANK_patrolB_y2);
				}
				if(it_enemy->get_x() == STDENEMYTANK_patrolB_x2 && it_enemy->get_y() == STDENEMYTANK_patrolB_y2){
					it_enemy->set_aim(STDENEMYTANK_patrolB_x1,STDENEMYTANK_patrolB_y1);
				}

			}
			else{  //不在巡逻线上
				it_enemy->set_aim(STDENEMYTANK_patrolB_x2,STDENEMYTANK_patrolB_y2);
			}
			it_enemy->moveto_aim();
		}

		if(it_enemy->get_state() == STDENEMYTANK_state_patrolC){
			if(it_enemy->if_patrolC()){//在巡逻线上
				if(it_enemy->get_x() == STDENEMYTANK_patrolC_x1 && it_enemy->get_y() == STDENEMYTANK_patrolC_y1){//在巡逻1点，则把目标设为巡逻2点
					it_enemy->set_aim(STDENEMYTANK_patrolC_x2,STDENEMYTANK_patrolC_y2);
				}
				if(it_enemy->get_x() == STDENEMYTANK_patrolC_x2 && it_enemy->get_y() == STDENEMYTANK_patrolC_y2){
					it_enemy->set_aim(STDENEMYTANK_patrolC_x1,STDENEMYTANK_patrolC_y1);
				}
			}
			else{                     //不在巡逻线上
				it_enemy->set_aim(STDENEMYTANK_patrolC_x1,STDENEMYTANK_patrolC_y1);
			}
			it_enemy->moveto_aim();
		}
	}
	move_judge_enemy();
}

