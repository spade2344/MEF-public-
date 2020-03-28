#include<stdio.h>
#include<stdlib.h>
#include "forfun.h"

void LecSMD(int* NbLign1, float** secmbr1, int** nuddir1,
            float** valdir1, int** AdPrCoefLi1, float** Matrice1, int** NumCol1,
            int** AdSuccLi1, char* nomfic){

  int NbCoef1;

  FILE* fich = fopen(nomfic, "rb");
  if (fich == NULL){
    printf("Ouverture du fichier impossible !\n");
    exit(1);
  }

  /* Lecture du fichier binaire*/
  fread(NbLign1, sizeof(int), 1, fich );

  *AdPrCoefLi1=malloc(*NbLign1*sizeof(int));
  *secmbr1=malloc(*NbLign1*sizeof(float));
  *nuddir1=malloc(*NbLign1*sizeof(int));
  *valdir1=malloc(*NbLign1*sizeof(float));

  fread( *secmbr1, sizeof(float), *NbLign1, fich );
  fread( *nuddir1, sizeof(int), *NbLign1, fich );
  fread( *valdir1, sizeof(float), *NbLign1, fich );
  fread( *AdPrCoefLi1, sizeof(int), *NbLign1, fich );

  NbCoef1 = (*AdPrCoefLi1)[*NbLign1-1]-1;

  *Matrice1=malloc((*NbLign1+NbCoef1)*sizeof(float));
  *NumCol1=malloc((NbCoef1)*sizeof(int));
  *AdSuccLi1=malloc((NbCoef1)*sizeof(int));

  fread( *Matrice1, sizeof(float),*NbLign1+NbCoef1, fich );
  fread( *NumCol1, sizeof(int), NbCoef1, fich );
  fread( *AdSuccLi1, sizeof(int), NbCoef1, fich );

  fclose(fich);

}
