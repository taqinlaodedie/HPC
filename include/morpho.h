#ifndef MORPHO_H
#define MORPHO_H

#include "nrdef.h"

void erosion(uint8 **img_src, uint8 **img_dst, int m, int n);
void dilatation(uint8 **img_src, uint8 **img_dst, int m, int n);

#endif