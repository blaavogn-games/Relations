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
};
#endif
