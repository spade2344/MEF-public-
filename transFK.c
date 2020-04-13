#include "utils.h"
#include<stdlib.h>
#include<stdio.h>

void transFK(int nbneel, float* valFbase, float** a, float* xk){

  /*** Transformation Fk ***
  ---------------------------------------------------------
  Calcule l'image d'un point de l'élément de réf par la
  transformation Fk

  # Inputs
  t        : type de l'element
  x        : (x1,x2) 
  a        : coordonn�es des noeuds de l'�l�ment

  # Outputs
  x_K      : la transformée Fk

  *** Girard Clément ***
  *** Draghici Cristian ***
  ---------------------------------------------------------
  */

  xk[0]=0; xk[1]=0;
  for(int i=0; i<nbneel; i++){
    xk[0]=xk[0]+a[i][0]*valFbase[i];
    xk[1]=xk[1]+a[i][1]*valFbase[i];
  }
}  
