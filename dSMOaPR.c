#include<stdio.h>

void dSMOaPR(int NbLign, int* AdPrCoefLi, float* Matrice, int* NumCol,
	     int* Profil, float* MatProf){

  int nbcoef=0;
  int nbcoeflSMO;
  int ind;
  MatProf[0]=Matrice[0];

  for(int i=0; i<NbLign-1; i++){
    MatProf[i+1]=Matrice[i+1];
    nbcoeflSMO=AdPrCoefLi[i+1]-AdPrCoefLi[i];
    if(nbcoeflSMO==0){
      Profil[i]=0;
    }else{
      Profil[i]=nbcoef+1;
      for(int j=0; j<nbcoeflSMO; j++){
       ind =NbLign+Profil[i]-1+NumCol[AdPrCoefLi[i]+j-1]-
	 NumCol[AdPrCoefLi[i]-1];
	MatProf[ind]=Matrice[NbLign+AdPrCoefLi[i]+j-1];
      }
      nbcoef=nbcoef+i+2-NumCol[AdPrCoefLi[i]-1];
    }

  }
  Profil[NbLign-1]=nbcoef+1;

  for(int i=1; i<NbLign+1; i++){
    if(Profil[NbLign-i]==0){
      Profil[NbLign-i]=Profil[NbLign-i+1];
    }
  }



}
