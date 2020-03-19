#include "utils.h"
#include<stdlib.h>
#include<stdio.h>

void ppquad(float* omega, float** x, int t){

  /*** Quadrature ***
  ---------------------------------------------------------
  Donne les poids et points de quadrature sous forme
  d'un couple {omega,x} en fonction du type t de l'element

  # Inputs
  t     : type de l'element

  # Outputs
  omega : poids de quadrature
  x     : points de quadrature

  *** Girard Clément ***
  *** Draghici Cristian ***
  ---------------------------------------------------------
  */
  
  switch(t){
    
  case 1:
    /* Poids omega */
    for(int i=0; i<4; i++){
      omega[i]=1.f/36;
    }
    for(int i=4; i<8; i++){
      omega[i]=1./9;
    }
    omega[8]=4./9;
    
    /* Points x */
    x[0][0]=1;    x[0][1]=0;
    x[1][0]=1;    x[1][1]=1;
    x[2][0]=0;    x[2][1]=1;
    x[3][0]=0;    x[3][1]=0;
    x[4][0]=1;    x[4][1]=0.5;
    x[5][0]=0.5;  x[5][1]=1;
    x[6][0]=0;    x[6][1]=0.5;
    x[7][0]=0.5;  x[7][1]=0;
    x[8][0]=0.5;  x[8][1]=0.5;
    break;
    
  case 2:
    /* Poids omega */
    for(int i=0; i<3; i++){
      omega[i]=1./6;
    }

    /* Points x */
    x[0][0]=0.5;  x[0][1]=0.5;
    x[1][0]=0;    x[1][1]=0.5;
    x[2][0]=0.5;  x[2][1]=0;
    break;
    
  case 3:
    /* Poids omega */
    omega[0]=1./6; omega[1]=1./6; omega[2]=2./3;

    /* Points x */
    x[0][0]=1; x[1][0]=0; x[2][0]=0.5;
    break;
    
  default:
      printf("*** Erreur dans la fonction ppquad - t différent de {1,2,3} ***\n");
      break;
  }


}
