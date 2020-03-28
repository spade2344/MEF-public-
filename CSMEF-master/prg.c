#include<stdio.h>
#include<stdlib.h>
#include "utils.h"
#include "fonc.h"
#include "calele.h"
#include "forfun.h"
#include "assmb.h"
#include "syslSMO.h"


int main(){

 int t;             /* type du maillage */
 int nbtng;         /* nbr de noeuds (n) */
 int nbtel;         /* nbr d'elements (m) */
 int nbneel;        /* nombre noeuds par element (p) */
 int nbaret;        /* nbr d'aretes par element (q) */
 float** pcoord;    /* (pointeur) coord des noeuds (n*2) */
 int** pngnel;      /* (pointeur) numeros glob des noeuds (m*p) */
 int** pnRefAr;     /* (pointeur) numeros ref associes aux aretes (taille m*q) */

 char* ficmai="car3x3t_3";	/* car1x1t_1 , car3x3t_3 */

 int i; int j; 					   /* itérations */

 /***** Lecture des fichiers de maillage *****/

 lecfima(ficmai,&t, &nbtng,&pcoord,&nbtel,&pngnel,&nbneel,&nbaret,&pnRefAr);

 /* Affichage des tableaux */
 printf("%d \n",nbtng); 		           /* affichage de nb */
  for(i=0; i<nbtng; i++){
    printf("%f %f \n", pcoord[i][0], pcoord[i][1]);
  }

  printf("%d %d %d %d \n", nbtel,t,nbneel,nbaret); /* affichate de m p t q */

  /* Affichage de pngnel */
  for(i=0;i<nbtel;i++){
    for(j=0; j<nbneel; j++){
      printf("%d ",pngnel[i][j]);
    }
  printf("\n");
  }

  /* Affichage de pnRefAr */
  for(i=0;i<nbtel;i++){
    for(j=0; j<nbaret; j++){
      printf("%d ",pnRefAr[i][j]);
    }
  printf("\n");
  }


 /***** Lecture numeros de ref et distribution sur les cotes *****/

 /* Allocation memoire et initialisation */
  float** coorEl=malloc(nbneel*sizeof(float *));
  int nRefDom = 0;          /* numero ref du domaine */
  int numRefD0[1]={1};      /* Dirichlet homog */
  int numRefD1[1]={4};      /* Dirichlet non-homog */
  int numRefF1[2]={2,3};    /* Neumann */
  int nbRefD0=1;            /* nombre de nRefD0 */
  int nbRefD1=1;
  int nbRefF1=2;




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


  /* affsmd_(&NbLign,AdPrCoefLi,NumCol, AdSuccLi,Matrice,secmbr,nuddir,valdir); */


  /***** EcrSMD - sauvegarde données sous la forme d'un fichier binaire *****/

  EcrSMD(NbLign, NbCoef, secmbr, nuddir, valdir,
	  AdPrCoefLi, Matrice, NumCol, AdSuccLi, "SMD_bin.txt");


  /***** LecSMD - lecture des données et affichage *****/

  int NbLign1;
  int* AdPrCoefLi1;
  float* secmbr1;
  int* nuddir1;
  float* valdir1;
  float *Matrice1;
  int* NumCol1;
  int* AdSuccLi1;

  /* Lecture du fichier binaire*/

  LecSMD(&NbLign1, &secmbr1, &nuddir1, &valdir1,
	 &AdPrCoefLi1, &Matrice1, &NumCol1, &AdSuccLi1,"SMD_bin.txt");

  /* Affichage de la matrice assemblée (prise en compte CL Dirichlet) */

  affsmd_(&NbLign1,AdPrCoefLi1,NumCol1, AdSuccLi1,Matrice1,secmbr1,nuddir1,valdir1);


  /*** Libération mémoire ***/
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

  free(Matrice1);
  free(AdPrCoefLi1);
  free(AdSuccLi1);
  free(NumCol1);
  free(valdir1);
  free(nuddir1);
  free(secmbr1);




/************************************************************************/




  /***** Construction de la SMO *****/

  float* secmbrO;
  int* AdPrCoefLiO;
  float* MatriceO;
  int* NumColO;

  dSMDaSMO(&secmbrO, &AdPrCoefLiO,& MatriceO, &NumColO, "SMD_bin.txt", "SMO_bin.txt");



  /***** LecSMO - Lecture fichier binaire SMO ***/

  int NbLignO1;
  int* AdPrCoefLiO1;
  float* secmbrO1;
  int NbCoefO1;
  float* MatriceO1;
  int* NumColO1;

  LecSMO(&NbLignO1, &NbCoefO1, &secmbrO1, &AdPrCoefLiO1,
         &MatriceO1, &NumColO1,"SMO_bin.txt");


  /* Affichage de la matrice assemblée SMO */

  affsmo_(&NbLignO1,AdPrCoefLiO1,NumColO1,MatriceO1,secmbrO1);


  /*** Liberation memoire ***/
  free(secmbrO);
  free(AdPrCoefLiO);
  free(MatriceO);
  free(NumColO);

  free(MatriceO1);
  free(AdPrCoefLiO1);
  free(NumColO1);
  free(secmbrO1);



}
