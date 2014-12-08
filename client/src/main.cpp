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

void connectToServer()
{
	IPaddress ip;
	SDLNet_ResolveHost(&ip,  "127.0.0.1", 7777);  // NULL used when its a server.  Last parameter is the port number
	
	TCPsocket client = SDLNet_TCP_Open(&ip);
	char text[100];
	//SDLNet_TCP_Recv(client, text, 100);
	
	//cout << text;
	
	SDLNet_TCP_Close(client);
	
	SDLNet_Quit();
	SDL_Quit();

	cout << "SDL Quitted" << endl;
}

int main(int argc, char** argv)
{
	initSDL();
	connectToServer();
	

	return 0;
}