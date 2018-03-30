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

int main() {
   
   char s[1024];
   int i=-1,j=-1,lignes=0,Ca=0,Cb=0;
   int **res;
	while (scanf("%s", &s) != EOF) {
	    printf("ok\n");
		if(i>-1){
		    if(j%2==0){
		        
		        sscanf(s,"%d",&res[i][0]);
		    }
		    if(j%3==0){
		        
		        sscanf(s,"%d",&res[i][1]);
		    }
		}
		else{
		    sscanf(s,"%d",&lignes);
		    res=(int**)calloc(lignes,sizeof(int*));
		    for(int a=0;a<2;a++){
		        res[a]=(int*)calloc(2,sizeof(int));
		    }
		    j=3;
		} 
		switch(j){
		     case 3:
		        j=2;
		        i++;
		     break;
		     
		     case 2:
		        j=3;
		     break; 
		}
	}
	for(i=0;i<lignes;i++){
	        
	    if(res[i][0]>res[i][1]){
	        printf("Ca : %d\n",Ca);
	        Ca++;
	    }     
	    else{ Cb++; }
	}
	if(Ca>Cb){
	    printf("A\n");
	}   
	 else { printf("B\n"); }
	 
	return 0;
}