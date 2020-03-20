#include<stdio.h>
#include<stdlib.h>
#include "forfun.h"

void LecSMO(int* NbLignO1, int* NbCoefO1, float** secmbrO1, int** AdPrCoefLiO1,
            float** MatriceO1, int** NumColO1, char* nomficO){

  FILE* smo1 = fopen(nomficO, "rb");
  if (smo1 == NULL){
    printf("Ouverture du fichier impossible !\n");
    exit(1);
  }

  /* Lecture du fichier binaire*/
  fread(NbLignO1, sizeof(int), 1, smo1 );

  *AdPrCoefLiO1=malloc(*NbLignO1*sizeof(int));
  *secmbrO1=malloc(*NbLignO1*sizeof(float));

  fread( *secmbrO1, sizeof(float), *NbLignO1, smo1 );
  fread( *AdPrCoefLiO1, sizeof(int), *NbLignO1, smo1 );

  *NbCoefO1 = (*AdPrCoefLiO1)[*NbLignO1-1]-1;

  *MatriceO1=malloc((*NbLignO1+*NbCoefO1)*sizeof(float));
  *NumColO1=malloc((*NbCoefO1)*sizeof(int));

  fread( *MatriceO1, sizeof(float),*NbLignO1+*NbCoefO1, smo1 );
  fread( *NumColO1, sizeof(int), *NbCoefO1, smo1 );

  fclose(smo1);

}
