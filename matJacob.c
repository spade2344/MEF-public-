#include "utils.h"
#include<stdlib.h>
#include<stdio.h>

void matJacob(int nbneel, int d, float** valDFbase, float** a, float** JFK){

  /*** Matrice jacobienne ***
  ---------------------------------------------------------
  Calcule la jacobienne de Fk

  # Inputs
  nbneel        : nombre de noeuds de l'élément
  d             : dimension 
	  		      (2 si triangles ou quadrangles ; 1 si segment)
  valDFbase     : valeurs des dérivées des fonctions de base en x
  a             : coordonnées des sommets de l'élément

  # Outputs
  JFk           : la matrice Jacob

  *** Girard Clément ***
  *** Draghici Cristian ***
  ---------------------------------------------------------
*/
  
 for(int i=0; i<2; i++){
   for(int j=0; j<d;j++){
     JFK[i][j]=0;
   }
 }
 
 for(int i=0; i<2; i++){
   for(int j=0; j<d; j++){
     for(int k=0; k<nbneel;k++){
       JFK[i][j]=JFK[i][j]+a[k][i]*valDFbase[k][j];
     }
   }
  }
}
