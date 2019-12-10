/********Grass class********
by huangjj
***********************************/
#ifndef GRASS_H
#define GRASS_H
#include "graphics.h"
#include "Block.h"
#define STDGRASS_pos 1
#define STDGRASS_width_2 15
class GRASS:public BLOCK{
	protected:
		int health;

	public:
		GRASS(int newX,int newY,int width,int lenth);
		GRASS();
		~GRASS();
		void show();
		void hide();
};
#endif