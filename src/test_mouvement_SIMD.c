#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "nrdef.h"
#include "nrutil.h"
#include "vnrdef.h"
#include "vnrutil.h"
#include "mouvement_SIMD.h"
#include "test_mouvement_SIMD.h"
#include "mymacro.h"

/* ------------------------------------------------------------------------------- */
void MLoadPGM_vui8matrix(char *filename, int nrl, int nrh, int ncl, int nch, vuint8 **m)
/* ------------------------------------------------------------------------------- */
{
    /* cette version ne lit plus que le type P5 */

    int height, width, gris;
    FILE *file;

    char *buffer;
    int i;

    buffer = (char*) calloc(80, sizeof(char));
    /* ouverture du fichier */
    file = fopen(filename,"rb");
    if (file==NULL)
        nrerror("ouverture du fichier impossible\n");
    //nrerror("ouverture du fichier %s impossible\n", filename);

    /* lecture de l'entete du fichier pgm */
    readitem(file, buffer);
    /*fscanf(fichier, "%s", buffer);*/

    if(strcmp(buffer, "P5") != 0)
        nrerror("entete du fichier %s invalide\n");
    //nrerror("entete du fichier %s invalide\n", filename);

    width  = atoi(readitem(file, buffer));
    height = atoi(readitem(file, buffer));
    gris   = atoi(readitem(file, buffer));

    for(i=0; i<height; i++) {
        if( !fread(&(m[i][0]), sizeof(vuint8), width/16, file) )// sizeof(vuint8) = sizeof(uint8)*16
		{
			printf("ERROR LOAD PGM\n");
		}
    }

    fclose(file);
    free(buffer);
}

/* ----------------------------------------------------------------------------------- */
void SavePGM_vui8matrix(vuint8 **m, int nrl, int nrh, int ncl, int nch, char *filename)
/* ----------------------------------------------------------------------------------- */
{
  int nrow = nrh-nrl+1;
  int ncol = nch-ncl+1;

  char buffer[80];

  FILE *file;
  int  i;

  file = fopen(filename, "wb");
  if (file == NULL)
    //nrerror("ouverture du fichier %s impossible dans SavePGM_bmatrix\n", filename);
    nrerror("ouverture du fichier %s impossible dans SavePGM_ui8matrix\n");

  /* enregistrement de l'image au format rpgm */

  sprintf(buffer,"P5\n%d %d\n255\n",ncol, nrow);
  fwrite(buffer,strlen(buffer),1,file);
  for(i=nrl; i<=nrh; i++)
    fwrite(&(m[i][0]), sizeof(vuint8), ncol/16, file);

  /* fermeture du fichier */
  fclose(file);
}

void copy_vui8matrix_vui8matrix(vuint8 **X, int i0, int i1, int j0, int j1, vuint8 **Y)
/* ----------------------------------------------------------------------------- */
{
    int i, j;
	vuint8 aux;

    for(i=i0; i<=i1; i++) {
        for(j=j0; j<=j1; j++) {
			aux = _mm_load_si128(&X[i][j]);
			_mm_store_si128(&Y[i][j], aux);
            // Y[i][j] = X[i][j];
        }
    }
}

void test_mouvement_SIMD()
{
	char *fname0 = (char*)malloc(sizeof(char*) * 16);
	char *fname1 = (char*)malloc(sizeof(char*) * 16);
	char *outfile= (char*)malloc(sizeof(char*) * 22);
	int aux;
	strcpy(fname0, "img/car_3000.pgm");
	strcpy(fname1, "img/car_3001.pgm");
	strcpy(outfile,"output/output_e001.pgm");

	vuint8 **I0 = vui8matrix(0, HAUT, 0, LARG);
	vuint8 **I1 = vui8matrix(0, HAUT, 0, LARG);
	vuint8 **M0 = vui8matrix(0, HAUT, 0, LARG);
	vuint8 **M1 = vui8matrix(0, HAUT, 0, LARG);
	vuint8 **O1 = vui8matrix(0, HAUT, 0, LARG);
	vuint8 **V0 = vui8matrix(0, HAUT, 0, LARG);
	vuint8 **V1 = vui8matrix(0, HAUT, 0, LARG);
	vuint8 **E1 = vui8matrix(0, HAUT, 0, LARG);
	uint8 **uE1 =  ui8matrix(0, HAUT, 0, LARG);

	// MLoadPGM_vui8matrix(fname0, 0, HAUT, 0, LARG, I0);
	// MLoadPGM_vui8matrix(fname1, 0, HAUT, 0, LARG, I1);
	//
	// SigmaDelta_step0_SIMD(M0, I0, V0, HAUT, LARG);
	// SigmaDelta_1step_SIMD(M1, M0, I1, HAUT, LARG);
	// SigmaDelta_2step_SIMD(O1, M1, I1, HAUT, LARG);
	// SigmaDelta_3step_SIMD(V1, V0, O1, HAUT, LARG);
	// SigmaDelta_4step_SIMD(O1, V1, E1, HAUT, LARG);
	//
	// SavePGM_vui8matrix(E1, 0, HAUT, 0, LARG, outfile);

	MLoadPGM_vui8matrix(fname0, 0, HAUT, 0, LARG, I0);

	for(int i = 2; i <= 200; i++)
	{
		// printf("iter %d\n", i);
		// printf("fname0 : %s\n", fname0);
		// printf("fname1 : %s\n", fname1);
		// printf("outfile: %s\n", outfile);
		MLoadPGM_vui8matrix(fname1, 0, HAUT, 0, LARG, I1);
		SIGMADELTA_SIMD(I0, I1, M0, M1, O1, V0, V1, E1);
		SavePGM_vui8matrix(E1, 0, HAUT, 0, LARG, outfile);
		COPIER_MATRICES_SIMD(I1, I0);
		COPIER_MATRICES_SIMD(M1, M0);
		COPIER_MATRICES_SIMD(V1, V0);
		strcpy(fname0, fname1);
		aux = (fname0[9]-'0')*100 + (fname0[10]-'0')*10 + (fname0[11]-'0') + 1;
		fname1[9] = outfile[15] = aux / 100 + '0';
		fname1[10] = outfile[16] = (aux / 10) % 10 + '0';
		fname1[11] = outfile[17] = aux % 10 + '0';
	}

	free_vui8matrix(I0, 0, HAUT, 0, LARG);
	free_vui8matrix(I1, 0, HAUT, 0, LARG);
	free_vui8matrix(M0, 0, HAUT, 0, LARG);
	free_vui8matrix(M1, 0, HAUT, 0, LARG);
	free_vui8matrix(O1, 0, HAUT, 0, LARG);
	free_vui8matrix(V0, 0, HAUT, 0, LARG);
	free_vui8matrix(V1, 0, HAUT, 0, LARG);
	free_vui8matrix(E1, 0, HAUT, 0, LARG);
	free_ui8matrix(uE1, 0, HAUT, 0, LARG);
}
