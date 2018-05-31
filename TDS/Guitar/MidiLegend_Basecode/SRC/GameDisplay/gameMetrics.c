#ifdef _WIN32
	#include <SDL.h>
#else
	#include <SDL2/SDL.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gameMetrics.h"
#include "../tools.h"


Metrics * newMetrics(Textures * textures)
{
    Metrics * metrics = NULL;
	
    int w, h,i;

    if (!textures)
        return NULL;

    metrics = (Metrics *)calloc(1, sizeof(Metrics));
    if (!metrics)
        return NULL;

    metrics->screen.x = 0;
    metrics->screen.y = 0;
    metrics->screen.w = WINDOW_WIDTH;
    metrics->screen.h = WINDOW_HEIGHT;    
	
    SDL_QueryTexture(textures->background, NULL, NULL, &w, &h);
    metrics->background.x = (metrics->screen.w - w) / 2;
    metrics->background.y = (metrics->screen.h - h) / 2;
    metrics->background.w = w;
    metrics->background.h = h;
	
	SDL_QueryTexture(textures->gameArea, NULL, NULL, &w, &h);
    metrics->gameArea.x = (metrics->screen.w - w) / 2 ;
    metrics->gameArea.y = (metrics->screen.h - h) / 2;
    metrics->gameArea.w = w;
    metrics->gameArea.h = h;
	
	SDL_QueryTexture(textures->logo, NULL, NULL, &w, &h);
    metrics->logo.x = 0;
    metrics->logo.y = (metrics->screen.h - 4.3*h) ;
    metrics->logo.w = w;
    metrics->logo.h = h;
	
	SDL_QueryTexture(textures->winner, NULL, NULL, &w, &h);
    metrics->winner.x = (metrics->screen.w - w) / 2;
    metrics->winner.y = (metrics->screen.h - h) / 2;
    metrics->winner.w = w;
    metrics->winner.h = h;
	
	SDL_QueryTexture(textures->loser, NULL, NULL, &w, &h);
    metrics->loser.x = (metrics->screen.w - w) / 2;
    metrics->loser.y = (metrics->screen.h - h) / 2;
    metrics->loser.w = w;
    metrics->loser.h = h;
	
	SDL_QueryTexture(textures->equal, NULL, NULL, &w, &h);
    metrics->equal.x = (metrics->screen.w - w) / 2;
    metrics->equal.y = (metrics->screen.h - h) / 2;
    metrics->equal.w = w;
    metrics->equal.h = h;
	
	SDL_QueryTexture(textures->notes[0], NULL, NULL, &w, &h);
    metrics->note.x = 0;
    metrics->note.y = 0;
    metrics->note.w = w;
    metrics->note.h = h;
	
	
	for(i = 0; i < 5; i++){
		
		SDL_QueryTexture(textures->strum[i], NULL, NULL, &w, &h);
		metrics->strum[i].w = w;
		metrics->strum[i].h = h;		
		
		SDL_QueryTexture(textures->strumH[i], NULL, NULL, &w, &h);
		metrics->strumH[i].w = w;
		metrics->strumH[i].h = h;
		
		SDL_QueryTexture(textures->cords[i], NULL, NULL, &w, &h);
		metrics->cords[i].w = w;
		metrics->cords[i].h = h;
		
		
	}
	for( i = 0; i < 10; i++){
		SDL_QueryTexture(textures->score[i], NULL, NULL, &w, &h);
		
		metrics->score[i].w = w;
		metrics->score[i].h = h;		
		
		metrics->score_adv[i].w = w;
		metrics->score_adv[i].h = h;
	}
    return metrics;
}

void freeMetrics(Metrics * metrics)
{
    free(metrics);
}

void initMetrics(Metrics * metrics, int nbStrings)
{
	Textures *textures = NULL;
	int i, espace = metrics->gameArea.w/(nbStrings);
	
	
	textures = (Textures *)calloc(1, sizeof(Textures));
    if (!textures)
        return;
	
	for(i = 0; i < nbStrings; i++){				
		
		metrics->strum[i].x = metrics->gameArea.x + (espace*(1+i)) - metrics->strum[i].w/2 + metrics->gameArea.w;
		metrics->strum[i].y = metrics->gameArea.y + metrics->gameArea.h*0.85;	
		
		metrics->strumH[i].x = metrics->gameArea.x + (espace*(1+i));
		metrics->strumH[i].y = metrics->gameArea.y + metrics->gameArea.h*0.85;	
		
		metrics->cords[i].x = metrics->gameArea.x + (espace*(1+i)) + metrics->gameArea.w;
		metrics->cords[i].y = metrics->gameArea.h*0.20 + metrics->gameArea.y;	
	}	
		
	for(i = 0; i < 10; i++){
	
		metrics->score[i].x = metrics->gameArea.x + (espace*(1+i)) - metrics->strum[i].w/2 - 1.4*metrics->gameArea.w;
		metrics->score[i].y = metrics->gameArea.h*1.3;
		
		metrics->score_adv[i].x = metrics->gameArea.x + (espace*(1+i)) - metrics->strum[i].w/2 + 0.9*metrics->gameArea.w;
		metrics->score_adv[i].y = 0;
		
		
	}
	
	
}
