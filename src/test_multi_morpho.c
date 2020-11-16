#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "nrdef.h"
#include "nrutil.h"
#include "morpho.h"
#include "mymacro.h"
#include "myutils.h"
#include "sys/time.h"

void test_multi_morpho()
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

	uint8 **I0 = ui8matrix(-1, HAUTMORPH, -1, LARGMORPH);
	uint8 **I1 = ui8matrix(-1, HAUTMORPH, -1, LARGMORPH);

	for(int i = 2; i <= 200; i++)
	{
		MLoadPGM_ui8matrix(fname0, -1, HAUTMORPH, -1, LARGMORPH, I0);
		erosion(I0, I1, HAUT, LARG);
		dilatation(I1, I0, HAUT, LARG);
		dilatation(I0, I1, HAUT, LARG);
		erosion(I1, I0, HAUT, LARG);
		// printf("hola0 %d\n", i);
		SavePGM_ui8matrix(I0, -1, HAUTMORPH, -1, LARGMORPH, outfile);
		// printf("hola1 %d\n", i);

		aux = (fname0[15]-'0')*100 + (fname0[16]-'0')*10 + (fname0[17]-'0') + 1;
		fname0[15] = outfile[15] = aux / 100 + '0';
		fname0[16] = outfile[16] = (aux / 10) % 10 + '0';
		fname0[17] = outfile[17] = aux % 10 + '0';
	}

	free_ui8matrix(I0, -1, HAUTMORPH, -1, LARGMORPH);
	free_ui8matrix(I1, -1, HAUTMORPH, -1, LARGMORPH);

	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("Temps pour 200 morphos: %f\n", total_t);
}
