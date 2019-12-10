/************BASE class**********
by jieyr
*********************************/
#ifndef BASE_H
#define BASE_H
#include "graphics.h"
#define STDBASE_me 1
#define STDBASE_enemy 0
#define STDBASE_health 10000
#define STDBASE_HealthLen 100
#define STDBASE_HealthHig 20
#define STDBASE_HealthPos -40

class BASE{
	protected:
		int health;
		int x_pos;
		int y_pos;
		bool id;
	public:
		BASE(int newX,int newY,bool newId);
		BASE();
		~BASE();
		bool whos();
		void show();
		void be_attacked(int power);
		int get_x(){return x_pos;}
		int get_y(){return y_pos;}
		int get_health(){return health;}
};
#endif