#include <stdlib.h>
#include <stdio.h>
int main(int argc, char **argv){	
  int i=0,rang,init,max=0,res=0;
  
  printf("Terme initial?\n");
  res=scanf("%d",&res);
  init = res;
  printf ("Rang de la suite?\n");
  rang=scanf("%d",&rang);
  
  /* // Calcul du n-ieme terme */
  for (i=0; i<rang; i++)
  {
    if (res%2 == 0)   // terme pair
      res /= 2;
    else
      res = 3*res + 1;
  }
  printf ("terme no %d = %d\n",rang,res);  
  
  
  // temps de vol et altitude max
  res = init;
  
  max = res;
  while (res != 1)
  {
    if (res%2 == 0)   // terme pair
      res /= 2;
    else
      res = 3*res + 1;
    if (res > max)
      max = res;
    i++;
  }
  printf ("temps de vol = %d\n",i);  
  printf ("Altitude maximale = %d\n", max);
  return 0;
}
