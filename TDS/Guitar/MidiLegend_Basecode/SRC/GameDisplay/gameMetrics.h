
#ifndef _GAME_METRICS_INCLUDED_
#define _GAME_METRICS_INCLUDED_

#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include "../GameModel/model.h"
#include "textures.h"

typedef struct Metrics_s
{
    SDL_Rect screen;
    SDL_Rect note;
    SDL_Rect background;
    SDL_Rect gameArea;
	SDL_Rect strum[MAX_STRINGS];
	SDL_Rect cords[MAX_STRINGS];
	SDL_Rect strumH[MAX_STRINGS];
	SDL_Rect score[10];
	SDL_Rect score_adv[10];
	SDL_Rect logo;
	SDL_Rect winner;
	SDL_Rect loser;
	SDL_Rect equal;
	
} Metrics;

Metrics * newMetrics(Textures * textures);
void freeMetrics(Metrics * metrics);

void initMetrics(Metrics *metrics, int nbStrings);

#endif
