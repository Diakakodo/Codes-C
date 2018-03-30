/*******
 * Read input from STDIN
 * Use printf(...) or fprintf( stdout, ...) to output your result.
 * Use:
 *  localPrint( char* mystring)
 * to display variable in a dedicated area.
 * ***/
#include <stdlib.h>
#include <stdio.h>
#include "libisograd.h"
#include <math.h>
int main() {
    //printf("ok\n");
    char s[1024];
    int heures=0,minutes=0,secondes=0,i=0,j=0,coord[10][3];
    float distance=0;
	while (scanf("%s", &s) != EOF) {
        switch(j){
            case 0:
                sscanf(s,"%d",&coord[i][j]);
                j=1;
            break;
            
            case 1:
                sscanf(s,"%d",&coord[i][j]);
                j=2;
            break;
            
            case 2:
                sscanf(s,"%d:%d:%d",&heures,&minutes,&secondes);
                coord[i][j]=heures*3600+minutes*60+secondes;
                j=0;
                i++;
            break;
        }
	}
	for(int z=0;z<i-1;z++){
	    
	    distance+=sqrt(pow(coord[z+1][0]-coord[z][0],2)+pow(coord[z+1][1]-coord[z][1],2));
	    
	}
	distance/=1000;
	
	printf("%.2f\n",3600*distance/(coord[i-1][2]-coord[0][2]));
   
	return 0;
}