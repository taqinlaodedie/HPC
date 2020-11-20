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
	vuint8 **I0 = vui8matrix(-2, IMG_HEIGHT+2, -2, IMG_LENGTH/16+2);
	vuint8 **I1 = vui8matrix(-2, IMG_HEIGHT+2, -2, IMG_LENGTH/16+2);
	vuint8 **I2 = vui8matrix(-2, IMG_HEIGHT+2, -2, IMG_LENGTH/16+2);
	vuint8 **I3 = vui8matrix(-2, IMG_HEIGHT+2, -2, IMG_LENGTH/16+2);
	vuint8 **I4 = vui8matrix(-2, IMG_HEIGHT+2, -2, IMG_LENGTH/16+2);
	vuint8 **tmp = vui8matrix(-2, IMG_HEIGHT+2, -2, IMG_LENGTH/16+2);
	zero_vui8matrix(I0, -2, IMG_HEIGHT+2, -2, IMG_LENGTH/16+2);
	zero_vui8matrix(I1, -2, IMG_HEIGHT+2, -2, IMG_LENGTH/16+2);
	zero_vui8matrix(I2, -2, IMG_HEIGHT+2, -2, IMG_LENGTH/16+2);
	zero_vui8matrix(I3, -2, IMG_HEIGHT+2, -2, IMG_LENGTH/16+2);
	zero_vui8matrix(I4, -2, IMG_HEIGHT+2, -2, IMG_LENGTH/16+2);

	MLoadPGM_vui8matrix(fname0, 0, IMG_HEIGHT-1, 0, IMG_LENGTH-1, I0);

	// gettimeofday(&t1, NULL);
	// erosion_SIMD(I0, I1, IMG_HEIGHT, IMG_LENGTH/16);
	// gettimeofday(&t2, NULL);
	// timeused = (t2.tv_sec - t1.tv_sec) + (double)(t2.tv_usec - t1.tv_usec)/1000000.0;
	// printf("Temps pour 1 erosion en SIMD: %f s\n", timeused);
	// SavePGM_vui8matrix(I1, 0,IMG_HEIGHT-1, 0, IMG_LENGTH-1, "test_img/morpho/erosion1_SIMD.pgm");

	// gettimeofday(&t1, NULL);
	// erosion_SIMD_factorisee(I0, I1, IMG_HEIGHT, IMG_LENGTH/16);
	// gettimeofday(&t2, NULL);
	// timeused = (t2.tv_sec - t1.tv_sec) + (double)(t2.tv_usec - t1.tv_usec)/1000000.0;
	// printf("Temps pour 1 erosion factorisee en SIMD: %f s\n", timeused);
	// SavePGM_vui8matrix(I1, 0,IMG_HEIGHT-1, 0, IMG_LENGTH-1, "test_img/morpho/erosion1_SIMD_factorisee.pgm");

	// gettimeofday(&t1, NULL);
	// dilatation_SIMD(I1, I0, IMG_HEIGHT, IMG_LENGTH/16);
	// gettimeofday(&t2, NULL);
	// timeused = (t2.tv_sec - t1.tv_sec) + (double)(t2.tv_usec - t1.tv_usec)/1000000.0;
	// printf("Temps pour 1 dilatation en SIMD: %f s\n", timeused);
	// SavePGM_vui8matrix(I0, 0,IMG_HEIGHT-1, 0, IMG_LENGTH-1, "test_img/morpho/dilatation1_SIMD.pgm");

	// gettimeofday(&t1, NULL);
	// dilatation_SIMD_factorisee(I1, I0, IMG_HEIGHT, IMG_LENGTH/16);
	// gettimeofday(&t2, NULL);
	// timeused = (t2.tv_sec - t1.tv_sec) + (double)(t2.tv_usec - t1.tv_usec)/1000000.0;
	// printf("Temps pour 1 dilatation factorisee en SIMD: %f s\n", timeused);
	// SavePGM_vui8matrix(I0, 0,IMG_HEIGHT-1, 0, IMG_LENGTH-1, "test_img/morpho/dilatation1_SIMD_factorisee.pgm");

	// gettimeofday(&t1, NULL);
	// dilatation5_SIMD(I0, I1, IMG_HEIGHT, IMG_LENGTH/16);
	// gettimeofday(&t2, NULL);
	// timeused = (t2.tv_sec - t1.tv_sec) + (double)(t2.tv_usec - t1.tv_usec)/1000000.0;
	// printf("Temps pour 1 dilatation en 5*5: %f s\n", timeused);
	// SavePGM_vui8matrix(I1, 0,IMG_HEIGHT-1, 0, IMG_LENGTH-1, "test_img/morpho/dilatation5_SIMD.pgm");

	// gettimeofday(&t1, NULL);
	// dilatation5_SIMD_factorisee(I0, I1, tmp, IMG_HEIGHT, IMG_LENGTH/16);
	// gettimeofday(&t2, NULL);
	// timeused = (t2.tv_sec - t1.tv_sec) + (double)(t2.tv_usec - t1.tv_usec)/1000000.0;
	// printf("Temps pour 1 dilatation factorisee en 5*5: %f s\n", timeused);
	// SavePGM_vui8matrix(I1, 0,IMG_HEIGHT-1, 0, IMG_LENGTH-1, "test_img/morpho/dilatation5_SIMD_factorisee.pgm");

	// gettimeofday(&t1, NULL);
	// dilatation_SIMD(I0, I1, IMG_HEIGHT, IMG_LENGTH/16);
	// dilatation_SIMD(I1, I0, IMG_HEIGHT, IMG_LENGTH/16);
	// gettimeofday(&t2, NULL);
	// timeused = (t2.tv_sec - t1.tv_sec) + (double)(t2.tv_usec - t1.tv_usec)/1000000.0;
	// printf("Temps pour 2 dilatations en SIMD: %f s\n", timeused);
	// SavePGM_vui8matrix(I0, 0,IMG_HEIGHT-1, 0, IMG_LENGTH-1, "test_img/morpho/2dilatation_SIMD.pgm");

	gettimeofday(&t1, NULL);
	morpho_SIMD_pipeline(I0, I1, I2, I3, I4, IMG_HEIGHT, IMG_LENGTH/16);
	gettimeofday(&t2, NULL);
	timeused = (t2.tv_sec - t1.tv_sec) + (double)(t2.tv_usec - t1.tv_usec)/1000000.0;
	printf("Temps pour pipeline en SIMD: %f s\n", timeused);
	SavePGM_vui8matrix(I1, 0,IMG_HEIGHT-1, 0, IMG_LENGTH-1, "test_img/morpho/pipeline_e1_SIMD.pgm");
	SavePGM_vui8matrix(I2, 0,IMG_HEIGHT-1, 0, IMG_LENGTH-1, "test_img/morpho/pipeline_d1_SIMD.pgm");
	SavePGM_vui8matrix(I3, 0,IMG_HEIGHT-1, 0, IMG_LENGTH-1, "test_img/morpho/pipeline_d2_SIMD.pgm");
	SavePGM_vui8matrix(I4, 0,IMG_HEIGHT-1, 0, IMG_LENGTH-1, "test_img/morpho/pipeline_e2_SIMD.pgm");

	free_vui8matrix(I0, -2, IMG_HEIGHT+2, -2, IMG_LENGTH/16+2);
	free_vui8matrix(I1, -2, IMG_HEIGHT+2, -2, IMG_LENGTH/16+2);
	free_vui8matrix(I2, -2, IMG_HEIGHT+2, -2, IMG_LENGTH/16+2);
	free_vui8matrix(I3, -2, IMG_HEIGHT+2, -2, IMG_LENGTH/16+2);
	free_vui8matrix(I4, -2, IMG_HEIGHT+2, -2, IMG_LENGTH/16+2);
	free_vui8matrix(tmp, -2, IMG_HEIGHT+2, -2, IMG_LENGTH/16+2);
}