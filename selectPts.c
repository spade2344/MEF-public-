#include "utils.h"
#include<stdlib.h>
#include<stdio.h>

void selectPts(int nb, int num[], float* coorEns[], float* coorSel[]){

  /*** Sélection des points ***
  ---------------------------------------------------------
  Selectionne nb pts de numeros num dans coorEns
  Stockage dans coorSel

  # Inputs
  nb       : nombre pts selectionnés
  num      : tabl des numéros de pts selectionnés
  coorEns  : tabl des pts

  # Outputs
  coorSel  : tabl des pts selectionnés

  *** Girard Clément ***
  *** Draghici Cristian ***
  ---------------------------------------------------------
  */
  
  int ind;
  for(int i=0; i<nb; i++){
    ind=num[i]-1;
    coorSel[i]=coorEns[ind];
  }

}
