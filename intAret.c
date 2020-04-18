#include "calele.h"
#include "utils.h"
#include "fonc.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void intAret(float **coorAr,int nbneel,int t, float **A, float* F){
	
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
  int nbpts=q_val(t);
  float **x_q_chap=alloctab(nbpts,2);
  float *x_q=malloc(2*sizeof(float));
  float *omega=malloc(nbpts*sizeof(float));
  float **JFK=alloctab(2,1);
  float *fctbas=malloc(nbneel*sizeof(float));
  float **Dfctbas=alloctab(nbneel,1);
  float eltdif;
  float cofvar; float cofv3;
  
  ppquad(omega,x_q_chap,t);
  
  for(int q=0; q<nbpts; q++){   
    /* WW */
    calFbase(t,x_q_chap[q],fctbas);
    transFK(nbneel,fctbas,coorAr,x_q);
    calDerFbase(t,x_q_chap[q],Dfctbas);
    
    matJacob(nbneel,1,Dfctbas,coorAr,JFK);
    
    eltdif=omega[q]*sqrtf(JFK[0][0]*JFK[0][0]+JFK[1][0]*JFK[1][0]);
    cofvar=BN(x_q);
    WW(nbneel,fctbas,eltdif,cofvar,A);
	
    /* W */
    cofv3=FN(x_q);
    W(nbneel,fctbas,eltdif,cofv3,F);
    
  }
  freetab(x_q_chap);
  free(x_q);
  free(omega);
  freetab(JFK);
  free(fctbas);
  freetab(Dfctbas);

}
