#include "calele.h"
#include "utils.h"
#include "fonc.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void intAret(float **coorAr,int t, float **A, float* F){
	
  /*** Procédure intAret ***
  ---------------------------------------------------------
  Regroupe les calculs des intégrales d'arete par les
  procédures WW et W.

  # Inputs
  t         : type de l'élément
  coorAr    : tableau contenant les coordonnées des noeuds
              d'une arete de numéro donné de l'élément
              courant K

  # Outputs
  A         : matrice élémentaire d'arete actualisée
  F         : vecteur élémentaire d'arete actualisé

  *** Girard Clément ***
  *** Draghici Cristian ***
  ---------------------------------------------------------
  */	

  /* Allocation et déclaration */
  float **x_q_chap=alloctab(3,2);
  float *x_q=malloc(2*sizeof(float));
  float *omega=malloc(3*sizeof(float));
  float **JFK=alloctab(2,1);
  float *fctbas=malloc(2*sizeof(float));
  float **Dfctbas=alloctab(2,1);
  float eltdif;
  float cofvar; float cofv3;
  
  ppquad(omega,x_q_chap,t);
  
  for(int q=0; q<3; q++){
    x_q[0]=x_q_chap[q][0]*coorAr[0][0]+coorAr[1][0]*(1-x_q_chap[q][0]);
    x_q[1]=x_q_chap[q][0]*coorAr[0][1]+coorAr[1][1]*(1-x_q_chap[q][0]);
    /* WW */
    calFbase(3,x_q_chap[q],fctbas);
    calDerFbase(3,x_q_chap[q],Dfctbas);
    
    matJacob(2,1,Dfctbas,coorAr,JFK);
    
    eltdif=omega[q]*sqrtf(JFK[0][0]*JFK[0][0]+JFK[1][0]*JFK[1][0]);
    cofvar=BN(x_q);
    WW(2,fctbas,eltdif,cofvar,A);
	
    /* W */
    cofv3=FN(x_q);
    W(2,fctbas,eltdif,cofv3,F);
    
  }
  freetab(x_q_chap);
  free(x_q);
  free(omega);
  freetab(JFK);
  free(fctbas);
  freetab(Dfctbas);

}
