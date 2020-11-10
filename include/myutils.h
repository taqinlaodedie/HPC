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

#endif