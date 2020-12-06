#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "nrdef.h"
#include "nrutil.h"
#include "mouvement.h"
#include "test_mouvement.h"
#include "mymacro.h"
#include "myutils.h"
#include "sys/time.h"

void test_mouvement()
{
	struct timeval t1, t2;
	double timeused;
	char *fname0 = "test_img/test1.pgm";
	char *fname1 = "test_img/test2.pgm";
	char *outfile = "test_img/mouvement/output.pgm";

  	/* Test unitaire avec des images de 5*5*/
  	uint8 **I0 = ui8matrix(0, 4, 0, 4);
	uint8 **I1 = ui8matrix(0, 4, 0, 4);
	uint8 **M0 = ui8matrix(0, 4, 0, 4);
	uint8 **M1 = ui8matrix(0, 4, 0, 4);
	uint8 **O1 = ui8matrix(0, 4, 0, 4);
	uint8 **V0 = ui8matrix(0, 4, 0, 4);
	uint8 **V1 = ui8matrix(0, 4, 0, 4);
	uint8 **E1 = ui8matrix(0, 4, 0, 4);

	// Initialisation en 0
	for (int i = 0; i <= 4; i++) {
		for (int j = 0; j <= 4; j++) {
			I0[i][j] = I1[i][j] = 0;
		}
	}

	for (int i = 0; i <=4; i++) {
		I0[2][i] = 128;
		I1[3][i] = 16;
	}

	printf("\nTEST UNITAIRE MOUVEMENT 2\n\n");
	SigmaDelta_step0(M0, I0, V0, 4, 4);
	SigmaDelta_1step(M1, M0, I1, O1, V1, V0, E1, 4, 4);
	display_ui8matrix(I0, 0, 4, 0, 4, " [%03d] ", "I0");
	display_ui8matrix(I1, 0, 4, 0, 4, " [%03d] ", "I1");
	display_ui8matrix(M0, 0, 4, 0, 4, " [%03d] ", "M0");
	display_ui8matrix(M1, 0, 4, 0, 4, " [%03d] ", "M1");
	display_ui8matrix(O1, 0, 4, 0, 4, " [%03d] ", "O1");
	display_ui8matrix(V0, 0, 4, 0, 4, " [%03d] ", "V0");
	display_ui8matrix(V1, 0, 4, 0, 4, " [%03d] ", "V1");
	display_ui8matrix(E1, 0, 4, 0, 4, " [%03d] ", "E1");
	printf("\n");

	free_ui8matrix(I0, 0, 4, 0, 4);
  	free_ui8matrix(I1, 0, 4, 0, 4);
  	free_ui8matrix(M0, 0, 4, 0, 4);
  	free_ui8matrix(M1, 0, 4, 0, 4);
  	free_ui8matrix(O1, 0, 4, 0, 4);
  	free_ui8matrix(V0, 0, 4, 0, 4);
  	free_ui8matrix(V1, 0, 4, 0, 4);
  	free_ui8matrix(E1, 0, 4, 0, 4);

  	/* Benchmark*/
	I0 = ui8matrix(0, IMG_HEIGHT, 0, IMG_LENGTH);
	I1 = ui8matrix(0, IMG_HEIGHT, 0, IMG_LENGTH);
	M0 = ui8matrix(0, IMG_HEIGHT, 0, IMG_LENGTH);
	M1 = ui8matrix(0, IMG_HEIGHT, 0, IMG_LENGTH);
	O1 = ui8matrix(0, IMG_HEIGHT, 0, IMG_LENGTH);
	V0 = ui8matrix(0, IMG_HEIGHT, 0, IMG_LENGTH);
	V1 = ui8matrix(0, IMG_HEIGHT, 0, IMG_LENGTH);
	E1 = ui8matrix(0, IMG_HEIGHT, 0, IMG_LENGTH);

	MLoadPGM_ui8matrix(fname0, 0, IMG_HEIGHT, 0, IMG_LENGTH, I0);
	MLoadPGM_ui8matrix(fname1, 0, IMG_HEIGHT, 0, IMG_LENGTH, I1);

	SigmaDelta_step0(M0, I0, V0, IMG_HEIGHT, IMG_LENGTH);
	CHRONO(SigmaDelta_1step(M1, M0, I1, O1, V1, V0, E1, IMG_HEIGHT, IMG_LENGTH), "SD 5*5");

	SavePGM_ui8matrix(E1, 0, IMG_HEIGHT, 0, IMG_LENGTH, outfile);

	free_ui8matrix(I0, 0, IMG_HEIGHT, 0, IMG_LENGTH);
  	free_ui8matrix(I1, 0, IMG_HEIGHT, 0, IMG_LENGTH);
  	free_ui8matrix(M0, 0, IMG_HEIGHT, 0, IMG_LENGTH);
  	free_ui8matrix(M1, 0, IMG_HEIGHT, 0, IMG_LENGTH);
  	free_ui8matrix(O1, 0, IMG_HEIGHT, 0, IMG_LENGTH);
  	free_ui8matrix(V0, 0, IMG_HEIGHT, 0, IMG_LENGTH);
  	free_ui8matrix(V1, 0, IMG_HEIGHT, 0, IMG_LENGTH);
  	free_ui8matrix(E1, 0, IMG_HEIGHT, 0, IMG_LENGTH);
}

