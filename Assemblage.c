#include<stdio.h>
#include<stdlib.h>
#include "utils.h"
#include "fonc.h"
#include "calele.h"
#include "forfun.h"



void Assemblage(int t, int nbtng, int nbtel, int nbneel, int nbaret, int** pngnel,
				float** pcoord, float** coorEl, int** pnRefAr, int nRefDom, int* numRefD0,
				int* numRefD1, int* numRefF1, int nbRefD0, int nbRefD1, int nbRefF1,
				int* AdPrCoefLi, int* NumCol, float* secmbr, int* nuddir,
				float* valdir, int* AdSuccLi, float* Matrice, int* NbCoef){

  int I; int J; float X;
  int NextAd=1;

  float** MatElem=alloctab(nbneel, nbneel);         /* matrice elementaire */
  float* SMbrElem=malloc(nbneel*sizeof(float));     /* second membre */
  int* NuDElem=malloc(nbneel*sizeof(int));          /* reperage noeuds avec CL Dirichlet */
  float* uDElem=malloc(nbneel*sizeof(float));       /* calc la valeur CL imposée dans ces noeuds */

  

  for (int i=0; i<nbtng; i++){
    nuddir[i]=i+1;
  }

    for(int k=0;k<nbtel;k++){
     selectPts(nbneel,pngnel[k],pcoord,coorEl);
    cal1Elem(nRefDom,nbRefD0,numRefD0,nbRefD1,numRefD1,nbRefF1, numRefF1,
       t,nbneel, coorEl,nbaret, pnRefAr[k],MatElem, SMbrElem,NuDElem,uDElem);
    
    for (int i=0; i<nbneel; i++){
      I=pngnel[k][i];
      secmbr[I-1]=secmbr[I-1]+SMbrElem[i];

      if (NuDElem[i]==-1){
		nuddir[I-1]=-I;
		valdir[I-1]=uDElem[i];
      }
      else if(NuDElem[i]==0){
		nuddir[I-1]=0;
      }

      Matrice[I-1]=Matrice[I-1]+MatElem[i][i];
      for(int j=0; j<i; j++){
		X=MatElem[i][j];
		J=pngnel[k][j];
	  if (J>I){
		assmat_(&J, &I, &X, AdPrCoefLi, NumCol, AdSuccLi, &Matrice[nbtng], &NextAd);
	  }
	  else{
		assmat_(&I, &J, &X, AdPrCoefLi, NumCol, AdSuccLi, &Matrice[nbtng], &NextAd);
	  }
      }
    }

  }

  AdPrCoefLi[nbtng-1] = NextAd;
  *NbCoef = AdPrCoefLi[nbtng-1]-1;

  freetab(MatElem);
  free(SMbrElem);
  free(NuDElem);
  free(uDElem); 

}
