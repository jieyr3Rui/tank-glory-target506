/***************BUFF class**********

***********************************/

#ifndef BUFF_H
#define BUFF_H

#include "graphics.h"

#define STDBUFF_red 1
#define STDBUFF_blue 2
#define STDBUFF_redbullet 3
#define STDBUFF_bluebullet 4
#define STDBUFF_width 40
#define STDBUFF_pick 30

class BUFF{
	protected:
		int id;
		int x_pos;
		int y_pos;
		int left;
		int right;
		int top;
		int bottom;

	public:
		BUFF(int newX,int newY,int newId);
		BUFF(){}
		~BUFF(){}
		void show();
		bool judge_pick(int tankX,int tankY);
		int get_x(){return x_pos;}
		int get_y(){return y_pos;}
		int get_id(){return id;}
};
#endif