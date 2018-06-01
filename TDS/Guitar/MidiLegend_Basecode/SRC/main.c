
#include <stdlib.h>
#include <math.h>
#include <time.h>

#ifdef _WIN32
#include <SDL.h>
#include <SDL_mixer.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#endif

#include "GameModel/model.h"
#include "GameDisplay/display.h"
#include "GameDisplay/mainWindow.h"
#include "GameDisplay/textures.h"
#include "GameControler/gameKeys.h"
#include "GameNetwork/network.h"

int playMusicWithDelay(void *ptr){
    MusicThread *music = (MusicThread*)ptr;
    int delay = (int)(music->t * 1000);
    printf("Thread Delay = %d\n", delay);
#ifdef _WIN32
    Sleep(delay);
#else
    usleep(delay * 1000);
#endif

    Mix_PlayMusic(music->music, 1);
    return 0;
}

int main(int argc, char** argv){
	
    MainWindow * mainWindow = NULL;
    SDLGameConfig * config = NULL;
    Mix_Music * music = NULL;
    MusicThread musicThread;
    Model * model = NULL;
    GameDisplay  * gameDisp = NULL;
    SheetMusic * sheet = NULL;
	
    FILE  *midiFile = NULL;
    int nbStrings;
    int pianoMode;
    int staffIdx;
	int i;
    float relSpeed;
	
    //******************************************************************************************************************
    // Récupération des arguments du main

    if (argc < 3)
    {
        printf("Arguments insuffisants\n");
        return EXIT_FAILURE;
    }

    midiFile = fopen(argv[1], "rb");
    if (!midiFile)
    {
        printf("Erreur d'ouverture du fichier %s\n", argv[1]);
        return EXIT_FAILURE;
    }
    nbStrings = atoi(argv[2]);
    staffIdx = (argc > 3) ? atoi(argv[3]) : 0;

    //******************************************************************************************************************
    // Traitement du midi et de la partition

    // Lecture du fichier midi
    sheet = newSheetMusic(midiFile);
    if (!sheet)
    {
        printf("Erreur de creation de la partition\n");
        return EXIT_FAILURE;
    }
    fclose(midiFile);

    // Traitement de la partition
    sheet->nbStrings = nbStrings;
    placeNotes(sheet);

    // Affichage de la partition
    printSheetMusic(sheet);

    //******************************************************************************************************************
    // Initialisation du modèle

    relSpeed = nbStrings * SPEED;
    model = newModel(sheet, relSpeed);
    if (!model)
    {
        printf("Erreur de creation du modele\n");
        return EXIT_FAILURE;
    }
    freeSheetMusic(sheet);

    model->gameSheet->staffIdx = staffIdx;
	
	if( argc == 5){	
	
		model->network = 1;
		for(i = 0; i < 4; i++){
			
			if(!(strcpy( model->args[i], argv[i + 1]))){
				
				printf("Erreur lors de la copie des arguments\n");
				return EXIT_FAILURE;
			}	
				
		}
	}    //******************************************************************************************************************
    // Initialisation de la vue

    initSDL();
    mainWindow = newMainWindow();
    if (!mainWindow)
    {
        printf("Erreur de creation de la fenetre\n");
        return EXIT_FAILURE;
    }
    gameDisp = newGameDisplay(mainWindow);
    if (!gameDisp)
    {
        printf("Erreur de creation de l'affichage\n");
        return EXIT_FAILURE;
    }
	
    //******************************************************************************************************************
    // Initialisation du controller

    config = newGameConfig(pianoMode);
    if (!config)
    {
        printf("Erreur de creation du controller\n");
        return EXIT_FAILURE;
    }
	initMetrics(gameDisp->metrics, nbStrings);
    //******************************************************************************************************************
    // Initialisation de la musique
	if( model->network == 1){
	
		if(!client(model)){
			printf("Connexion impossible\n");
			return 0;
		}	
	}	
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
    {
        printf("Erreur de chargement du mixer : %s\n", Mix_GetError());
        return EXIT_FAILURE;
    }
    music = Mix_LoadMUS(argv[1]);
    if (music == NULL)
    {
        printf("Erreur de chargement de la musique : %s\n", argv[1]);
        printf("  SDL : %s\n", Mix_GetError());
        return EXIT_FAILURE;
    }
#ifdef _WIN32
    musicThread.t = STRUM_AREA / relSpeed - 0.30f;
#else
    musicThread.t = STRUM_AREA / relSpeed;
#endif
    musicThread.music = music;
    SDL_CreateThread(playMusicWithDelay, "music", &musicThread);

    //******************************************************************************************************************
    // Boucle de rendu

    // Lancement du timer
    startTimer(model->timer);	

    while (!(model->keys->quitDown || model->keys->exitDown))
    {
        // Mise à jour du controller
        processGameEvents(config, model->keys);

        // Mise à jour du modèle
        updateModel(model);

        // Mise à jour de la vue
        updateGameDisplay(gameDisp, mainWindow, model);
		
		if(model->connexion == 1 && model->resultat == 0){
			if(model->timer->currentTime > model->gameSheet->notes[model->gameSheet->staffIdx][model->gameSheet->nbNotes[model->gameSheet->staffIdx] - 1].playingTime){
				client(model);
				model->resultat = 1;
				if(model->points_adv > model->points){
					model->win_lose = 0;
				}
				else if(model->points_adv < model->points){
					model->win_lose = 1;
				}
				else if(model->points_adv == model->points){
					model->win_lose = 2;
					
				}
			}		
		}	
    }

    //******************************************************************************************************************
    // Libération de la mémoire

    freeGameConfig(config);
    freeModel(model);
    freeGameDisplay(gameDisp);
    freeMainWindow(mainWindow);

    Mix_FreeMusic(music);
    Mix_CloseAudio();
    quitSDL();

    return EXIT_SUCCESS;
}
