#ifndef MORPHO_SIMD_H
#define MORPHO_SIMD_H

#include "vnrdef.h"

void erosion_SIMD(vuint8 **img_src, vuint8 **img_dst, int m, int n);
void dilatation_SIMD(vuint8 **img_src, vuint8 **img_dst, int m, int n);
void dilatation5_SIMD(vuint8 **img_src, vuint8 **img_dst, int m, int n);
void erosion_SIMD_factorisee(vuint8 **img_src, vuint8 **img_dst, int m, int n);
void dilatation_SIMD_factorisee(vuint8 **img_src, vuint8 **img_dst, int m, int n);
void dilatation5_SIMD_factorisee(vuint8 **img_src, vuint8 **img_dst, vuint8 **tmp, int m, int n);
// void morpho_SIMD_pipeline(vuint8 **img_src, vuint8 **erosion1, vuint8 **dilatation1, vuint8 **dilatation2, vuint8 **img_dst, int m, int n);

#endif