#include "dichotomie.h"
int dichotomie(int N){		
	int min=0,max=50000,Test=max;
	
	printf("%d\n",Test);
	while(Test != N){
		
		if(Test<N){
			min=Test;			
			Test=(max+min)/2;
			printf("%d\n",Test);			
		}			
		if(Test>N){
			max=Test;
			
			Test=(max+min)/2;
			printf("%d\n",Test);
		}				
		if(Test==N)	break;
					
	}
	return Test;
}

int dichotomieRec(int N,int min,int max){		
	int Test=(min+max)/2;
	
	printf("%d\n",Test);	
	if(Test==N)	return Test;
		
	if(Test<N)	Test=dichotomieRec(N,Test+1,max);				
				
	if(Test>N)	Test=dichotomieRec(N,min,Test-1);
		
	return Test;
}