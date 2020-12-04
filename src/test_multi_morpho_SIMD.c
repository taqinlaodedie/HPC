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
#include "test_multi_morpho_SIMD.h"
#include "mymacro.h"
#include "myutils.h"
#include "sys/time.h"

void test_multi_morpho_SIMD()
{
	clock_t start_t, end_t;
	double total_t;
	start_t = clock();

	char *fname0  = (char*)malloc(sizeof(char*) * 16);
	char *outfile = (char*)malloc(sizeof(char*) * 16);
	int aux;
	strcpy(fname0, "output/output_e001.pgm");
	strcpy(outfile,"output/xmorph_e001.pgm");
				//  012345678901234567890123

	INIT_MORPHO_VMATRICES(I0, E0, D0, D1, E1);

	for(int i = 2; i <= 200; i++)
	{
		MLoadPGM_vui8matrix(fname0, 0, HAUT, 0, LARG, I0);
		erosion_SIMD(I0, E0, HAUTMORPH, LARGMORPH/16);
		dilatation_SIMD(E0, D0, HAUTMORPH, LARGMORPH/16);
		dilatation_SIMD(D0, D1, HAUTMORPH, LARGMORPH/16);
		erosion_SIMD(D1, E1, HAUTMORPH, LARGMORPH/16);
		// printf("hola0 %d\n", i);
		SavePGM_vui8matrix(E1, 0, HAUT, 0, LARG, outfile);
		// printf("hola1 %d\n", i);

		aux = (fname0[15]-'0')*100 + (fname0[16]-'0')*10 + (fname0[17]-'0') + 1;
		fname0[15] = outfile[15] = aux / 100 + '0';
		fname0[16] = outfile[16] = (aux / 10) % 10 + '0';
		fname0[17] = outfile[17] = aux % 10 + '0';
	}

	free(fname0);
	free(outfile);
	FREE_MORPHO_VMATRICES(I0, E0, D0, D1, E1);

	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("Temps pour 200 morphos en SIMD: %f\n", total_t);
}