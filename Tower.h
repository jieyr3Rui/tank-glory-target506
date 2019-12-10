/*****************TOWER class*********
by jieyr
**************************************/
#ifndef TOWER_H
#define TOWER_H

#include "Tank.h"
#include "graphics.h"

#define STDTOWER_me           1
#define STDTOWER_enemy        0

#define STDTOWER_buff_Ax      1350
#define STDTOWER_buff_Ay      1000  
#define STDTOWER_buff_Bx      1000
#define STDTOWER_buff_By      1350
#define STDTOWER_buff_Cx      2200
#define STDTOWER_buff_Cy      1850
#define STDTOWER_buff_Dx      1850
#define STDTOWER_buff_Dy      2200

#define STDTOWER_load        30
#define STDTOWER_me_health     3000
#define STDTOWER_enemy_health   600
#define STDTOWER_HealthLen   80
#define STDTOWER_HealthHig   20
#define STDTOWER_HealthPos  -40
#define STDTOWER_effectiveRange 400

class TOWER:public TANK{
	protected:

		int health;
		bool id;
	public:
		TOWER(int newX,int newY,bool newId);
		TOWER();
		~TOWER();
		void be_attacked(int power);
		void show();
		int load;
		bool who(){return id;}
		bool if_alive(){return (health > 0);}

};
#endif