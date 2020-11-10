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
	char *fname0 = (char*)malloc(sizeof(char*) * 16);
	char *fname1 = (char*)malloc(sizeof(char*) * 16);
	char *outfile= (char*)malloc(sizeof(char*) * 22);
	int aux;
	strcpy(fname0, "img/car_3000.pgm");
	strcpy(fname1, "img/car_3001.pgm");
	strcpy(outfile,"output/output_e001.pgm");
				//  012345678901234567890123

	uint8 **I0 = ui8matrix(0, HAUT, 0, LARG);
	uint8 **I1 = ui8matrix(0, HAUT, 0, LARG);
	uint8 **M0 = ui8matrix(0, HAUT, 0, LARG);
	uint8 **M1 = ui8matrix(0, HAUT, 0, LARG);
	uint8 **O1 = ui8matrix(0, HAUT, 0, LARG);
	uint8 **V0 = ui8matrix(0, HAUT, 0, LARG);
	uint8 **V1 = ui8matrix(0, HAUT, 0, LARG);
	uint8 **E1 = ui8matrix(0, HAUT, 0, LARG);

	MLoadPGM_ui8matrix(fname0, 0, HAUT, 0, LARG, I0);

	for(int i = 2; i <= 200; i++)
	{
		// printf("iter %d\n", i);
		// printf("fname0 : %s\n", fname0);
		// printf("fname1 : %s\n", fname1);
		// printf("outfile: %s\n", outfile);
		MLoadPGM_ui8matrix(fname1, 0, HAUT, 0, LARG, I1);
		SIGMADELTA(I0, I1, M0, M1, O1, V0, V1, E1, 2);
		SavePGM_ui8matrix(E1, 0, HAUT, 0, LARG, outfile);
		COPIER_MATRICES(I1, I0);
		COPIER_MATRICES(M1, M0);
		COPIER_MATRICES(V1, V0);
		strcpy(fname0, fname1);
		aux = (fname0[9]-'0')*100 + (fname0[10]-'0')*10 + (fname0[11]-'0') + 1;
		fname1[9] = outfile[15] = aux / 100 + '0';
		fname1[10] = outfile[16] = (aux / 10) % 10 + '0';
		fname1[11] = outfile[17] = aux % 10 + '0';
	}


	// MLoadPGM_ui8matrix(outfile, 0, HAUT, 0, LARG, I0);
	// MLoadPGM_ui8matrix("output_sd_SIMD.pgm", 0, HAUT, 0, LARG, I1);
	// for (int i = 0; i < HAUT; i++) {
	// 	for (int j = 0; j < LARG; j++) {
	// 		I0[i][j] -= I1[i][j];
	// 	}
	// }
	// SavePGM_ui8matrix(I0, 0, HAUT, 0, LARG, "diff.pgm");

	free_ui8matrix(I0, 0, HAUT, 0, LARG);
	free_ui8matrix(I1, 0, HAUT, 0, LARG);
	free_ui8matrix(M0, 0, HAUT, 0, LARG);
	free_ui8matrix(M1, 0, HAUT, 0, LARG);
	free_ui8matrix(O1, 0, HAUT, 0, LARG);
	free_ui8matrix(V0, 0, HAUT, 0, LARG);
	free_ui8matrix(V1, 0, HAUT, 0, LARG);
	free_ui8matrix(E1, 0, HAUT, 0, LARG);
}
