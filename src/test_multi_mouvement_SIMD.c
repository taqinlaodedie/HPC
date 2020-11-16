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
#include "mouvement_SIMD.h"
#include "test_multi_mouvement_SIMD.h"
#include "mymacro.h"
#include "myutils.h"
#include "sys/time.h"

void test_multi_mouvement_SIMD()
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
	vuint8 **I0 = vui8matrix(0, HAUT, 0, LARSIMD);		// image source NB
	vuint8 **M0 = vui8matrix(0, HAUT, 0, LARSIMD);		// image de fond/moyenne
	vuint8 **V0 = vui8matrix(0, HAUT, 0, LARSIMD);		// image variance/d'ecart type
	vuint8 **I1 = vui8matrix(0, HAUT, 0, LARSIMD);		// image source NB
	vuint8 **M1 = vui8matrix(0, HAUT, 0, LARSIMD);		// image de fond/moyenne
	vuint8 **V1 = vui8matrix(0, HAUT, 0, LARSIMD);		// image variance/d'ecart type
	vuint8 **O1 = vui8matrix(0, HAUT, 0, LARSIMD);		// image difference
	vuint8 **E1 = vui8matrix(0, HAUT, 0, LARSIMD);		// image etiquettes

	MLoadPGM_vui8matrix(fname0, 0, HAUT, 0, LARG, I0);

	for(int i = 2; i <= 200; i++)
	{
		MLoadPGM_vui8matrix(fname0, 0, HAUT, 0, LARG, I1);
		SigmaDelta_step0_SIMD(M0, I0, V0, HAUT+1, LARSIMD+1);
		SigmaDelta_1step_SIMD(M1, M0, I1, O1, V1, V0, E1, HAUT+1, LARSIMD+1);
		SavePGM_vui8matrix(E1, 0, HAUT, 0, LARG, outfile);
		copy_3_vui8matrix_vui8matrix(I1, I0, M1, M0, V0, V1, 0, 0, HAUT, LARSIMD);
		strcpy(fname0, fnamE1);
		aux = (fname0[9]-'0')*100 + (fname0[10]-'0')*10 + (fname0[11]-'0') + 1;
		fnamE1[9] = outfile[15] = aux / 100 + '0';
		fnamE1[10] = outfile[16] = (aux / 10) % 10 + '0';
		fnamE1[11] = outfile[17] = aux % 10 + '0';
	}

	// void free_ui8matrix(uint8 **m, long nrl, long nrh, long ncl, long nch)
	free_vui8matrix(I0, 0, HAUT, 0, LARSIMD);
	free_vui8matrix(M0, 0, HAUT, 0, LARSIMD);
	free_vui8matrix(V0, 0, HAUT, 0, LARSIMD);
	free_vui8matrix(I1, 0, HAUT, 0, LARSIMD);
	free_vui8matrix(M1, 0, HAUT, 0, LARSIMD);
	free_vui8matrix(V1, 0, HAUT, 0, LARSIMD);
	free_vui8matrix(O1, 0, HAUT, 0, LARSIMD);
	free_vui8matrix(E1, 0, HAUT, 0, LARSIMD);

	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("Temps pour 200 SD en SIMD: %f\n", total_t);
}
