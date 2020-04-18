/* Procedures */
void ADWDW(int nbneel, float **valDFbase, float **invJFK, float eltdif, float **cofvar, float **matelm);
void WW(int nbneel, float *fctbas, float eltdif, float cofvar, float **matelm);
void W(int nbneel, float *fctbas, float eltdif, float cofvar, float *matelm);

/* Fonctions de calcul et impression */
void intElem(float **coorEl,int nbneel,int t, float **A, float* F);
void intAret(float **coorAr,int nbneel,int t, float **A, float* F);
void cal1Elem(int nRefFom, int nbRefD0, int* numRefD0, int nbRefD1, int* numRefD1,int nbRefF1, int* numRefF1,
	      int typEl, int nbneel, float** coorEl, int nbaret, int* nRefArE1,float** MatElem, float* SMbrElem,int* NuDElem, float* uDElem);
void impCalEl(int K, int typEl, int nbneel, float **MatElem, float *SMbrElem,
              int *NuDElem, float *uDElem);
