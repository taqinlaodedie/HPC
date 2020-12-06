#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "nrdef.h"
#include "nrutil.h"
#include "vnrdef.h"
#include "vnrutil.h"
#include "morpho_SIMD.h"
#include "test_morpho_SIMD.h"
#include "mymacro.h"
#include "myutils.h"
#include "sys/time.h"
#include  <omp.h>

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

void test_multi_morpho_SIMD()
{
	clock_t start_t, end_t;
	double total_t;

	char *fname0  = (char*)malloc(sizeof(char*) * 16);
	char *outfile = (char*)malloc(sizeof(char*) * 16);
	int aux;
	strcpy(fname0, "output/output_e001.pgm");
	strcpy(outfile,"output/xmorph_e001.pgm");
				//  012345678901234567890123

	INIT_MORPHO_VMATRICES(I0, E0, D0, D1, E1);

	start_t = clock();
	for(int i = 2; i <= 200; i++)
	{
		MLoadPGM_vui8matrix(fname0, 0, HAUT, 0, LARG, I0);
		erosion_SIMD(I0, E0, HAUT+1, (LARG+1)/16);
		dilatation_SIMD(E0, D0, HAUT+1, (LARG+1)/16);
		dilatation_SIMD(D0, D1, HAUT+1, (LARG+1)/16);
		erosion_SIMD(D1, E1, HAUT+1, (LARG+1)/16);
		SavePGM_vui8matrix(E1, 0, HAUT, 0, LARG, outfile);

		aux = (fname0[15]-'0')*100 + (fname0[16]-'0')*10 + (fname0[17]-'0') + 1;
		fname0[15] = outfile[15] = aux / 100 + '0';
		fname0[16] = outfile[16] = (aux / 10) % 10 + '0';
		fname0[17] = outfile[17] = aux % 10 + '0';
	}

	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("Temps pour 200 morphos en SIMD: %f\n", total_t);

	strcpy(fname0, "output/output_e001.pgm");
	strcpy(outfile,"output/xmorph_e001.pgm");

	start_t = clock();
	for(int i = 2; i <= 200; i++)
	{
		MLoadPGM_vui8matrix(fname0, 0, HAUT, 0, LARG, I0);
		morpho_SIMD_pipeline(I0, E0, D0, D1, E1, HAUT+1, (LARG+1)/16);
		SavePGM_vui8matrix(E1, 0, HAUT, 0, LARG, outfile);

		aux = (fname0[15]-'0')*100 + (fname0[16]-'0')*10 + (fname0[17]-'0') + 1;
		fname0[15] = outfile[15] = aux / 100 + '0';
		fname0[16] = outfile[16] = (aux / 10) % 10 + '0';
		fname0[17] = outfile[17] = aux % 10 + '0';
	}

	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("Temps pour 200 morphos en SIMD en pipeline: %f\n", total_t);

	free(fname0);
	free(outfile);
	FREE_MORPHO_VMATRICES(I0, E0, D0, D1, E1);
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
	display_vui8matrix(tab0, -1, 1, -1, 1, " [%d]", "Test unitaire EROSION SIMD");
	// printf(" i  j\n");

	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			_mm_store_si128((vuint8 *)&tab0[i][j], one);
			erosion_SIMD(tab0, tab1, 1, 1);
			// display_vui8matrix(tab0, -1, 1, -1, 1, " [%03d] ", "\nModifie");
			// display_vui8matrix(tab1, -1, 1, -1, 1, " [%03d] ", "Resultat");
			aux = _mm_load_si128((vuint8 *)&tab1[0][0]);
			// printf("%2d %2d   ", i, j);
			display_vuint8(aux, "[%d] ", "");
			printf("\n");
			_mm_store_si128((vuint8 *)&tab0[i][j], zer);
		}
	}

	/***** TESTS UNITAIRES DILATATION *****/

	// Initialisation à 255
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			_mm_store_si128((vuint8 *)&tab0[i][j], one);
		}
	}

	printf("\n");
	display_vui8matrix(tab0, -1, 1, -1, 1, " [%03d]", "Test unitaire DILATATION SIMD");
	printf(" i  j\n");

	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			_mm_store_si128((vuint8 *)&tab0[i][j], zer);
			dilatation_SIMD(tab0, tab1, 1, 1);
			// display_vui8matrix(tab0, -1, 1, -1, 1, " [%03d] ", "\nModifie");
			// display_vui8matrix(tab1, -1, 1, -1, 1, " [%03d] ", "Resultat");
			aux = _mm_load_si128((vuint8 *)&tab1[0][0]);
			printf("%2d %2d   ", i, j);
			display_vuint8(aux, "[%03d] ", "");
			printf("\n");
			_mm_store_si128((vuint8 *)&tab0[i][j], one);
		}
	}
	printf("\n");

	free_vui8matrix(tab0, -1, 1, -1, 1);
  	free_vui8matrix(tab1, -1, 1, -1, 1);
}

