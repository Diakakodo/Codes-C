#include "recursif.h"
#include <stdio.h>
int pair(int n){
	
	return (n==0)?1:impair(n-1);
}
int impair(int n){
	
	return (n==0)?0:pair(n-1);
}
char *PremiereOccurence (char *str, char occ){
	if(*str == '\0')
		return NULL;
	
	if(*str==occ)
		return str;
	else	
		return PremiereOccurence(str+1,occ);
}

int CompareChaine (char *str1, char *str2){
	
	char *alphabet="abcdefghijklmnopqrstuvwxyz";
	char *ch1=PremiereOccurence(alphabet,*str1);
	char *ch2=PremiereOccurence(alphabet,*str2);
	
	if(ch1>ch2)
		return 1;
	if(ch1<ch2)
		return -1;		
	
	if(ch1==ch2){
		
		if(ch1==NULL)			
			return 0;			
					
		if(CompareChaine(str1+1,str2+1)==0)		
			return 0;
	}
	return 2;
}

int NbOcc (char *str, char c){
	int compteur=0;
	char *test=PremiereOccurence(str,c);
	
	while(test!=NULL){
		
		compteur++;
		test=PremiereOccurence(test+1,c);
	}	
	
	return compteur;								
}

char InverserMot(char* str,char* str2,int cpt){
	
	if(*(str+1)!='\0'){
		
		str2[cpt]=InverserMot(str+1,str2,cpt-1);
		
		
	}
	return str[0];
}

float Sardine(float Sa,float Re,float MoRe,float CrSa,float FacEv,int cpt){
	
	if(cpt!=0)
		Sa=Sardine(Sa,Re,MoRe,CrSa,FacEv,cpt-1)*(1+CrSa-FacEv*Requin(Sa,Re,MoRe,CrSa,FacEv,cpt-1));		
		
	return Sa;
	
}

float Requin(float Sa,float Re,float MoRe,float CrSa,float FacEv,int cpt){
	
	if(cpt!=0)		
		Re=Requin(Sa,Re,MoRe,CrSa,FacEv,cpt-1)*(1-MoRe+FacEv*Sardine(Sa,Re,MoRe,CrSa,FacEv,cpt));
	
	return Re;	
	
} 