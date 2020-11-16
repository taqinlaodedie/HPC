#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "nrdef.h"
#include "nrutil.h"
#include "mouvement.h"
#include "test_multi_mouvement.h"
#include "mymacro.h"
#include "myutils.h"
#include "sys/time.h"

void test_multi_mouvement()
{
	clock_t start_t, end_t;
	double total_t;
	start_t = clock();

	char *fname0 = (char*)malloc(sizeof(char*) * 16);
	char *fname1 = (char*)malloc(sizeof(char*) * 16);
	char *outfile = (char*)malloc(sizeof(char*) * 22);
	int aux;
	strcpy(fname0, "img/car_3000.pgm");
	strcpy(fname1, "img/car_3001.pgm");
	strcpy(outfile,"output/output_e001.pgm");
				//  012345678901234567890123

	INIT_MATRICES(I0, M0, V0, I1, M1, V1, O1, E1);

	MLoadPGM_ui8matrix(fname0, 0, HAUT, 0, LARG, I0);
	SigmaDelta_step0(M0, I0, V0, HAUT, LARG);

	for(int i = 2; i <= 200; i++)
	{
		MLoadPGM_ui8matrix(fname1, 0, HAUT, 0, LARG, I1);
		SigmaDelta_1step(M1, M0, I1, O1, V1, V0, E1, HAUT, LARG);
		SavePGM_ui8matrix(E1, 0, HAUT, 0, LARG, outfile);
		COPIER_MATRICES(I1, I0, M1, M0, V1, V0);
		strcpy(fname0, fname1);
		aux = (fname0[9]-'0')*100 + (fname0[10]-'0')*10 + (fname0[11]-'0') + 1;
		fname1[9] = outfile[15] = aux / 100 + '0';
		fname1[10] = outfile[16] = (aux / 10) % 10 + '0';
		fname1[11] = outfile[17] = aux % 10 + '0';
	}

	FREE_MATRICES(I0, M0, V0, I1, M1, V1, O1, E1);

	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("Temps pour 200 SD: %f\n", total_t);
}
