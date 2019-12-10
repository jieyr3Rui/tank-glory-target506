/********River class********
by hk
***********************************/
#ifndef RIVER_H
#define RIVER_H
#include "Block.h"
#include "graphics.h"


class RIVER:public BLOCK{
	protected:
		int health;

	public:
		RIVER(int newX,int newY,int width,int lenth);
		RIVER();
		~RIVER();
		void show();
		void hide();
};
#endif

