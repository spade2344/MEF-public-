#include<stdio.h>
#include<stdlib.h>
#include "utils.h"
#include "fonc.h"
#include "calele.h"
#include "forfun.h"
#include "assmb.h"
#include "syslSMO.h"
#include "sol.h"


int main(){

 int t;             /* type du maillage */
 int nbtng;         /* nbr de noeuds (n) */
 int nbtel;         /* nbr d'elements (m) */
 int nbneel;        /* nombre noeuds par element (p) */
 int nbaret;        /* nbr d'aretes par element (q) */
 float** pcoord;    /* (pointeur) coord des noeuds (n*2) */
 int** pngnel;      /* (pointeur) numeros glob des noeuds (m*p) */
 int** pnRefAr;     /* (pointeur) numeros ref associes aux aretes (taille m*q) */

 char* ficmai="d1t1_2.txt";    

 /***** Lecture des fichiers de maillage *****/

 lecfima(ficmai,&t, &nbtng,&pcoord,&nbtel,&pngnel,&nbneel,&nbaret,&pnRefAr);

 printf("nbtel = %d", nbtel);


 /***** Lecture numeros de ref et distribution sur les cotes *****/

 /* Allocation memoire et initialisation */
  float** coorEl=malloc(nbneel*sizeof(float *));
  int nRefDom = 0;          /* numero ref du domaine */
  int numRefD0[4]={1,2,3,4};      /* Dirichlet homog */
  int numRefD1[1]={-1};      /* Dirichlet non-homog */
  int numRefF1[1]={-1};    /* Neumann */
  int nbRefD0=4;            /* nombre de nRefD0 */
  int nbRefD1=0;
  int nbRefF1=0;



  /***** Procédure d'assemblage *****/

  /* Allocations et déclarations pour la fonction d'assemblage */

  int NbLign = nbtng;
  int NbCoef =2*t*NbLign;
  int* AdPrCoefLi=(int *) calloc(NbLign,sizeof(int));
  float* secmbr=(float *) calloc(NbLign, sizeof(float));
  int* nuddir=malloc(NbLign*sizeof(int));
  float* valdir=(float *) calloc(NbLign, sizeof(float));

  int* AdSuccLi=(int *) calloc((NbCoef),sizeof(int));
  float* Matrice=(float *) calloc((NbLign+NbCoef),sizeof(float));
  int* NumCol=malloc((NbCoef)*sizeof(int));

  Assemblage(t, nbtng, nbtel, nbneel, nbaret, pngnel,
				pcoord, coorEl, pnRefAr, nRefDom, numRefD0,
				numRefD1, numRefF1, nbRefD0, nbRefD1, nbRefF1,
				AdPrCoefLi, NumCol, secmbr, nuddir,
				valdir, AdSuccLi, Matrice, &NbCoef);


  /* Affichage de la matrice assemblée (prise en compte CL Dirichlet) */

  affsmd_(&NbLign,AdPrCoefLi,NumCol, AdSuccLi,Matrice,secmbr,nuddir,valdir);



/************************************************************************/


  /***** Construction de la SMO *****/

  float* secmbrO;
  int* AdPrCoefLiO;
  float* MatriceO;
  int* NumColO;

  secmbrO=(float *) calloc(NbLign, sizeof(float));
  AdPrCoefLiO=(int *) calloc(NbLign,sizeof(int));
  NbCoef = (AdPrCoefLi)[NbLign-1]-1;  
  MatriceO=(float *) calloc((NbLign+NbCoef),sizeof(float));
  NumColO=malloc((NbCoef)*sizeof(int));

  cdesse_(&NbLign, AdPrCoefLi, NumCol, AdSuccLi,
          Matrice, secmbr, nuddir, valdir,
          AdPrCoefLiO, NumColO, MatriceO, secmbrO);


  /* Affichage de la matrice assemblée SMO */

  affsmo_(&NbLign,AdPrCoefLiO,NumColO,MatriceO,secmbrO);


  /* Passage de la SMO au stockage profil */

  float* MatProf = (float *)calloc(0.5*NbLign*(NbLign+1),sizeof(float));
  int* Profil = malloc(NbLign*sizeof(int));

  dSMOaPR(NbLign, AdPrCoefLiO,MatriceO,NumColO,Profil, MatProf);


    /*** Calcul de la solution Elements finis ***/

  /* Decomposition de Cholesky */

  float* ld = malloc(NbLign*sizeof(float));
  float* ll = malloc((0.5*NbLign*(NbLign-1))*sizeof(float));
  float eps = 1e-15;


  ltlpr_(&NbLign,Profil,MatProf,&MatProf[NbLign],&eps,ld,ll);


  /* Resolution du systeme */

  float* smbc=(float *) calloc(NbLign, sizeof(float));
  float* UCAL =(float *) calloc(NbLign, sizeof(float));


  rsprl_(&NbLign,Profil,ld,ll,secmbrO,smbc);
  rspru_(&NbLign,Profil,ld,ll,smbc,UCAL);

  /* Calcul de la solution exacte */
  
  float* UEX = (float *) calloc(NbLign, sizeof(float));
  CalSol(NbLign,pcoord,UEX);
  int impfic=-1;
  

  affsol_(&NbLign,pcoord[0],UCAL,UEX,&impfic);
  

  /*** Liberation memoire ***/
  free(coorEl);
  freetab(pcoord);
  freetab(pnRefAr);
  freetab(pngnel);

  free(Matrice);
  free(AdPrCoefLi);
  free(AdSuccLi);
  free(NumCol);
  free(valdir);
  free(nuddir);
  free(secmbr);
  
  free(secmbrO);
  free(AdPrCoefLiO);
  free(MatriceO);
  free(NumColO);


}
