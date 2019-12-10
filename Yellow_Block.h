/********YELLOW_BLOCK class********
by jieyr
***********************************/
#ifndef YELLOW_BLOCK_H
#define YELLOW_BLOCK_H
#include "Block.h"
#include "graphics.h"

#define STDYELLOW_BLOCK_health 100

class YELLOW_BLOCK:public BLOCK{
	protected:
		int health;
	public:
		YELLOW_BLOCK(int newX,int newY);
		YELLOW_BLOCK();
		~YELLOW_BLOCK();
		void show();
		void hide();
};
#endif

