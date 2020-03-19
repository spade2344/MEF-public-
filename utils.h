void etiqAr(int type1, int n1, int n2, int nrefdom, const int *nrefcot, int nbtel, int nbaret, int **nRefAr);
int lecfima(char *ficmai, int *type1, int *nbtng, float ***pcoord, int *nbtel, int ***pngnel, int *nbneel, int *nbaret, int ***pnRefAr);

/* Fonctions */
void ppquad(float* omega, float** x, int t);
int q_val(int t);
void calFbase(int t, float* x, float* valFbase);
void calDerFbase(int t, float* x, float** valFbase);
void transFK(int nbneel, float* valFbase, float** a, float* xk);
void matJacob(int nbneel, int d,float** valDFbase, float** a, float** JFK);
void invertM2x2(float** M, float* Det, float** Inv);
void numNaret(int t,int num_arete,int* tab_noeuds);
void selectPts(int nb, int num[], float* coorEns[], float* coorSel[]);

/* Allocation */
float **alloctab(int dim1, int dim2);
void freetab(void *ptr);
int **alloctab_int(int dim1, int dim2);
