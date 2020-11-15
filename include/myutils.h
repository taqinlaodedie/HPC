#ifndef MYUTILS_H
#define MYUTILS_H

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
#include "mymacro.h"

void MLoadPGM_vui8matrix(char *filename, int nrl, int nrh, int ncl, int nch, vuint8 **m);
void SavePGM_vui8matrix(vuint8 **m, int nrl, int nrh, int ncl, int nch, char *filename);
void copy_3_vui8matrix_vui8matrix(vuint8 **src1, vuint8 **dst1, vuint8 **src2, vuint8 **dst2, vuint8 **src3, vuint8 **dst3, int i0, int i1, int j0, int j1);

#endif
