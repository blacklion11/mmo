#include "core.h"

#define DEFAULT_WINDOW_WIDTH 640
#define DEFAULT_WINDOW_HEIGHT 480

using namespace std;

SDL_Window *window;
SDL_Renderer *renderer;


IPaddress ip;
TCPsocket server;
TCPsocket listener;
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

void createServerSocket()
{
	SDLNet_ResolveHost(&ip,  NULL, 7777);   // IPaddress pointer for resolving, server IP address (NULL if this is a server), Port number
	
	server = SDLNet_TCP_Open(&ip);
}

void listen()
{
	listener = SDLNet_TCP_Accept(server);
	// if client is not null
	if(listener)
	{
		client = listener;
		listener = NULL;
	}
	
}

void run()
{
	//listen();
	
	//SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	
	bool running = true;
	while(running)
	{
		//Listen for client connections
		listen();
		
		//Listen for input from player
		int input = getInput();
		running = input != -1;
		
		if(input == 2)
		{
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		}
		
		if(client)
		{
			SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		}
		else
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}
		
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
		
	}
	
	
	
	
}

void closeConnections()
{
	SDLNet_TCP_Close(client);
	SDLNet_TCP_Close(listener);
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
	createServerSocket();
	run();
	
	closeConnections();
	closeSDL();
	return 0;
}













