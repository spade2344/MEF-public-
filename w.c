#include "calele.h"
#include<stdio.h>

void W(int nbneel, float *fctbas, float eltdif, float cofvar, float *matelm) {
  
  /*** Procédure W ***
  ---------------------------------------------------------
  Calcul du second membre de la forme linéaire f

  # Inputs
  nbneel    : nombre de noeuds de l'élément
  fctbas    : valeurs des fonctions de base au point de
              quadrature courant
  eltdif    : élément différentiel multiplié par le poids de
              quadrature
  cofvar    : valeur du coefficient variable (fonction a
              integrer calculée en l'image par FK du point
              de quadrature courant)

  # Outputs
  matelm    : vecteur élémentaire actualisé
              Dimensions utiles : matelm(nbneel)

  *** Girard Clément ***
  *** Draghici Cristian ***
  ---------------------------------------------------------
  */  
  
  int j;
  float coeff;
  coeff = eltdif*cofvar;
  for (j=0; j<nbneel; j++) {
    matelm[j] = matelm[j] + coeff*fctbas[j];
  }
}


