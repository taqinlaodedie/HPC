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
#include "test_mouvement.h"
#include "mymacro.h"
#include "sys/time.h"

void test_multi_mouvement()
{
	clock_t start_t, end_t;
	double total_t;
	start_t = clock();

	char *fname0 = (char*)malloc(sizeof(char*) * 16);
	char *fnamE1 = (char*)malloc(sizeof(char*) * 16);
	char *outfile = (char*)malloc(sizeof(char*) * 22);
	int aux;
	strcpy(fname0, "img/car_3000.pgm");
	strcpy(fnamE1, "img/car_3001.pgm");
	strcpy(outfile,"output/output_e001.pgm");
				//  012345678901234567890123

	/*uint8** ui8matrix(long nrl, long nrh, long ncl, long nch) */
	/* allocate an uint8 matrix with subscript range m[nrl..nrh][ncl..nch] */
	uint8 **I0 = ui8matrix(0, HAUT, 0, LARG);		// image source NB
	uint8 **M0 = ui8matrix(0, HAUT, 0, LARG);		// image de fond/moyenne
	uint8 **V0 = ui8matrix(0, HAUT, 0, LARG);		// image variance/d'ecart type
	uint8 **I1 = ui8matrix(0, HAUT, 0, LARG);		// image source NB
	uint8 **M1 = ui8matrix(0, HAUT, 0, LARG);		// image de fond/moyenne
	uint8 **V1 = ui8matrix(0, HAUT, 0, LARG);		// image variance/d'ecart type
	uint8 **O1 = ui8matrix(0, HAUT, 0, LARG);		// image difference
	uint8 **E1 = ui8matrix(0, HAUT, 0, LARG);		// image etiquettes
	// uint8 **ero = ui8matrix(0, HAUT, 0, LARG);		// image etiquettes
	// uint8 **dil = ui8matrix(0, HAUT, 0, LARG);		// image etiquettes

	MLoadPGM_ui8matrix(fname0, 0, HAUT, 0, LARG, I0);

	for(int i = 2; i <= 200; i++)
	{
		MLoadPGM_ui8matrix(fname0, 0, HAUT, 0, LARG, I1);
		SIGMADELTA(I0, I1, M0, M1, O1, V0, V1, E1, HAUT+1, LARG+1);
		SavePGM_ui8matrix(E1, 0, HAUT, 0, LARG, outfile);
		COPIER_MATRICES(I1, I0);
		COPIER_MATRICES(M1, M0);
		COPIER_MATRICES(V1, V0);
		strcpy(fname0, fnamE1);
		aux = (fname0[9]-'0')*100 + (fname0[10]-'0')*10 + (fname0[11]-'0') + 1;
		fnamE1[9] = outfile[15] = aux / 100 + '0';
		fnamE1[10] = outfile[16] = (aux / 10) % 10 + '0';
		fnamE1[11] = outfile[17] = aux % 10 + '0';
	}

	// void free_ui8matrix(uint8 **m, long nrl, long nrh, long ncl, long nch)
	free_ui8matrix(I0, 0, HAUT, 0, LARG);
	free_ui8matrix(M0, 0, HAUT, 0, LARG);
	free_ui8matrix(V0, 0, HAUT, 0, LARG);
	free_ui8matrix(I1, 0, HAUT, 0, LARG);
	free_ui8matrix(M1, 0, HAUT, 0, LARG);
	free_ui8matrix(V1, 0, HAUT, 0, LARG);
	free_ui8matrix(O1, 0, HAUT, 0, LARG);
	free_ui8matrix(E1, 0, HAUT, 0, LARG);
	// free_ui8matrix(ero, 0, HAUT, 0, LARG);
	// free_ui8matrix(dil, 0, HAUT, 0, LARG);

	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("Temps pour 200 SD: %f\n", total_t);
}
