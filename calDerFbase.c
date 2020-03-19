#include "utils.h"
#include<stdlib.h>
#include<stdio.h>


void calDerFbase(int t, float* x, float** valDFbase){

  /*** Dérivée des fonctions de base ***
  ----------------------------------------------------------------
  Calcule la valeur en un point des dérivées des n fonctions
  de base associées à l'élément de réf de type t

  # Inputs
  t           : type de l'element
  x           : (x1,x2) 

  # Outputs
  valDFbase   : dérivée des fonctions de base w

  *** Girard Clément ***
  *** Draghici Cristian ***
  ----------------------------------------------------------------
*/

  switch(t){

  case 1:
    valDFbase[0][0]=1-x[1];		valDFbase[0][1]=-x[0];
    valDFbase[1][0]=x[1];		valDFbase[1][1]=x[0];
    valDFbase[2][0]=-x[1];		valDFbase[2][1]=1-x[0];
    valDFbase[3][0]=-1+x[1];		valDFbase[3][1]=-1+x[0];
    break;
    
  case 2:
    valDFbase[0][0]=1;			valDFbase[0][1]=0;
    valDFbase[1][0]=0;			valDFbase[1][1]=1;
    valDFbase[2][0]=-1;			valDFbase[2][1]=-1;
    break;
    
  case 3:
    valDFbase[0][0]=1;
    valDFbase[1][0]=-1;
    break;
    
  default:
	printf("*** Erreur dans la fonction calDerFbase - t différent de {1,2,3} ***\n");
    break;

  }

}
