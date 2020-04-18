#include "calele.h"
#include "utils.h"
#include "fonc.h"
#include<stdio.h>
#include<stdlib.h>

void cal1Elem(int nRefDom, int nbRefD0, int* numRefD0, int nbRefD1, int* numRefD1,
			  int nbRefF1, int* numRefF1, int typEl, int nbneel, float** coorEl, int nbaret, 
			  int* nRefArE1, float** MatElem, float* SMbrElem, int* NuDElem, float* uDElem){
				  
  /*** Procédure cal1Elem ***
  ----------------------------------------------------------
  Regroupe les calculs élémentaires surfaciques et linéiques
  (sur les aretes) de l'élément courant K.

  # Inputs
  nRefDom   : numéro de référence du domaine
  numRefD0  : numéros de références associés aux noeuds "Dirichlet homogene"
  numRefD1  : "Dirichlet non-homogene"
  numRefF1  : "Neumann"
  nbRefD0   : nombre de valeurs de numRefD0
  nbRefD1   : nombre de valeurs de numRefD1
  nbRefF1   : nombre de valeurs de numRefF1
  typEl     : type de l'élément
  nbneel    : nombre de noeuds de l'élément
  coorEl    : tableau contenant les coordonnées des nbneel
              noeuds de l'élément courant K
  nbaret    : nombre d'aretes par élément
  nRefArEl  : numéros de référence des nbaret aretes de l'élément

  # Outputs
  MatElem   : matrice élémentaire calculée dans l'élément K
  SMbrElem  : vecteur élémentaire calculé dans l'élément K
  NuDElem   : reperage des noeuds avec CL Dirichlet (tableau initialisé a 1)
  uDElem    : calcule dans ces noeuds la valeur des CL imposées

  *** Girard Clément ***
  *** Draghici Cristian ***

  ----------------------------------------------------------
  */				  
				  			   
  /* Allocation et déclaration */
  int nRef;                             	/* Numéro de référence de chq arete */
  int* neelAr=malloc(2*sizeof(int));    	/* Tableau des numéros de noeuds selectionnés */
  float** coorAr=malloc(2*sizeof(float *));	/* Tableau des noeuds concernés */

  float** M_Ar=alloctab(2,2);           /* Matrice élémentaire d'arete */
  float* B_Ar=malloc(2*sizeof(float));  /* Vecteur élémentaire d'arete */

  /* Initialisations */

  for(int i=0; i<nbneel; i++){
    SMbrElem[i]=0;
    NuDElem[i]=1;
    uDElem[i]=0;
    for(int j=0; j<nbneel; j++){
      MatElem[i][j]=0;
    }
  }


  intElem(coorEl,nbneel,typEl, MatElem, SMbrElem);
  
  for(int i=0; i<nbaret; i++){
	  
	/* CL Dirichlet homogene(vaut 0) */  
    nRef=nRefArE1[i];
    for(int j=0; j<nbRefD0; j++){ 
      if(nRef==numRefD0[j]){
		numNaret(typEl,i+1,neelAr);
		NuDElem[neelAr[0]-1]=0;
		NuDElem[neelAr[1]-1]=0;
	  }
    }
    
    /* CL Dirichlet non-homogene(vaut -1) */
    for(int j=0; j<nbRefD1; j++){ 
      if(nRef==numRefD1[j]){
		numNaret(typEl,i+1,neelAr);
		NuDElem[neelAr[0]-1]=-1;
		NuDElem[neelAr[1]-1]=-1;
		uDElem[neelAr[0]-1]=UD(coorEl[neelAr[0]-1]);
		uDElem[neelAr[1]-1]=UD(coorEl[neelAr[1]-1]);
      }
    }
    
    for(int j=0; j<nbRefF1; j++){
      if(nRef==numRefF1[j]){
		numNaret(typEl,i+1,neelAr);
		selectPts(2,neelAr,coorEl,coorAr);
		
		/*printf("noeuds concernes : \n");
		printf("%f %f\n", coorAr[0][0], coorAr[0][1]);
		printf("%f %f\n", coorAr[1][0], coorAr[1][1]);*/

		M_Ar[0][0]=0; M_Ar[0][1]=0; M_Ar[1][0]=0; M_Ar[1][1]=0;
		B_Ar[0]=0; B_Ar[1]=0;
		
		intAret(coorAr,2,3,M_Ar,B_Ar);
		MatElem[neelAr[0]-1][neelAr[0]-1] = MatElem[neelAr[0]-1][neelAr[0]-1] + M_Ar[0][0];
		MatElem[neelAr[1]-1][neelAr[0]-1] = MatElem[neelAr[1]-1][neelAr[0]-1] + M_Ar[1][0];
		MatElem[neelAr[0]-1][neelAr[1]-1] = MatElem[neelAr[0]-1][neelAr[1]-1] + M_Ar[0][1];
		MatElem[neelAr[1]-1][neelAr[1]-1] = MatElem[neelAr[1]-1][neelAr[1]-1] + M_Ar[1][1];
		SMbrElem[neelAr[0]-1]=SMbrElem[neelAr[0]-1]+B_Ar[0];
		SMbrElem[neelAr[1]-1]=SMbrElem[neelAr[1]-1]+B_Ar[1];
		/* printf(" Arete %d \n",i);
		   printf("%f  %f\n",B_Ar[0],B_Ar[1]); */
      }
    }
  
  }
  free(coorAr);
  free(neelAr);
  freetab(M_Ar);
  free(B_Ar);
}
