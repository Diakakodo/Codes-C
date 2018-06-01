
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "model.h"
#include "timer.h"
#include "../GameNetwork/network.h"

GameSheet * newGameSheet(SheetMusic * sheet)
{
    GameSheet * gameSheet = NULL;
    Note * note = NULL;
    GameNote * gameNote = NULL;
    int nbStaves;
    int i, noteIdx;

    if (!sheet)
        return NULL;

    gameSheet = (GameSheet *)calloc(1, sizeof(GameSheet)); nbStaves = sheet->nbStaves;

    gameSheet->nbStaves = nbStaves;
    gameSheet->nbStrings = sheet->nbStrings;
    gameSheet->nbNotes = (int *)calloc(nbStaves, sizeof(int));
    gameSheet->notes = (GameNote **)calloc(nbStaves, sizeof(GameNote *));

    memcpy(gameSheet->nbNotes, sheet->nbNotes, nbStaves * sizeof(int));

    for (i = 0; i < nbStaves; i++)
    {
        gameSheet->notes[i] = (GameNote *)calloc(sheet->nbNotes[i], sizeof(GameNote));
    }

    for (i = 0; i < nbStaves; i++)
    {
        for (noteIdx = 0; noteIdx < sheet->nbNotes[i]; noteIdx++)
        {
            note = sheet->notes[i] + noteIdx;
            gameNote = gameSheet->notes[i] + noteIdx;

            gameNote->value = note->value;
            gameNote->stringIdx = note->stringIdx;
            gameNote->playingTime = note->appearingTime;
            gameNote->duration = note->durationTime;
            gameNote->endingTime = note->appearingTime + note->durationTime;
            gameNote->visible = 1;
            gameNote->state = stateAlive;
            gameNote->relPos = 0.0f;
			

            if (gameNote->duration > MINIMAL_LONG_NOTE)
                gameNote->type = typeLongNote;
            else
                gameNote->type = typeShortNote;
        }
    }

    return gameSheet;
}

void freeGameSheet(GameSheet * gameSheet)
{
    int i;

    if (gameSheet)
    {
        if (gameSheet->notes)
        {
            for (i = 0; i < gameSheet->nbStaves; i++)
                free(gameSheet->notes[i]);
        }
        free(gameSheet->notes);
        free(gameSheet->nbNotes);
    }
    free(gameSheet);
}

void updateGameSheet(GameSheet *sheet, Timer *timer)
{
    int staffIdx, i;
	float fallTime = 0;
    GameNote *notes;

    staffIdx = sheet->staffIdx;
    notes = sheet->notes[staffIdx];    
   
    for(i = 0; i < sheet->nbNotes[staffIdx]; i++){
		
		notes[i].visible = 1;		
		
		fallTime = notes[i].playingTime - timer->timeBeforeStrum;
		
		if (fallTime < timer->currentTime){
				
			notes[i].relPos += timer->delta * timer->relSpeed;
		}
		else{
			
			notes[i].visible = 0;
		}
	
	}	
}

void checkStrum(Model *model){
    
	int j, fret;
	float time, noteTime;
	
	for(j = 0; j < model -> gameSheet->nbNotes[model->gameSheet->staffIdx] ; j++){
	
		time = model -> timer->currentTime;
		noteTime = model -> gameSheet -> notes[model -> gameSheet->staffIdx][j].playingTime;		
		fret = model->keys->fretDown[model->gameSheet->notes[model->gameSheet->staffIdx][j].stringIdx];
		
		if((model->keys->strumDown == 1) && ( fret == 1) &&  model->gameSheet->notes[model->gameSheet->staffIdx][j].state != statePlayed){			
			
			if((time - noteTime > - 0.1) && (time - noteTime < 0.1)){
							
				model->gameSheet->notes[model->gameSheet->staffIdx][j].state = statePlayed;					
				model->points += 10;		
			}			
		}			
	}	
}

Model * newModel(SheetMusic * sheet, float relSpeed)
{
    Model * model = NULL;
	int i;
    if (!sheet)
        return NULL;

    model = (Model *)calloc(1, sizeof(Model));

    model->keys = newGameKeys();
    model->gameSheet = newGameSheet(sheet);
    model->timer = newTimer(relSpeed);
    model->points = 0.0f;
	model->network = 0;
	model->connexion = 0;
	model->win_lose = -1;
	model->resultat = 0;	
	
	model->args = (char**) calloc(4, sizeof(char*));
	for( i = 0; i < 4; i++){
		
		model->args[i] = (char *) calloc(2000, sizeof(char));
	}

    return model;
}

void freeModel(Model * model)
{
    if (model)
    {
        freeGameKeys(model->keys);
        freeGameSheet(model->gameSheet);
        freeTimer(model->timer);
		free(model->args);
    }
    free(model);
}

void updateModel(Model *model)
{
    Timer * timer = model->timer;
    GameSheet * gameSheet = model->gameSheet;

    updateTimer(timer);
    updateGameSheet(gameSheet, timer);
    checkStrum(model);
}
