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

void test_mouvement()
{
	char *fname0 = "img/car_3110.pgm";
	char *fname1 = "img/car_3111.pgm";
	char *outfile = "output_mouvement.pgm";
	uint8 **I0 = ui8matrix(0, IMG_LENGTH-1, 0, IMG_HEIGHT-1);
	uint8 **I1 = ui8matrix(0, IMG_LENGTH-1, 0, IMG_HEIGHT-1);
	uint8 **M0 = ui8matrix(0, IMG_LENGTH-1, 0, IMG_HEIGHT-1);
	uint8 **M1 = ui8matrix(0, IMG_LENGTH-1, 0, IMG_HEIGHT-1);
	uint8 **O1 = ui8matrix(0, IMG_LENGTH-1, 0, IMG_HEIGHT-1);
	uint8 **V0 = ui8matrix(0, IMG_LENGTH-1, 0, IMG_HEIGHT-1);
	uint8 **V1 = ui8matrix(0, IMG_LENGTH-1, 0, IMG_HEIGHT-1);
	uint8 **E1 = ui8matrix(0, IMG_LENGTH-1, 0, IMG_HEIGHT-1);

	MLoadPGM_ui8matrix(fname0, 0, IMG_LENGTH-1, 0, IMG_HEIGHT-1, I0);
	MLoadPGM_ui8matrix(fname1, 0, IMG_LENGTH-1, 0, IMG_HEIGHT-1, I1);

	SigmaDelta_step0(M0, I0, V0, IMG_LENGTH, IMG_HEIGHT);
	SigmaDelta_1step(M1, M0, I1, IMG_LENGTH, IMG_HEIGHT);
	SigmaDelta_2step(O1, M1, I1, IMG_LENGTH, IMG_HEIGHT);
	SigmaDelta_3step(V1, V0, O1, IMG_LENGTH, IMG_HEIGHT, 2);
	SigmaDelta_4step(O1, V1, E1, IMG_LENGTH, IMG_HEIGHT);

	SavePGM_ui8matrix(E1, 0, IMG_LENGTH-1, 0, IMG_HEIGHT-1, outfile);

	MLoadPGM_ui8matrix(outfile, 0, IMG_LENGTH-1, 0, IMG_HEIGHT-1, I0);
	MLoadPGM_ui8matrix("output_mouvement_SIMD.pgm", 0, IMG_LENGTH-1, 0, IMG_HEIGHT-1, I1);
	for (int i = 0; i < IMG_LENGTH; i++) {
		for (int j = 0; j < IMG_HEIGHT; j++) {
			I0[i][j] -= I1[i][j];
		}
	}
	SavePGM_ui8matrix(I0, 0, IMG_LENGTH-1, 0, IMG_HEIGHT-1, "diff.pgm");

	free_ui8matrix(I0, 0, IMG_LENGTH-1, 0, IMG_HEIGHT-1);
	free_ui8matrix(I1, 0, IMG_LENGTH-1, 0, IMG_HEIGHT-1);
	free_ui8matrix(M0, 0, IMG_LENGTH-1, 0, IMG_HEIGHT-1);
	free_ui8matrix(M1, 0, IMG_LENGTH-1, 0, IMG_HEIGHT-1);
	free_ui8matrix(O1, 0, IMG_LENGTH-1, 0, IMG_HEIGHT-1);
	free_ui8matrix(V0, 0, IMG_LENGTH-1, 0, IMG_HEIGHT-1);
	free_ui8matrix(V1, 0, IMG_LENGTH-1, 0, IMG_HEIGHT-1);
	free_ui8matrix(E1, 0, IMG_LENGTH-1, 0, IMG_HEIGHT-1);
}