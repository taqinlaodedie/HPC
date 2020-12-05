#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
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
	CHRONO(SigmaDelta_1step_SIMD(M1, M0, I1, O1, V1, V0, E1, IMG_HEIGHT, IMG_LENGTH/16), "SD en SIMD");

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
