#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>

// Pour compiler le fichier : gcc glo2001-h18-tp1-q4-threads.c -o tp1 -lpthread
#define N 8
#define M 10
#define P 5
#define N_THREADS N*P

typedef struct {
    int  iThread;
    int Longueur;
    double Vecteur1[M];
    double Vecteur2[M];
    double *pResultat;
} ParametresThread;

/* Voici la fonction correspondant a chaque thread - à compléter */
void  *ProduitScalaire(void *data) {
    ParametresThread *pParam = (ParametresThread*)data;
    *pParam->pResultat = 0;
    int i;
    for (i = 0; i < M; i++){
    	*pParam->pResultat += pParam->Vecteur1[i] * pParam->Vecteur2[i];
    }

    pthread_exit(NULL);
}

/* Une fonction pour afficher une matrice a l'ecran */
void AfficherMatrice(double *pMatrice, int nrangees, int ncolonnes) {
    int i,j;
    printf("Matrice : \n");
    for (i=0; i<nrangees; i++) {
        for (j=0; j<ncolonnes; j++ ) {
            printf("%10.3f ",pMatrice[i*ncolonnes+j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    // Creation des deux matrices
    printf("Nous allons creer les matrice de %dx%d et %dx%d\n",N,M,M,P);
    int i,j,index;
    double G[N][M];
    double H[M][P];
    double R[N][P];

    pthread_t threads[N_THREADS];

    ParametresThread myParameters[N_THREADS];

    // Initialisation de la premiere matrice
    for (i=0;i<N;i++) {
        for (j=0; j<M; j++) {
            G[i][j] = (double)i + (double)j*0.01;
        }
    }
    AfficherMatrice(&G[0][0],N,M);

    // Initialisation de la deuxieme matrice
    for (i=0;i<M;i++) {
        for (j=0; j<P; j++) {
            H[i][j] = (double)i + (double)j*0.01;
        }
    }
    AfficherMatrice(&H[0][0],M,P);
    // Votre code de creation de thread commence ici...

    //test de la struct
    /*
    double index_test[10] = {1,1,1,1,1};
    double *ptr_test = &index_test[2];
    double v1_test[10] = {1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0};
    double v2_test[10] = {1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0};
    ParametresThread test;

    test.pResultat = ptr_test;
    test.Longueur = M;
    test.iThread = threads[0];
    for (int i = 0; i < M; i++){
    	test.Vecteur1[i] = v1_test[i];
    	test.Vecteur2[i] = v2_test[i];
    }
    */

    int n_index = 0;
    for (int i = 0; i < N_THREADS; i++){
    	myParameters[i].iThread = threads[i];
    	myParameters[i].Longueur = M;
    	int p_index = i%P;
    	if (p_index == 0 && i != 0){
    		n_index += 1;
    	}
    	myParameters[i].pResultat = &R[n_index][p_index];
    	for (int j = 0; j < M; j++){
    		myParameters[i].Vecteur1[j] = G[n_index][j];
    		myParameters[i].Vecteur2[j] = H[j][p_index];
    	}
    }

    for (int i = 0; i < N_THREADS; i++){
    	pthread_create(&threads[i], NULL, ProduitScalaire, (void *) &myParameters[i]);
    	pthread_join(threads[i], NULL);
    }


    // Et se termine essentiellement ici...
    printf("Main(): Tous les threads ont termines! On affiche la reponse...\n");
    AfficherMatrice(&R[0][0],N,P);
    exit(0);
}
