#include "core.h"

// SDL Event variable
SDL_Event e;


int getInput()
{
	if(SDL_PollEvent(&e))
	{
		switch(e.type)
		{
			case SDL_QUIT:
				return -1;
			case SDL_KEYDOWN:
				switch(e.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						return -1;
					case SDLK_LEFT:
						return 2;
						//player.x -= 10;
						//break;
					case SDLK_RIGHT:
						return 3;
						//player.x += 10;
						//break;
					case SDLK_UP:
						//player.y -= 10;
						break;
					case SDLK_DOWN:
						//player.y += 10;
						break;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				if(e.button.button == SDL_BUTTON_LEFT)
				{
					//movePlayerXY(e.button.x, e.button.y);
					//player.x = e.button.x - (player.w >> 1);
					//player.y = e.button.y - (player.h >> 1);
				}
				if(e.button.button == SDL_BUTTON_RIGHT)
				{
					
				}
				break;
		}
	}
	return 0;
}