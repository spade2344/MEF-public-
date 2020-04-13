#include<stdio.h>
#include "sol.h"


void CalSol(int NbLign, float** coord, float* UEX){

  for (int i=0; i<NbLign; i++){
    UEX[i]  = solex(coord[i]);
  }

}
