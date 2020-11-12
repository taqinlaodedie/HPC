#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "nrdef.h"
#include "nrutil.h"
#include "morpho_SIMD.h"
#include "test_morpho_SIMD.h"
#include "mymacro.h"
#include "myutils.h"
#include "sys/time.h"

void test_morpho_SIMD()
{
	struct timeval t1, t2;
	double timeused;

	char *fname0 = "test_img/mouvement/output_SIMD.pgm";
	vuint8 **I0 = vui8matrix(-1, IMG_HEIGHT+1, -1, IMG_LENGTH/16+1);
	vuint8 **I1 = vui8matrix(-1, IMG_HEIGHT+1, -1, IMG_LENGTH/16+1);

	MLoadPGM_vui8matrix(fname0, -1, IMG_HEIGHT+1, -1, IMG_LENGTH+1, I0);

	gettimeofday(&t1, NULL);
	erosion_SIMD(I0, I1, IMG_HEIGHT, IMG_LENGTH/16);
	gettimeofday(&t2, NULL);
	timeused = (t2.tv_sec - t1.tv_sec) + (double)(t2.tv_usec - t1.tv_usec)/1000000.0;
	printf("Temps pour une erosion en SIMD: %f s\n", timeused);
	SavePGM_vui8matrix(I1, 0,IMG_HEIGHT-1, 0, IMG_LENGTH-1, "test_img/morpho/erosion1_SIMD.pgm");

	gettimeofday(&t1, NULL);
	dilatation_SIMD(I1, I0, IMG_HEIGHT, IMG_LENGTH/16);
	gettimeofday(&t2, NULL);
	timeused = (t2.tv_sec - t1.tv_sec) + (double)(t2.tv_usec - t1.tv_usec)/1000000.0;
	printf("Temps pour une dilatation en SIMD: %f s\n", timeused);
	SavePGM_vui8matrix(I0, 0,IMG_HEIGHT-1, 0, IMG_LENGTH-1, "test_img/morpho/dilatation1SIMD.pgm");

	free_vui8matrix(I0, -1, IMG_HEIGHT+1, -1, IMG_LENGTH/16+1);
	free_vui8matrix(I1, -1, IMG_HEIGHT+1, -1, IMG_LENGTH/16+1);
}