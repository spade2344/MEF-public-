#include "fonc.h"

float A11(float* x){
  return 1.0;
}

float A22(float* x){
  return 1.0;
}

float A12(float* x){
  return 0.0;
}

float A00(float* x){
  return 0.0;
}

float BN(float* x){
  return 0.0;
}

float FOMEGA(float* x){
  return(32.0*(x[0]*(1-x[0])+x[1]*(1-x[1])));
}

float FN(float* x){
  return 0.0;
}

float UD(float* x){
  return 0.0;
}
