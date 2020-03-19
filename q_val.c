#include<stdio.h>

int q_val(int t){

  /*** Quadrature ***
  -------------------------------------------
  Donne les valeurs q correspondant a t

  t = 1 (quadr) : q=9
  t = 2 (tring) : q=3
  t = 3 (seg)   : q=3

  *** Girard Clément ***
  *** Draghici Cristian ***
  -------------------------------------------
  */
  
  switch(t){

  case 1:
    return 9;
    break;
    
  case 2:
    return 3;
    break;
    
  case 3:
    return 3;
    break;
    
  default:
    printf("*** Erreur dans la fonction qval - t différent de {1,2,3} ***\n");
    return 0;
    break;
  }
}
