/*************Gray_Block class*****
by jieyr
**********************************/
#ifndef GRAY_BLOCK_H
#define GRAY_BLOCK_H

#include "Block.h"
#include "graphics.h"

#define STDGRAY_BLOCK_health 200

class GRAY_BLOCK:public BLOCK{
	protected:
		int health;
	public:
		GRAY_BLOCK(int newX,int newY);
		GRAY_BLOCK();
		~GRAY_BLOCK();
		void show();
		void hide();
};
#endif