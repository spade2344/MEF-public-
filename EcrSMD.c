#include<stdio.h>
#include<stdlib.h>

void EcrSMD(int NbLign, int NbCoef, float* secmbr, int* nuddir,
            float* valdir, int* AdPrCoefLi, float* Matrice, int* NumCol,
            int* AdSuccLi, char* nomfic){


  FILE* fic = fopen(nomfic, "wb");
  if (fic == NULL){
    printf("Ouverture du fichier impossible !\n");
    exit(1);
  }

  /* Ecriture dans le fichier */

  fwrite(&NbLign, sizeof(int), 1, fic );
  fwrite( secmbr, sizeof(float), NbLign, fic );
  fwrite( nuddir, sizeof(int), NbLign, fic );
  fwrite( valdir, sizeof(float), NbLign, fic );
  fwrite( AdPrCoefLi, sizeof(int), NbLign, fic );
  fwrite( Matrice, sizeof(float), NbLign+NbCoef, fic );
  fwrite( NumCol, sizeof(int), NbCoef, fic );
  fwrite( AdSuccLi, sizeof(int), NbCoef, fic );

  fclose(fic);

}
