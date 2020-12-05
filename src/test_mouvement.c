#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "nrdef.h"
#include "nrutil.h"
#include "mouvement.h"
#include "test_mouvement.h"
#include "mymacro.h"
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

	printf("Test unitaire pour moouvement\n");
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
	CHRONO(SigmaDelta_1step(M1, M0, I1, O1, V1, V0, E1, IMG_HEIGHT, IMG_LENGTH), "SD");

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
