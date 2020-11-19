#include "game.hpp"
bool Game::init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "Lightyears Apart", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
				// if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				// {
				// 	printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
				// 	success = false;
				// }
			}
		}
	}

	return success;
}

bool Game::loadMedia()
{
	//Loading success flag
	bool success = true;
	
	assets = loadTexture("sprite.png");
    gTexture = loadTexture("stars.png");
	// gTexture = loadTexture("Welcome Screen.png");
	// gTexture = loadTexture("Instructions Screen.png");
	if(assets==NULL || gTexture == NULL)
    {
        printf("Unable to run due to error: %s\n",SDL_GetError());
        success =false;
    }
	// if(bgMusic == NULL){
	// 	printf("Unable to load music: %s \n", Mix_GetError());
	// 	success = false;
	// }
	return success;
}

void Game::close()
{
	texture.~BGTexture();
	//Free loaded images
	SDL_DestroyTexture(assets);
	assets=NULL;
	SDL_DestroyTexture(gTexture);
	
	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;
	// Mix_FreeMusic(bgMusic);
	// bgMusic = NULL;
	//Quit SDL subsystems
	IMG_Quit();
	Mix_Quit();
	SDL_Quit();
}

SDL_Texture* Game::loadTexture( std::string path )
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//storing dimensions of the bg
		texture.bgWidth = loadedSurface->w;
		texture.bgHeight = loadedSurface->h;

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}
	texture.assets = newTexture;
	return newTexture;
}
void Game::run( )
{
	bool quit = false;
	SDL_Event e;
	PlayerSpaceship p = {assets};
	while( !quit )
	{
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{
			//User requests quit
			if( e.type == SDL_QUIT )
			{
				quit = true;
			}
			p.EventHandler(e);	//handles ship events
		}
		p.moveShip();
		// if( Mix_PlayingMusic() == 0 )
		// {
		// 	//Play the music
		// 	Mix_PlayMusic( bgMusic, 2 );
		// }
		SDL_RenderClear(gRenderer); //removes everything from renderer
		
		texture.drawBG(gRenderer);	//moving background

		//***********************draw the objects here********************

		
		ThunderBearers t = {assets}; FireBreathers f = {assets}; StormCarriers s = {assets}; GeoYielders g = {assets};
		Meteor m = {assets}; Fireball fb = {assets};
		
		p.drawSprite(gRenderer);
		g.drawSprite(gRenderer);
		t.drawSprite(gRenderer);
		s.drawSprite(gRenderer);
		f.drawSprite(gRenderer);
		m.drawSprite(gRenderer);
		fb.drawSprite(gRenderer);
		//tb.drawSprite(gRenderer);
		//****************************************************************

    	SDL_RenderPresent(gRenderer); //displays the updated renderer

	    SDL_Delay(200);	//causes sdl engine to delay for specified miliseconds
	}
			
}
