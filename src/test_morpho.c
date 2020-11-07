#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "nrdef.h"
#include "nrutil.h"
#include "morpho.h"
#include "test_morpho.h"

void test_morpho()
{
	char *fname0 = "output_mouvement.pgm";
	uint8 **I0 = ui8matrix(-1, 321, -1, 241);
	uint8 **I1 = ui8matrix(-1, 321, -1, 241);

	MLoadPGM_ui8matrix(fname0, -1, 321, -1, 241, I0);

	erosion(I0, I1, 320, 240);
	SavePGM_ui8matrix(I1, 0, 320, 0, 240, "erosion1.pgm");
	dilatation(I1, I0, 320, 240);
	SavePGM_ui8matrix(I0, 0, 320, 0, 240, "dilatation1.pgm");
	dilatation(I0, I1, 320, 240);
	SavePGM_ui8matrix(I1, 0, 320, 0, 240, "dilatation2.pgm");
	erosion(I1, I0, 320, 240);
	SavePGM_ui8matrix(I0, 0, 320, 0, 240, "erosion2.pgm");
}