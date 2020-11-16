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
	uint8 **I0 = ui8matrix(0, IMG_HEIGHT, 0, IMG_LENGTH);
	uint8 **I1 = ui8matrix(0, IMG_HEIGHT, 0, IMG_LENGTH);
	uint8 **M0 = ui8matrix(0, IMG_HEIGHT, 0, IMG_LENGTH);
	uint8 **M1 = ui8matrix(0, IMG_HEIGHT, 0, IMG_LENGTH);
	uint8 **O1 = ui8matrix(0, IMG_HEIGHT, 0, IMG_LENGTH);
	uint8 **V0 = ui8matrix(0, IMG_HEIGHT, 0, IMG_LENGTH);
	uint8 **V1 = ui8matrix(0, IMG_HEIGHT, 0, IMG_LENGTH);
	uint8 **E1 = ui8matrix(0, IMG_HEIGHT, 0, IMG_LENGTH);

	MLoadPGM_ui8matrix(fname0, 0, IMG_HEIGHT, 0, IMG_LENGTH, I0);
	MLoadPGM_ui8matrix(fname1, 0, IMG_HEIGHT, 0, IMG_LENGTH, I1);

	SigmaDelta_step0(M0, I0, V0, IMG_HEIGHT, IMG_LENGTH);
	gettimeofday(&t1, NULL);
	SigmaDelta_1step(M1, M0, I1, O1, V1, V0, E1, IMG_HEIGHT, IMG_LENGTH);
	gettimeofday(&t2, NULL);
	timeused = (t2.tv_sec - t1.tv_sec) + (double)(t2.tv_usec - t1.tv_usec)/1000000.0;
	printf("Temps pour 1 SD: %f s\n", timeused);

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
