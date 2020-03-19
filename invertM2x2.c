#include "utils.h"
#include<stdlib.h>
#include<stdio.h>

void invertM2x2(float** M, float* Det, float** Inv){

  /*** Inverse de la jacobienne ***
  ---------------------------------------
  # Inputs
  M     : JFk

  # Outputs
  Det   : determinant 
  Inv   : inverse de JFk

  *** Girard Clément ***
  *** Draghici Cristian ***
  ---------------------------------------
  */
  
  /* Determinant de JFk */
  *Det = M[0][0]*M[1][1] - M[0][1]*M[1][0];
   
  /* Inverse de JFk */
  float h;
  h = 1.0/(*Det);

  Inv[0][0] = M[1][1]*h;
  Inv[0][1] = -M[0][1]*h;
  Inv[1][0] = -M[1][0]*h;
  Inv[1][1] = M[0][0]*h;
    
}
