void Assemblage(int t, int nbtng, int nbtel, int nbneel, int nbaret, int** pngnel,
				float** pcoord, float** coorEl, int** pnRefAr, int nRefDom, int* numRefD0,
				int* numRefD1, int* numRefF1, int nbRefD0, int nbRefD1, int nbRefF1,
				int* AdPrCoefLi, int* NumCol, float* secmbr, int* nuddir,
				float* valdir, int* AdSuccLi, float* Matrice,int* NbCoef);
void EcrSMD(int NbLign, int NbCoef, float* secmbr, int* nuddir,
            float* valdir, int* AdPrCoefLi, float* Matrice, int* NumCol,
            int* AdSuccLi, char* nomfic);
void LecSMD(int* NbLign1, float** secmbr1, int** nuddir1,
            float** valdir1, int** AdPrCoefLi1, float** Matrice1, int** NumCol1,
            int** AdSuccLi1, char* nomfic);
