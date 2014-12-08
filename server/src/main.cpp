#include <iostream>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
#include <cstring>

#define DEFAULT_WINDOW_WIDTH 640
#define DEFAULT_WINDOW_HEIGHT 480

using namespace std;

SDL_Window *window;
SDL_Renderer *renderer;


TCPsocket server;
TCPsocket client;

void initSDL()
{
	// Initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	SDLNet_Init();
	
	window = SDL_CreateWindow("Game Window", 
															SDL_WINDOWPOS_UNDEFINED,
															SDL_WINDOWPOS_UNDEFINED,
															DEFAULT_WINDOW_WIDTH,
															DEFAULT_WINDOW_HEIGHT,
															0
														);
	
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	// Redirect output to log files
	FILE * my_stdout = freopen ("../logs/log.txt", "wt" /*or "wt"*/, stdout);
	//FILE * my_stderr = freopen ("log.txt", "wb" /*or "wt"*/, stderr);
	
	cout << "SDL Initialized..." << endl;
}

void listen()
{
	
	IPaddress ip;
	SDLNet_ResolveHost(&ip,  NULL, 7777);  // NULL used when its a server.  Last parameter is the port number
	
	server = SDLNet_TCP_Open(&ip);

	const char * text = "Hello Client!\n";
	while(1)
	{
		client = SDLNet_TCP_Accept(server);
		// if client is not null
		if(client)
		{
			cout << "Client connected" << endl;
			//SDLNet_TCP_Send(client,  text, strlen(text) + 1);
			SDLNet_TCP_Close(client);
			break;
		}
	}
	
}

void closeSDL()
{
	SDLNet_TCP_Close(server);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	
	SDLNet_Quit();
	SDL_Quit();
	
	cout << "SDL closed and quitted" << endl;
}


int main(int argc, char** argv)
{
	initSDL();
	listen();
	
	closeSDL();
	return 0;
}













