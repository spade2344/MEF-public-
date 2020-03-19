#include "calele.h"
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

void ADWDW(int nbneel, float **valDFbase, float **invJFK, float eltdif, float **cofvar, float **matelm) {
  
  /*** Procédure ADWDW ***
  ---------------------------------------------------------
  Calcul de la matrice de rigidité de la forme bilinéaire a

  # Inputs
  nbneel    : nombre de noeuds de l'élément
  valDFbase : dérivée des fonctions de base w
  Dfctbas   : valeurs des dérivées de fonctions de base au
              point de quadrature courant
  eltdif    : élément différentiel multiplié par le poids de
              quadrature
  cofvar    : valeur du coefficient variable (fonction a
              integrer calculée en l'image par FK du point
              de quadrature courant)

  # Outputs
  matelm    : matrice élémentaire de rigidité actualisée
              Dimensions utiles : matelm(nbneel,nbneel)

  *** Girard Clément ***
  *** Draghici Cristian ***
  ---------------------------------------------------------
  */

  float **val_ps=alloctab(nbneel,2);

  /* Dérivée des fonctions de base dans l'élément courant */
  for(int i=0; i<nbneel; i++){
   val_ps[i][0]=valDFbase[i][0]*invJFK[0][0] + valDFbase[i][1]*invJFK[1][0];
   val_ps[i][1]=valDFbase[i][0]*invJFK[0][1] + valDFbase[i][1]*invJFK[1][1];
  }
 
  
  for (int i=0; i<nbneel; i++) {
    for (int j=0; j<nbneel; j++) {
      matelm[i][j] = matelm[i][j] + eltdif*(cofvar[0][0]*val_ps[i][0]*val_ps[j][0]
					  + cofvar[0][1]*val_ps[i][0]*val_ps[j][1]
					  + cofvar[1][0]*val_ps[i][1]*val_ps[j][0]
					  + cofvar[1][1]*val_ps[i][1]*val_ps[j][1]);
    }
  }
  freetab(val_ps);
}

