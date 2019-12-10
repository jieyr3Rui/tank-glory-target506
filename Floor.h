/********Floor class********
by hk
***********************************/
#ifndef FLOOR_H
#define FLOOR_H
#include "Block.h"
#include "graphics.h"


#define BIG_STDBLOCK_hit_dis_x 10
#define BIG_STDBLOCK_hit_dis_y 10

#define BIG_STDBLOCK_move_dis_x 60
#define BIG_STDBLOCK_move_dis_y 60

#define STDYELLOW_BLOCK_health 100

class FLOOR:public BLOCK{
	protected:
		int health;

	public:
		FLOOR(int newX,int newY,int width,int lenth);
		FLOOR();
		~FLOOR();
		void show();
		void hide();
};
#endif