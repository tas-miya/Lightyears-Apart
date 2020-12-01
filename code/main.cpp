#include <iostream>
#include <list>
#include<string>
#include<SDL_mixer.h>
#include "SDL.h"
#include "sprite.hpp"
#include "player_spaceship.hpp"
#include "alien.hpp"
#include "alienTypes.hpp"
#include "Laser.hpp"
#include "obstacle.hpp"
#include "obstacleTypes.hpp"
#include "LinkedList.hpp"
#include "game.hpp"

int main(int argc, char *argv[]){
    Game game;
    srand(time(NULL));
    if( !game.init() ){
		printf( "Failed to initialize!\n" );
        return 0;
	}
		//Load media
    if( !game.loadMedia() ){
        printf( "Failed to load media!\n" );
        return 0;
    }

    game.run();
    game.close();

    return 0;
}