#ifndef MORPHO_SIMD_H
#define MORPHO_SIMD_H

#include "vnrdef.h"

void erosion_SIMD(vuint8 **img_src, vuint8 **img_dst, int m, int n);
void dilatation_SIMD(vuint8 **img_src, vuint8 **img_dst, int m, int n);

#endif