
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "../SheetMusic/analysis.h"
#include "../SheetMusic/midiFile.h"
#include "../SheetMusic/sheetMusic.h"
#include "../GameModel/model.h"
#include "../tools.h"
#include "display.h"

#include "mainWindow.h"
#include "textures.h"

GameDisplay * newGameDisplay(MainWindow * mainWindow)
{
    GameDisplay * gameDisp = NULL;

    if (!mainWindow)
        return NULL;

    gameDisp = (GameDisplay *)calloc(1, sizeof(GameDisplay));
    if (!gameDisp)
        goto ERROR_LABEL;

    gameDisp->textures = newTextures(mainWindow->renderer);
    if (!gameDisp->textures)
        goto ERROR_LABEL;
    gameDisp->metrics = newMetrics(gameDisp->textures);
    if (!gameDisp->metrics)
        goto ERROR_LABEL;

    return gameDisp;

ERROR_LABEL:
    freeGameDisplay(gameDisp);
    return NULL;
}

void freeGameDisplay(GameDisplay * gameDisp)
{
    if (gameDisp)
    {
        freeTextures(gameDisp->textures);
        freeMetrics(gameDisp->metrics);

        free(gameDisp);
    }
}

void updateGameDisplay(GameDisplay *gameDisp, MainWindow *mainWindow, Model *model)
{
    SDL_Renderer *renderer = mainWindow->renderer;
    Textures *textures = gameDisp->textures;
    GameSheet *gameSheet = model->gameSheet;
    GameNote *notes, *curNote;
    Metrics *metrics;
    int x, y, i;
	int nbStrings = model->gameSheet->nbStrings;	
    int stringIdx, staffIdx;
	
	staffIdx = gameSheet->staffIdx;
    notes = gameSheet->notes[staffIdx];
    metrics = gameDisp->metrics;
	
	int espace = metrics->gameArea.w/(nbStrings);
	int score[6] = { 0 };	
	int score_adv[6] = { 0 };	
	int points = (int) model->points;   
	int points_adv = (int) model->points_adv;
    //******************************************************************************************************************
    // Remise à zéro de l'affichage

    SDL_RenderClear(renderer);

    //******************************************************************************************************************
    // Fond de la guitare
	
	x = metrics->background.x;
    y = metrics->background.y;
    renderTexture(textures->background, renderer, x, y);
	
	x = metrics->logo.x;
    y = metrics->logo.y;
    renderTexture(textures->logo, renderer, x, y);
	
    x = metrics->gameArea.x;
    y = metrics->gameArea.y;
    //renderTexture(textures->gameArea, renderer, x, y);
	
	if(model->resultat == 1){
		if(model->win_lose == 1){
			
			x = metrics->winner.x;
			y = metrics->winner.y;
			renderTexture(textures->winner, renderer, x, y);	
		}
		if(model->win_lose == 0){
			
			x = metrics->loser.x;
			y = metrics->loser.y;
			renderTexture(textures->loser, renderer, x, y);
		}
		
		if(model->win_lose == 2){
			
			x = metrics->equal.x;
			y = metrics->equal.y;
			renderTexture(textures->equal, renderer, x, y);
		}
		
		i = 5;
		while(points_adv > 0 && i >= 0){
					
			score_adv[i] = points_adv % 10;
			i--;
			points_adv /= 10;
		}
		for(i = 0; i < 6; i ++){
			
			x = metrics->score_adv[i].x;
			y = metrics->score_adv[i].y;
			renderTexture(textures->score[score_adv[i]], renderer, x, y);		
		} 	
	}
	
	for(i = 0; i < nbStrings; i++){
		
		x = metrics->cords[i].x;
		y = metrics->cords[i].y;
		renderTexture(textures->cords[i], renderer, x, y);		
	}
	
	for(i = 0; i < nbStrings; i++){
		
		x = metrics->strum[i].x;
		y = metrics->strum[i].y;
		
		
		if(model->keys->fretDown[i] == 1){
			
			renderTexture(textures->strumH[i], renderer, x, y);			
		}				
		renderTexture(textures->strum[i], renderer, x, y);			
	}	
	
	i = 5;
	while(points > 0 && i >= 0){
					
		score[i] = points % 10;
		i--;
		points /= 10;
	}
	for(i = 0; i < 6; i ++){
		
		x = metrics->score[i].x;
		y = metrics->score[i].y;
		renderTexture(textures->score[score[i]], renderer, x, y);
		
	} 
    //******************************************************************************************************************
    // Notes
	for(i = 0; i < model->gameSheet->nbNotes[staffIdx]; i++){
							
		curNote = &notes[i];
		stringIdx = curNote->stringIdx;
		
		if(curNote->state == statePlayed){
			
			curNote->visible = 0;
		}		
		if(nbStrings > stringIdx && curNote->visible == 1 ){			
			
			x = metrics->gameArea.x + espace*(1 + stringIdx) - metrics->strum[stringIdx].w/2 + metrics->gameArea.w;
			y = metrics->gameArea.y + curNote->relPos * metrics->gameArea.h;
			renderTexture(textures->notes[stringIdx], renderer, x, y);			
		}
		
	}			
    //******************************************************************************************************************
    // Mise à jour de l'affichage

    SDL_RenderPresent(renderer);
}
