#include "utils.h"
#include<stdlib.h>
#include<stdio.h>

void calFbase(int t, float* x, float* valFbase){

  /*** Fonctions de base ***
  ---------------------------------------------------------
  Calcule la valeur en un point des n fonctions de base
  associées à l'élément de réf de type t

  # Inputs
  t        : type de l'element
  x        : (x1,x2) 

  # Outputs
  valFbase : fonctions de base w

  *** Girard Clément ***
  *** Draghici Cristian ***
  ---------------------------------------------------------
  */

  switch(t){

  case 1:
    valFbase[0]=x[0]-x[0]*x[1];
    valFbase[1]=x[0]*x[1];
    valFbase[2]=x[1]-x[0]*x[1];
    valFbase[3]=1-x[0]-x[1]+x[0]*x[1];
    break;
    
  case 2:
    valFbase[0]=x[0];
    valFbase[1]=x[1];
    valFbase[2]=1-x[0]-x[1];
    break;
    
  case 3:
    valFbase[0]=x[0];
    valFbase[1]=1-x[0];
    break;
    
  default:
    printf("*** Erreur dans la fonction calFbase - t différent de {1,2,3} ***\n");
    break;

  }

}
