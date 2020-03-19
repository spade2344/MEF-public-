#include <stdlib.h>
#include "utils.h"
#include <stdio.h>

int lecfima(char *ficmai, int *type1, int *nbtng, float ***pcoord, int *nbtel, int ***pngnel, int *nbneel, int *nbaret, int ***pnRefAr){

  FILE* fic=fopen(ficmai,"r");
  if (fic == NULL){
    printf("Erreur d'ouverture \n");
    exit(1);
  }

  
  fscanf(fic,"%d", nbtng); 
  float ** P =  alloctab(*nbtng,2);
  for (int i=0; i<*nbtng; i++){
    fscanf(fic,"%f %f",&P[i][0],&P[i][1]);
    }
  *pcoord = P;
  fscanf(fic,"%d %d %d %d", nbtel,type1,nbneel,nbaret);

  int ** P1 = alloctab_int(*nbtel,*nbneel);
  int ** P2 = alloctab_int(*nbtel,*nbaret);

  for(int i=0; i<*nbtel; i++){
    for(int j=0; j<*nbneel; j++){
      fscanf(fic,"%d ",&P1[i][j]);
    }
    for(int j=0; j<*nbaret; j++){
      fscanf(fic,"%d ", &P2[i][j]);
    }
  }
  *pnRefAr=P2;
  *pngnel=P1;

  fclose(fic);
  return 1;
}
