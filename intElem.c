#include "calele.h"
#include "utils.h"
#include "fonc.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void intElem(float **coorEl,int nbneel,int t, float **A, float* F){

  /*** Procédure intElem ***
  ---------------------------------------------------------
  Regroupe les calculs des intégrales de surface par les
  procédures ADWDW, WW et W.

  # Inputs
  t         : type de l'élément
  nbneel    : nombre de noeuds de l'élément
  coorEl    : tableau contenant les coordonnées des nbneel
              noeuds de l'élément courant K

  # Outputs
  A         : matrice élémentaire de surface actualisée
  F         : vecteur élémentaire de surface actualisé

  *** Girard Clément ***
  *** Draghici Cristian ***
  ---------------------------------------------------------
  */

  /* Allocation et déclaration */
  float **x_q_chap=alloctab(nbneel,2);
  float *x_q=malloc(2*sizeof(float));
  float *omega=malloc(nbneel*sizeof(float));
  float **JFK=alloctab(2,2);
  float **invJFK=alloctab(2,2);
  float *fctbas=malloc(nbneel*sizeof(float));
  float **Dfctbas=alloctab(nbneel,2);
  float det;
  float eltdif;
  float cofvar;     float **cofv2=alloctab(2,2);		float cofv3;
  
  ppquad(omega,x_q_chap,t);
   
  for(int q=0; q<nbneel; q++){
    calFbase(t,x_q_chap[q],fctbas);
    transFK(t,fctbas,coorEl,x_q);
    
    /* WW */
   
    calDerFbase(t,x_q_chap[q],Dfctbas);
    matJacob(nbneel,2,Dfctbas,coorEl,JFK);
    invertM2x2(JFK, &det, invJFK);
    eltdif=omega[q]*fabs(det);
    cofvar=A00(x_q);
    WW(nbneel,fctbas,eltdif,cofvar,A);

    
    /* ADWDW */
    cofv2[0][0]=A11(x_q); cofv2[0][1]=A12(x_q);
    cofv2[1][0]=A12(x_q); cofv2[1][1]=A22(x_q);
    
    ADWDW(nbneel,Dfctbas,invJFK,eltdif,cofv2,A);

	/* W */
    cofv3=FOMEGA(x_q);
    W(nbneel,fctbas,eltdif,cofv3,F);
    
  }
  freetab(x_q_chap);
  free(x_q);
  free(omega);
  freetab(JFK);
  freetab(invJFK);
  free(fctbas);
  freetab(Dfctbas);
  freetab(cofv2);

}