void test_multi_mouvement()
{
	clock_t start_t, end_t;
	double total_t;
	start_t = clock();

	char *fname0  = (char*)malloc(sizeof(char*) * 16);
	char *fname1  = (char*)malloc(sizeof(char*) * 16);
	char *outfile = (char*)malloc(sizeof(char*) * 24);
	int aux;
	strcpy(fname0, "img/car_3000.pgm");
	strcpy(fname1, "img/car_3001.pgm");
	strcpy(outfile,"output/1_sigdel_e001.pgm");
				//  012345678901234567890123456789

	INIT_MATRICES(I0, M0, V0, I1, M1, V1, O1, E1);

	MLoadPGM_ui8matrix(fname0, 0, HAUT, 0, LARG, I0);
	SigmaDelta_step0(M0, I0, V0, HAUT, LARG);

	for(int i = 2; i <= 200; i++)
	{
		MLoadPGM_ui8matrix(fname1, 0, HAUT, 0, LARG, I1);
		SigmaDelta_1step(M1, M0, I1, O1, V1, V0, E1, HAUT, LARG);
		SavePGM_ui8matrix(E1, 0, HAUT, 0, LARG, outfile);
		COPIER_MATRICES(I1, I0, M1, M0, V1, V0);
		strcpy(fname0, fname1);
		aux = (fname0[9]-'0')*100 + (fname0[10]-'0')*10 + (fname0[11]-'0') + 1;
		fname1[ 9] = outfile[17] = aux / 100 + '0';
		fname1[10] = outfile[18] = (aux / 10) % 10 + '0';
		fname1[11] = outfile[19] = aux % 10 + '0';
	}

	free(fname0);
	free(fname1);
	free(outfile);
	FREE_MATRICES(I0, M0, V0, I1, M1, V1, O1, E1);

	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("Temps pour 200 SD\t\t\t\t\t: %f s\n", total_t);
}

void test_unitaire_mouvement()
{
	char *fname0 = (char*)malloc(sizeof(char*) * 25);
	char *fname1 = (char*)malloc(sizeof(char*) * 25);
	char *outfile = (char*)malloc(sizeof(char*) * 34);
	strcpy(fname0, "test_img/tests_mouv_1.pgm");
	strcpy(fname1, "test_img/tests_mouv_2.pgm");
	strcpy(outfile,"test_img/mouvement/output_mouv.pgm");
				// 012345678901234567890123456789012345
	printf("\nTEST UNITAIRE MOUVEMENT 1\n");

	uint8 **I0 = ui8matrix(-1, 10, -1, 10);
	uint8 **I1 = ui8matrix(-1, 10, -1, 10);
	uint8 **M0 = ui8matrix(-1, 10, -1, 10);
	uint8 **V0 = ui8matrix(-1, 10, -1, 10);
	uint8 **M1 = ui8matrix(-1, 10, -1, 10);
	uint8 **V1 = ui8matrix(-1, 10, -1, 10);
	uint8 **O1 = ui8matrix(-1, 10, -1, 10);
	uint8 **E1 = ui8matrix(-1, 10, -1, 10);

	MLoadPGM_ui8matrix(fname0, 0, 9, 0, 9, I0);
	MLoadPGM_ui8matrix(fname1, 0, 9, 0, 9, I1);
	SigmaDelta_step0(M0, I0, V0, 9, 9);
	SigmaDelta_1step(M1, M0, I1, O1, V1, V0, E1, 9, 9);
	SavePGM_ui8matrix(E1, 0, 9, 0, 9, outfile);

	display_ui8matrix(I0, 0, 9, 0, 9, " [%03d]", "\nI0");
	display_ui8matrix(I1, 0, 9, 0, 9, " [%03d]", "\nI1");
	// display_ui8matrix(M0, 0, 9, 0, 9, " [%03d]", "\nM0");
	// display_ui8matrix(M1, 0, 9, 0, 9, " [%03d]", "\nM1");
	// display_ui8matrix(O1, 0, 9, 0, 9, " [%03d]", "\nO1");
	// display_ui8matrix(V0, 0, 9, 0, 9, " [%03d]", "\nV0");
	// display_ui8matrix(V1, 0, 9, 0, 9, " [%03d]", "\nV1");
	display_ui8matrix(E1, 0, 9, 0, 9, " [%3d]", "\nE1");

	free(fname0);
	free(fname1);
	free(outfile);
	free_ui8matrix(I0, -1, 10, -1, 10);
	free_ui8matrix(I1, -1, 10, -1, 10);
	free_ui8matrix(M0, -1, 10, -1, 10);
	free_ui8matrix(M1, -1, 10, -1, 10);
	free_ui8matrix(O1, -1, 10, -1, 10);
	free_ui8matrix(V0, -1, 10, -1, 10);
	free_ui8matrix(V1, -1, 10, -1, 10);
	free_ui8matrix(E1, -1, 10, -1, 10);
}
