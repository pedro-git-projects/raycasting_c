#include <stdio.h>
#include <SDL2/SDL.h>
#include "constants.h"

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

// Global variables
int isGameRunning = FALSE;
int playerX, playerY;
int ticksLastFrame = 0; 


int initializeWindow()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		fprintf(stderr, "Error initializing SDL.\n");
		return FALSE;
	}
	window = SDL_CreateWindow(
		NULL,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		SDL_WINDOW_BORDERLESS);
	if (!window)
	{
		fprintf(stderr, "Error creating SDL window \n");
		return FALSE;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer)
	{
		fprintf(stderr, "Error creating SDL renderer \n");
		return FALSE;
	}
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	return TRUE;
}

void destroyWindow()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void processInput()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
	{
		isGameRunning = FALSE;
		break;
	}
	case SDL_KEYDOWN:
	{
		if (event.key.keysym.sym == SDLK_ESCAPE)
			isGameRunning = FALSE;
		break;
	}
	}
}

void setup()
{
	 playerX = 0;
	 playerY = 0;
}

void update() {
    // how long until we reach the target frame time in milliseconds
    int timeToWait = FRAME_TIME_LENGTH - (SDL_GetTicks() - ticksLastFrame);

    // delays execution when needed
    if (timeToWait > 0 && timeToWait <= FRAME_TIME_LENGTH) {
        SDL_Delay(timeToWait);
    }

    float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;

    // stores the milliseconds of the current frame to be used in the future
    ticksLastFrame = SDL_GetTicks();

    playerX += 50 * deltaTime;
    playerY += 50 * deltaTime;
}

void render()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
	SDL_Rect rect = { playerX, playerY, 20, 20 };
	SDL_RenderFillRect(renderer, &rect);

	SDL_RenderPresent(renderer);
}

int main()
{

	isGameRunning = initializeWindow();

	setup();
	// right now the framerate is dependant on the cpu speed
	// TODO: fix game loop with delta time
	while (isGameRunning)
	{
		processInput();
	    update();
		render();
	}

	destroyWindow();

	return 0;
}