// mode 0: normal, mode 1: pipeline
void test_morpho_SIMD_para(int mode)
{
	clock_t start_t, end_t;
	double total_t;

	char *fname0  = (char*)malloc(sizeof(char*) * 16);
	char *outfile = (char*)malloc(sizeof(char*) * 16);
	int aux;
	strcpy(fname0, "output/output_e001.pgm");
	strcpy(outfile,"output/xmorph_e001.pgm");
				//  012345678901234567890123

	INIT_MORPHO_VMATRICES(I0, E0, D0, D1, E1);

	if (mode == 0) {
		start_t = clock();
		#pragma omp parallel
		#pragma  omp  for  schedule(static) nowait
		for(int i = 2; i <= 200; i++)
		{
			MLoadPGM_vui8matrix(fname0, 0, HAUT, 0, LARG, I0);
			erosion_SIMD(I0, E0, HAUT+1, (LARG+1)/16);
			dilatation_SIMD(E0, D0, HAUT+1, (LARG+1)/16);
			dilatation_SIMD(D0, D1, HAUT+1, (LARG+1)/16);
			erosion_SIMD(D1, E1, HAUT+1, (LARG+1)/16);
			SavePGM_vui8matrix(E1, 0, HAUT, 0, LARG, outfile);

			aux = (fname0[15]-'0')*100 + (fname0[16]-'0')*10 + (fname0[17]-'0') + 1;
			fname0[15] = outfile[15] = aux / 100 + '0';
			fname0[16] = outfile[16] = (aux / 10) % 10 + '0';
			fname0[17] = outfile[17] = aux % 10 + '0';
			// printf("%d\n", i);
		}

		end_t = clock();
		total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
		printf("Temps pour 200 morphos en SIMD parallel: %f\n", total_t);
	}
	else {
		start_t = clock();
		#pragma omp parallel
		#pragma  omp  for  schedule(static) nowait
		for(int i = 2; i <= 200; i++)
		{
			MLoadPGM_vui8matrix(fname0, 0, HAUT, 0, LARG, I0);
			morpho_SIMD_pipeline(I0, E0, D0, D1, E1, HAUT+1, (LARG+1)/16);
			SavePGM_vui8matrix(E1, 0, HAUT, 0, LARG, outfile);

			aux = (fname0[15]-'0')*100 + (fname0[16]-'0')*10 + (fname0[17]-'0') + 1;
			fname0[15] = outfile[15] = aux / 100 + '0';
			fname0[16] = outfile[16] = (aux / 10) % 10 + '0';
			fname0[17] = outfile[17] = aux % 10 + '0';
			// printf("%d\n", i);
		}

		end_t = clock();
		total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
		printf("Temps pour 200 morphos en SIMD en pipeline parallel: %f\n", total_t);
	}

	free(fname0);
	free(outfile);
	FREE_MORPHO_VMATRICES(I0, E0, D0, D1, E1);
}
