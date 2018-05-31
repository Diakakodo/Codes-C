#ifndef _NETWORK_INCLUDED_
#define _NETWORK_INCLUDED_

#include <stdio.h> 
#include <string.h>    
#include <sys/socket.h>    
#include <arpa/inet.h> //inet_addr
#include "../GameModel/model.h"
int client(Model *model);

#endif