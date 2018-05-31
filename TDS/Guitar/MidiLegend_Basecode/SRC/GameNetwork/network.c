#include <stdio.h> 
#include <string.h>    
#include <sys/socket.h>    
#include <arpa/inet.h> //inet_addr
#include "network.h"

 
int client(Model *model){

	int i = 0, j = 0;
	if( model->args == NULL){
		printf("Verifiez les arguments de la ligne de commande.\n");
		return 0;
	}	
	
    int sock;
    struct sockaddr_in server;
    char server_reply[2000]; 
	float server_score = 0;
	
	
     
    //Create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
    {
        printf("Erreur creation socket");
    }
    puts("Socket cree");
     
	 
    server.sin_addr.s_addr = inet_addr(model->args[3]);
	
    server.sin_family = AF_INET;

	if(model->connexion == 0){
		server.sin_port = htons( 8886 );
	
	}
	else if(model->connexion == 1){
		server.sin_port = htons( 8887 );
	}
	
 
    //Connect to remote server	
	
    while(connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0){
		
        perror("En attente de connexion ");
      
    }   
 
    puts("Connecte\n");
     
    //keep communicating with server
	if( model->connexion == 0){
		
		char *envoi = (char*) calloc(2000, sizeof(char));
		
		for(i = 0; i < 3; i++ ){			
			
			sprintf(envoi,"%d %s", (int)strlen(model->args[i]), model->args[i]);
						
			if( send(sock , envoi , strlen(envoi) , 0) < 0){
				puts("Send erreur.");
				return 0;
			}
			printf("Envoi = %s\n", envoi);
			//Receive a reply from the server
			if( recv(sock , server_reply , 2000 , 0) < 0){
				puts("recv erreur.");
				break;
			}
			
			for(j = 0; j < 3; j++){
				
			//	printf("server_reply[%d] = %c\nenvoi[%d] = %c\n", j, server_reply[j], j, envoi[j]);
				if(server_reply[j] == envoi[j]){
					
					printf("ok.\n");
				}
				else{
					
					printf("Erreur.\n");
					return 0;
				}				
			}
		}		
		model->connexion = 1;	
		free(envoi);
	}		
	if( model->connexion == 1){		
					
		if(send(sock , &model->points , sizeof(float) , 0) < 0){
			puts("Send erreur.");
			return 0;
		}
		printf("Envoi = %f\n", model->points);
		//Receive a reply from the server
		if(recv(sock , &server_score , sizeof(float) , 0) < 0){
			puts("recv erreur.");
			return 0;
		}	
		printf("Server_score = %f\n", server_score);
		model->points_adv = server_score;
		
		return 1;
	}
     
    //pclose(sock);
    return 1;
}