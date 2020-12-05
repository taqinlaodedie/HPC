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

	test_unitaire_morpho_SIMD();

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

void test_unitaire_morpho_SIMD()
{
	vuint8 **tab0 = vui8matrix(-1, 1, -1, 1);
	vuint8 **tab1 = vui8matrix(-1, 1, -1, 1);
	vuint8 aux;
	vuint8 zer = init_vuint8(0);
	vuint8 one = init_vuint8(255);

	/***** TESTS UNITAIRES EROSION *****/

	// Initialisation
	zero_vui8matrix(tab0, -1, 1, -1, 1);
	zero_vui8matrix(tab1, -1, 1, -1, 1);

	printf("\n");
	display_vui8matrix(tab0, -1, 1, -1, 1, " [%d]", "Test unitaire SIMD EROSION");

	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			_mm_store_si128((vuint8 *)&tab0[i][j], one);
			erosion_SIMD(tab0, tab1, 1, 1);
			// display_vui8matrix(tab0, -1, 1, -1, 1, " [%03d] ", "\nModifie");
			// display_vui8matrix(tab1, -1, 1, -1, 1, " [%03d] ", "Resultat");
			aux = _mm_load_si128((vuint8 *)&tab1[0][0]);
			display_vuint8(aux, "[%03d] ", "");
			printf("\n");
			// if( cmpeq_vuint8(aux, zer) )
			// 	printf("OK\n");
			// else
			// {
			// 	printf("KO\n");
			// 	return;
			// }
			_mm_store_si128((vuint8 *)&tab0[i][j], zer);
		}
	}

	/***** TESTS UNITAIRES DILATATION *****/

	// Initialisation en 1
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			_mm_store_si128((vuint8 *)&tab0[i][j], one);
		}
	}

	printf("\n");
	display_vui8matrix(tab0, -1, 1, -1, 1, " [%03d]", "Test unitaire SIMD DILATATION");

	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			_mm_store_si128((vuint8 *)&tab0[i][j], zer);
			dilatation_SIMD(tab0, tab1, 1, 1);
			// display_vui8matrix(tab0, -1, 1, -1, 1, " [%03d] ", "\nModifie");
			// display_vui8matrix(tab1, -1, 1, -1, 1, " [%03d] ", "Resultat");
			aux = _mm_load_si128((vuint8 *)&tab1[0][0]);
			display_vuint8(aux, "[%03d] ", "");
			printf("\n");
			// if( cmpeq_vuint8(aux, one) )
			// 	printf("OK\n");
			// else
			// {
			// 	printf("KO\n");
			// 	return;
			// }
			_mm_store_si128((vuint8 *)&tab0[i][j], one);
		}
	}

	free_vui8matrix(tab0, -1, 1, -1, 1);
  	free_vui8matrix(tab1, -1, 1, -1, 1);
}
