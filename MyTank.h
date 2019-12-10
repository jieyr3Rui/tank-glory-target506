/*********************MYPLANE CLASS*********
by:jieyr
*******************************************/
#ifndef MYTANK_H
#define MYTANK_H

#include "Tank.h"
#include "Bullet.h"
#include "Yellow_Block.h"
#include "Gray_Block.h"
#include "Big_Block.h"
#include "River.h"
#include "Buff.h"

#define STDMYTANK_health 5000
#define STDMYTANK_money 0
#define STDMYTANK_range 1
#define STDMYTANK_experience 0
#define STDMYTANK_alive 1
#define STDMYTANK_death 0
#define STDMYTANK_HealthLen 80
#define STDMYTANK_HealthHig 20
#define STDMYTANK_HealthPos -50
class MYTANK:public TANK{
	protected:
		bool alive;
		int health;
		int money;
		int experience;
		int score;
		int range;
		/*****buff******/
		int redbullet_Num;
		int bluebullet_Num;
		int redbuff_Tim;
		int bluebuff_Tim;
		
	public:
		MYTANK(int newX,int newY,COLORREF newColor);
		MYTANK();
		~MYTANK();
		int get_health(){return health;}
		int get_money(){return money;}
		int get_experience(){return experience;}
		int get_range(){return range;}
		int get_score(){return score;}
		void range_exp();
		void destroy_block();
		void destroy_tank();
		void destroy_tower();
		void be_attacked(int power);
		void die();
		void judge_move(YELLOW_BLOCK yellow);
		void judge_move(GRAY_BLOCK gray);
		void heal();
		void show();
		void show_state();
		void pick_buff(int buff_type);
		void buff_fade_load();
		void fire_aBullet(COLORREF bulletColor);
		bool if_redbuff(){return (redbuff_Tim > 0);}
		bool if_bluebuff(){return (bluebuff_Tim > 0);}
		bool if_redbullet(){return (redbullet_Num > 0);}
		bool if_bluebullet(){return (bluebullet_Num > 0);}
		int load;
		void blood_recovery(){health += (health <= 20000) * 100;} 
};
#endif