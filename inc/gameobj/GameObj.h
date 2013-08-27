#ifndef GAMEOBJ_H
#define GAMEOBJ_H
#include <SFML/Graphics.hpp>

class GameObj{
	private:

	protected:
		GameObj(){
			init();
		}
		void init();
		void update();
		void render();

    public:
        //Need to look up what virtual means, but apparently I am able to override it
        //Everything in this class should perhaps be virtual const
        virtual void alarmAction(int type);
};
#endif
