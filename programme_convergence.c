#include<stdio.h>
#include<stdlib.h>
#include "utils.h"
#include "fonc.h"
#include "calele.h"
#include "forfun.h"
#include "assmb.h"
#include "syslSMO.h"
#include "sol.h"
#include <math.h>


int main(){

  int nbiter=7;

  float a=0;
  float b=1;
  float c=0;
  float d=1;

  int t=2; /* type de maillage (t=1 => quadrangles ; t=2 => triangles) */

  for(int l=0; l<nbiter; l++){

    /* Cr�ation du fichier de maillage */
    

    int n1=pow(2,l+1); /* nombre de noeuds horizontaux */
    int n2=n1; /* nombre de noeuds verticaux */ 
    int n=n1*n2; /* nombre de noeuds au total */

    float h1=(b-a)/(n1-1); 
    float h2=(d-c)/(n2-1);


    FILE* fic=fopen("fic_m", "w");

    /*Ecriture du n*/
    fprintf(fic,"%d \n",n);

    /* Ecriture des coordonnees des n noeuds */
    for(int i=0; i<n2; i++){
      for(int j=0; j<n1; j++){
	float xi = a + j*h1;
	float yi = c + i*h2;
	fprintf(fic, "%f %f \n", xi, yi);
      }

    } 

    /* Ecriture de m t p q*/

    int m=t*(n1-1)*(n2-1);
    int p=5-t;
    int q=p;

    fprintf(fic, "%d %d %d %d \n", m,t,p,q);

  
    /* Creation du tableau nRefAr */
  
    int  nrefdom=0;
    const int nrefcot[4]={1,2,3,4};
    int** nRefAr;
    nRefAr=alloctab_int(m,q);
    etiqAr(t,n1,n2,nrefdom,&nrefcot[0],m,q,nRefAr);



    /* Ecriture des noeuds de chaque element + étiquettes */
    int ctr=0;
    if(t==1){
      for (int i=0; i<n2-1; i++){
	for(int j=0; j<n1-1; j++){
	  fprintf(fic,"%d %d %d %d ",i*n1+j+1,i*n1+j+2,i*n1+j+2+n1,i*n1+j+1+n1);
	  for(int k=0; k<q; k++){
	    fprintf(fic,"%d ",(int)nRefAr[ctr][k]);
	  }
	  ctr++;
	  fprintf(fic, "\n");
	
	}
      }
    }

    else{
      for (int i=0; i<n2-1; i++){
	for(int j=0; j<n1-1; j++){
	  fprintf(fic,"%d %d %d ",i*n1+j+2,i*n1+j+1+n1,i*n1+j+1);
	  for(int k=0; k<q; k++){
	    fprintf(fic,"%d ",(int)nRefAr[ctr][k]);
	  }
	  ctr++;
	  fprintf(fic,"\n");
	  fprintf(fic,"%d %d %d ",i*n1+j+1+n1,i*n1+j+2,i*n1+j+2+n1);
	  for(int k=0; k<q; k++){
	    fprintf(fic,"%d ",(int)nRefAr[ctr][k]);
	  }
	  ctr++;
	  fprintf(fic, "\n");
	}
      }
    }

    fclose(fic);
    

    int nbtng;         /* nbr de noeuds (n) */
    int nbtel;         /* nbr d'elements (m) */
    int nbneel;        /* nombre noeuds par element (p) */
    int nbaret;        /* nbr d'aretes par element (q) */
    float** pcoord;    /* (pointeur) coord des noeuds (n*2) */
    int** pngnel;      /* (pointeur) numeros glob des noeuds (m*p) */
    int** pnRefAr;     /* (pointeur) numeros ref associes aux aretes (taille m*q) */

    char* ficmai="fic_m";    

    /***** Lecture des fichiers de maillage *****/
   
    lecfima(ficmai,&t, &nbtng,&pcoord,&nbtel,&pngnel,&nbneel,&nbaret,&pnRefAr);


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

    /*  affsmd_(&NbLign,AdPrCoefLi,NumCol, AdSuccLi,Matrice,secmbr,nuddir,valdir); */



    /************************************************************************/


    /***** Construction de la SMO *****/

    float* secmbrO;
    int* AdPrCoefLiO;
    float* MatriceO;
    int* NumColO;

    secmbrO=(float *) calloc(2*NbLign, sizeof(float));
    AdPrCoefLiO=(int *) calloc(2*NbLign,sizeof(int));
    NbCoef = (AdPrCoefLi)[NbLign-1]-1;
    MatriceO=(float *) calloc(2*(NbLign+NbCoef),sizeof(float));
    NumColO=malloc(2*(NbCoef)*sizeof(int));


    cdesse_(&NbLign, AdPrCoefLi, NumCol, AdSuccLi,
	    Matrice, secmbr, nuddir, valdir,
	    AdPrCoefLiO, NumColO, MatriceO, secmbrO);
   

  
    /* Affichage de la matrice assemblée SMO */

    /* affsmo_(&NbLign,AdPrCoefLiO,NumColO,MatriceO,secmbrO); */


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
    int impfic=1;
  

     affsol_(&NbLign,pcoord[0],UCAL,UEX,&impfic); 
  

    /*** Liberation memoire ***/

    freetab(nRefAr);
    
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

}
