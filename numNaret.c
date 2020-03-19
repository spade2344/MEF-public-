#include "utils.h"
#include<stdlib.h>
#include<stdio.h>


void numNaret(int t,int num_arete,int* tab_noeuds){

  /*** Définition des arêtes ***
  ---------------------------------------------------------
  Renovie la liste des numéros (locaux) des noeuds 
  situés sur une arête de numéro donné sur l'él de réf
  de type t

  # Inputs
  t           : type de l'element
  num_arete   : numero de l'arete 

  # Outputs
  tab_noeuds  : tabl des noeuds

  *** Girard Clément ***
  *** Draghici Cristian ***
  ---------------------------------------------------------
  */
  
  tab_noeuds[0]=num_arete;
  if(num_arete+1==5-t)
	tab_noeuds[1]=5-t;
  else
    tab_noeuds[1]=(num_arete+1)%(5-t);
}
