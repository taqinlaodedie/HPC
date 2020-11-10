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
#include "mymacro.h"

void test_morpho()
{
	char *fname0 = "output_mouvement.pgm";
	uint8 **I0 = ui8matrix(-1, HAUT+1, -1, LARG+1);
	uint8 **I1 = ui8matrix(-1, HAUT+1, -1, LARG+1);

	MLoadPGM_ui8matrix(fname0, -1, 321, -1, 241, I0);

	erosion(I0, I1, HAUT, LARG);
	SavePGM_ui8matrix(I1, 0, HAUT, 0, LARG, "erosion1.pgm");
	dilatation(I1, I0, HAUT, LARG);
	SavePGM_ui8matrix(I0, 0, HAUT, 0, LARG, "dilatation1.pgm");
	dilatation(I0, I1, HAUT, LARG);
	SavePGM_ui8matrix(I1, 0, HAUT, 0, LARG, "dilatation2.pgm");
	erosion(I1, I0, HAUT, LARG);
	SavePGM_ui8matrix(I0, 0, HAUT, 0, LARG, "erosion2.pgm");

	free_ui8matrix(I0, -1, 321, -1, 241);
	free_ui8matrix(I1, -1, 321, -1, 241);
}
