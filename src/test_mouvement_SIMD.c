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
#include "test_mouvement_SIMD.h"
#include "mymacro.h"
#include "myutils.h"
#include "sys/time.h"

void test_mouvement_SIMD()
{
	struct timeval t1, t2;
	double timeused;
	char *fname0 = "test_img/test1.pgm";
	char *fname1 = "test_img/test2.pgm";
	char *outfile = "test_img/mouvement/output_SIMD.pgm";
	vuint8 **I0 = vui8matrix(0, IMG_HEIGHT-1, 0, IMG_LENGTH/16-1);
	vuint8 **I1 = vui8matrix(0, IMG_HEIGHT-1, 0, IMG_LENGTH/16-1);
	vuint8 **M0 = vui8matrix(0, IMG_HEIGHT-1, 0, IMG_LENGTH/16-1);
	vuint8 **M1 = vui8matrix(0, IMG_HEIGHT-1, 0, IMG_LENGTH/16-1);
	vuint8 **O1 = vui8matrix(0, IMG_HEIGHT-1, 0, IMG_LENGTH/16-1);
	vuint8 **V0 = vui8matrix(0, IMG_HEIGHT-1, 0, IMG_LENGTH/16-1);
	vuint8 **V1 = vui8matrix(0, IMG_HEIGHT-1, 0, IMG_LENGTH/16-1);
	vuint8 **E1 = vui8matrix(0, IMG_HEIGHT-1, 0, IMG_LENGTH/16-1);

	MLoadPGM_vui8matrix(fname0, 0, IMG_HEIGHT, 0, IMG_LENGTH-1, I0);
	MLoadPGM_vui8matrix(fname1, 0, IMG_HEIGHT, 0, IMG_LENGTH-1, I1);

	SigmaDelta_step0_SIMD(M0, I0, V0, IMG_HEIGHT, IMG_LENGTH/16);
	CHRONO(SigmaDelta_1step_SIMD(M1, M0, I1, O1, V1, V0, E1, IMG_HEIGHT, IMG_LENGTH/16), "SD 576*576 en SIMD");

	SavePGM_vui8matrix(E1, 0, IMG_HEIGHT-1, 0, IMG_LENGTH-1, outfile);

	free_vui8matrix(I0, 0, IMG_HEIGHT-1, 0, IMG_LENGTH/16-1);
	free_vui8matrix(I1, 0, IMG_HEIGHT-1, 0, IMG_LENGTH/16-1);
	free_vui8matrix(M0, 0, IMG_HEIGHT-1, 0, IMG_LENGTH/16-1);
	free_vui8matrix(M1, 0, IMG_HEIGHT-1, 0, IMG_LENGTH/16-1);
	free_vui8matrix(O1, 0, IMG_HEIGHT-1, 0, IMG_LENGTH/16-1);
	free_vui8matrix(V0, 0, IMG_HEIGHT-1, 0, IMG_LENGTH/16-1);
	free_vui8matrix(V1, 0, IMG_HEIGHT-1, 0, IMG_LENGTH/16-1);
	free_vui8matrix(E1, 0, IMG_HEIGHT-1, 0, IMG_LENGTH/16-1);
}

void test_multi_mouvement_SIMD()
{
	clock_t start_t, end_t;
	double total_t;
	start_t = clock();

	char *fname0  = (char*)malloc(sizeof(char*) * 16);
	char *fname1  = (char*)malloc(sizeof(char*) * 16);
	char *outfile = (char*)malloc(sizeof(char*) * 29);
	int aux;
	strcpy(fname0, "img/car_3000.pgm");
	strcpy(fname1, "img/car_3001.pgm");
	strcpy(outfile,"output/3_sigdel_SIMD_e001.pgm");
				//  012345678901234567890123456789

	INIT_VMATRICES(I0, M0, V0, I1, M1, V1, O1, E1);

	MLoadPGM_vui8matrix(fname0, 0, HAUT, 0, LARG, I0);
	SigmaDelta_step0_SIMD(M0, I0, V0, HAUT+1, LARSIMD+1);

	for(int i = 2; i <= 200; i++)
	{
		MLoadPGM_vui8matrix(fname1, 0, HAUT, 0, LARG, I1);
		SigmaDelta_1step_SIMD(M1, M0, I1, O1, V1, V0, E1, HAUT+1, LARSIMD+1);
		SavePGM_vui8matrix(E1, 0, HAUT, 0, LARG, outfile);
		copy_3_vui8matrix_vui8matrix(I1, I0, M1, M0, V0, V1, 0, 0, HAUT, LARSIMD);
		strcpy(fname0, fname1);
		aux = (fname0[9]-'0')*100 + (fname0[10]-'0')*10 + (fname0[11]-'0') + 1;
		fname1[ 9] = outfile[22] = aux / 100 + '0';
		fname1[10] = outfile[23] = (aux / 10) % 10 + '0';
		fname1[11] = outfile[24] = aux % 10 + '0';
	}

	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("Temps pour 200 SD en SIMD\t\t\t\t: %f s\n", total_t);

	free(fname0);
	free(fname1);
	free(outfile);
	FREE_VMATRICES(I0, M0, V0, I1, M1, V1, O1, E1);
}
