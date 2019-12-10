/********BigBlock_BLOCK class********
by hk
***********************************/
#ifndef BIG_BLOCK_H
#define BIG_BLOCK_H
#include "Block.h"
#include "graphics.h"


#define BIG_STDBLOCK_hit_dis_x 10
#define BIG_STDBLOCK_hit_dis_y 10

#define BIG_STDBLOCK_move_dis_x 60
#define BIG_STDBLOCK_move_dis_y 60

#define STDYELLOW_BLOCK_health 100

class BIG_BLOCK:public BLOCK{
	protected:
		int health;

	public:
		BIG_BLOCK(int newX,int newY,int width,int lenth);
		BIG_BLOCK();
		~BIG_BLOCK();
		void show();
		void hide();
};
#endif

