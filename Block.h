/********BLOCK class*****
by jieyr
************************/
#ifndef BLOCK_H
#define BLOCK_H
#include "graphics.h"

#define STDBLOCK_width_2 15
#define STDBLOCK_hit_dis 15
#define STDBLOCK_move_dis 30
#define STDBLOCK_pos 1
class BLOCK{
	protected:
		int x_pos;
		int y_pos;
		int left;
		int right;
		int top;
		int bottom;
		int width;
	public:
		BLOCK(int newX,int newY);
		BLOCK();
		~BLOCK();
		void show(); //show
		void hide(); //hide
		/********get hit function******/
		int get_hit_left  (int dis); //×²»÷Ê±×ó±ß±ß½çxÖá
		int get_hit_right (int dis); //
		int get_hit_top   (int dis); //
		int get_hit_bottom(int dis); //
};
#endif