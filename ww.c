#include "calele.h"

void WW(int nbneel, float *fctbas, float eltdif, float cofvar, float **matelm) {
  
  /*** Procédure WW ***
  ----------------------------------------------------------------
  Mise a jour de la matrice elementaire : ajout de la contribution
  d'un point de quadrature d'un element ou de son bord, pour le
  calcul d'integrales elementaires faisant intervenir le produit
  de deux fonctions de base.

  Terminologie : FK designe la transformation qui calcule l'image dans
                 l'element courant d'un point de l'element de reference

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
  matelm    : matrice élémentaire de masse actualisée
              Dimensions utiles : matelm(nbneel,nbneel)

  *** Girard Clément ***
  *** Draghici Cristian ***
  ----------------------------------------------------------------
  */  
  
  float coeff;

  for (int i=0; i<nbneel; i++) {
    coeff = eltdif*cofvar*fctbas[i];
    for (int j=0; j<nbneel; j++) {
      matelm[i][j] = matelm[i][j] + coeff*fctbas[j];
    }
  }
}
