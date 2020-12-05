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

	CHRONO(erosion_SIMD(I0, I1, IMG_HEIGHT, IMG_LENGTH/16);	\
		dilatation_SIMD(I1, I2, IMG_HEIGHT, IMG_LENGTH/16);	\
		dilatation_SIMD(I2, I3, IMG_HEIGHT, IMG_LENGTH/16);	\
		erosion_SIMD(I3, I4, IMG_HEIGHT, IMG_LENGTH/16), "chaine morpho SIMD");
	
	CHRONO(morpho_SIMD_pipeline(I0, I1, I2, I3, I4, IMG_HEIGHT, IMG_LENGTH/16), "pipeline SIMD");
	SavePGM_vui8matrix(I1, 0,IMG_HEIGHT-1, 0, IMG_LENGTH-1, "test_img/morpho/pipeline_e1_SIMD.pgm");
	SavePGM_vui8matrix(I2, 0,IMG_HEIGHT-1, 0, IMG_LENGTH-1, "test_img/morpho/pipeline_d1_SIMD.pgm");
	SavePGM_vui8matrix(I3, 0,IMG_HEIGHT-1, 0, IMG_LENGTH-1, "test_img/morpho/pipeline_d2_SIMD.pgm");
	SavePGM_vui8matrix(I4, 0,IMG_HEIGHT-1, 0, IMG_LENGTH-1, "test_img/morpho/pipeline_e2_SIMD.pgm");

	CHRONO(erosion_SIMD(I0, I1, IMG_HEIGHT, IMG_LENGTH/16), "erosion SIMD");
	SavePGM_vui8matrix(I1, 0,IMG_HEIGHT-1, 0, IMG_LENGTH-1, "test_img/morpho/erosion1_SIMD.pgm");

	CHRONO(erosion_SIMD_factorisee(I0, I1, IMG_HEIGHT, IMG_LENGTH/16), "erosion factorisee en SIMD");
	SavePGM_vui8matrix(I1, 0,IMG_HEIGHT-1, 0, IMG_LENGTH-1, "test_img/morpho/erosion1_SIMD_factorisee.pgm");

	CHRONO(dilatation_SIMD(I1, I2, IMG_HEIGHT, IMG_LENGTH/16), "dilatation en SIMD");
	SavePGM_vui8matrix(I2, 0,IMG_HEIGHT-1, 0, IMG_LENGTH-1, "test_img/morpho/dilatation1_SIMD.pgm");

	CHRONO(dilatation_SIMD_factorisee(I1, I2, IMG_HEIGHT, IMG_LENGTH/16), "dilatation factorisee en SIMD");
	SavePGM_vui8matrix(I2, 0,IMG_HEIGHT-1, 0, IMG_LENGTH-1, "test_img/morpho/dilatation1_SIMD_factorisee.pgm");

	CHRONO(dilatation5_SIMD(I1, I3, IMG_HEIGHT, IMG_LENGTH/16), "dilatation en 5*5");
	SavePGM_vui8matrix(I3, 0,IMG_HEIGHT-1, 0, IMG_LENGTH-1, "test_img/morpho/dilatation5_SIMD.pgm");

	CHRONO(dilatation5_SIMD_factorisee(I1, I3, tmp, IMG_HEIGHT, IMG_LENGTH/16), "dilatation factorisee en 5*5");
	SavePGM_vui8matrix(I3, 0,IMG_HEIGHT-1, 0, IMG_LENGTH-1, "test_img/morpho/dilatation5_SIMD_factorisee.pgm");

	CHRONO(dilatation_SIMD(I1, I2, IMG_HEIGHT, IMG_LENGTH/16);	\
		dilatation_SIMD(I2, I3, IMG_HEIGHT, IMG_LENGTH/16), "2 dilatations en SIMD");
	SavePGM_vui8matrix(I3, 0,IMG_HEIGHT-1, 0, IMG_LENGTH-1, "test_img/morpho/2dilatation_SIMD.pgm");

	CHRONO(for (int i = 0; i < 200; i++) {	\
		dilatation_SIMD(I1, I3, IMG_HEIGHT, IMG_LENGTH/16);
		}, "200 dilatation_SIMD");

	CHRONO(for (int i = 0; i < 200; i++) {	\
		dilatation_SIMD_factorisee(I1, I3, IMG_HEIGHT, IMG_LENGTH/16);
		}, "200 dilatation_SIMD_factorisee");

	CHRONO(for (int i = 0; i < 200; i++) {	\
		dilatation5_SIMD(I1, I3, IMG_HEIGHT, IMG_LENGTH/16);
		}, "200 dilatation5_SIMD");

	CHRONO(for (int i = 0; i < 200; i++) {	\
		dilatation_SIMD(I1, I2, IMG_HEIGHT, IMG_LENGTH/16);	\
		dilatation_SIMD(I2, I3, IMG_HEIGHT, IMG_LENGTH/16);
		}, "400 dilatations en SIMD");

	free_vui8matrix(I0, -2, IMG_HEIGHT+2, -2, IMG_LENGTH/16+2);
	free_vui8matrix(I1, -2, IMG_HEIGHT+2, -2, IMG_LENGTH/16+2);
	free_vui8matrix(I2, -2, IMG_HEIGHT+2, -2, IMG_LENGTH/16+2);
	free_vui8matrix(I3, -2, IMG_HEIGHT+2, -2, IMG_LENGTH/16+2);
	free_vui8matrix(I4, -2, IMG_HEIGHT+2, -2, IMG_LENGTH/16+2);
	free_vui8matrix(tmp, -2, IMG_HEIGHT+2, -2, IMG_LENGTH/16+2);
}