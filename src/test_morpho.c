#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "nrdef.h"
#include "nrutil.h"
#include "morpho.h"
#include "test_morpho.h"
#include "mymacro.h"
#include "sys/time.h"

void traitement_bord(uint8 **img, int larg, int haut)
{
	int i;

	for (i = 0; i < haut; i++) {
		img[i][-1] = img[i][0];
		img[i][haut] = img[i][haut-1];
	}

	for (i = -1; i <= larg; i++) {
		img[-1][i] = img[0][i];
		img[haut][i] = img[haut-1][i];
	}
}

void test_morpho()
{
	struct timeval t1, t2;
	double timeused;

	/* Benchmark */
	// char *fname0 = "test_img/mouvement/output.pgm";
	// uint8 **I0 = ui8matrix(-1, IMG_HEIGHT+1, -1, IMG_LENGTH+1);
	// uint8 **I1 = ui8matrix(-1, IMG_HEIGHT+1, -1, IMG_LENGTH+1);

	// MLoadPGM_ui8matrix(fname0, 0, IMG_HEIGHT-1, 0, IMG_LENGTH-1, I0);
	// traitement_bord(I0, IMG_HEIGHT, IMG_LENGTH);

	// gettimeofday(&t1, NULL);
	// erosion(I0, I1, IMG_HEIGHT, IMG_LENGTH);
	// gettimeofday(&t2, NULL);
	// timeused = (t2.tv_sec - t1.tv_sec) + (double)(t2.tv_usec - t1.tv_usec)/1000000.0;
	// printf("Temps pour 1 erosion: %f s\n", timeused);
	// SavePGM_ui8matrix(I1, 0, IMG_HEIGHT-1, 0, IMG_LENGTH-1, "test_img/morpho/erosion1.pgm");
	// traitement_bord(I1, IMG_HEIGHT, IMG_LENGTH);

	// gettimeofday(&t1, NULL);
	// dilatation(I1, I0, IMG_HEIGHT, IMG_LENGTH);
	// gettimeofday(&t2, NULL);
	// timeused = (t2.tv_sec - t1.tv_sec) + (double)(t2.tv_usec - t1.tv_usec)/1000000.0;
	// printf("Temps pour 1 dilatation: %f s\n", timeused);
	// SavePGM_ui8matrix(I0, 0, IMG_HEIGHT-1, 0, IMG_LENGTH-1, "test_img/morpho/dilatation1.pgm");

	// free_ui8matrix(I0, -1, IMG_HEIGHT+1, -1, IMG_LENGTH+1);
	// free_ui8matrix(I1, -1, IMG_HEIGHT+1, -1, IMG_LENGTH+1);

	/* Test unitaire avec des images de 5*5*/
  	uint8 **I0 = ui8matrix(-1, 5, -1, 5);
	uint8 **I1 = ui8matrix(-1, 5, -1, 5);

	// Initialisation en 0
	for (int i = -1; i <= 5; i++) {
		for (int j = -1; j <= 5; j++) {
			I0[i][j] = 0;
		}
	}

	for (int i = 0; i <=4; i++) {
		I0[1][i] = 255;
		I0[2][i] = 255;
		I0[3][i] = 255;
	}

	printf("Test unitaire pour morpho\n");
	display_ui8matrix(I0, 0, 4, 0, 4, " [%03d] ", "I0");
	erosion(I0, I1, 5, 5);
	display_ui8matrix(I1, 0, 4, 0, 4, " [%03d] ", "erosion");
	dilatation(I0, I1, 5, 5);
	display_ui8matrix(I1, 0, 4, 0, 4, " [%03d] ", "dilatation");
	
	free_ui8matrix(I0, -1, 5, -1, 5);
  	free_ui8matrix(I1, -1, 5, -1, 5);
}
