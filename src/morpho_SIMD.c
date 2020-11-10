#include <stdio.h>
#include <stdlib.h>
#include "mymacro.h"
#include "nrdef.h"
#include "nrutil.h"
#include "vnrdef.h"
#include "vnrutil.h"
#include "morpho_SIMD.h"

// Dans ce fichier: n est le nombre de colonne et m est le nombre de ligne
void erosion_SIMD(vuint8 **img_src, vuint8 **img_dst, int m, int n)
{
	int i, j;
	vuint8 a0, a1, a2, b0, b1, b2, c0, c1, c2, s0, s1, s2, s;	// Registres alignes
	vuint8 a10, a12, b10, b12, c10, c12;	// Registres non alignes

	a0 = _mm_load_si128((vuint8 *)&img_src[-1][-1]);
	a1 = _mm_load_si128((vuint8 *)&img_src[-1][0]);
	b0 = _mm_load_si128((vuint8 *)&img_src[0][-1]);
	b1 = _mm_load_si128((vuint8 *)&img_src[0][0]);
	for (i = 0; i < m; i++) {
		c0 = _mm_load_si128((vuint8 *)&img_src[i+1][-1]);
		c1 = _mm_load_si128((vuint8 *)&img_src[i+1][0]);
		for (j = 0; j < n; j++) {
			a2 = _mm_load_si128((vuint8 *)&img_src[i-1][j+1]);
			b2 = _mm_load_si128((vuint8 *)&img_src[i][j+1]);
			c2 = _mm_load_si128((vuint8 *)&img_src[i+1][j+1]);

			a10 = FIFTEEN_R(a0, a1);
			a12 = FIFTEEN_L(a1, a2);
			b10 = FIFTEEN_R(b0, b1);
			b12 = FIFTEEN_L(b1, b2);
			c10 = FIFTEEN_R(c0, c1);
			c12 = FIFTEEN_L(c1, c2);

			s0 = AND_THREE_VAL(a10, a1, a12);
			s1 = AND_THREE_VAL(b10, b1, b12);
			s2 = AND_THREE_VAL(c10, c1, c12);
			s = AND_THREE_VAL(s0, s1, s2);

			_mm_store_si128((vuint8 *)&img_dst[i][j], s);

			a0 = a1; a1 = a2;
			b0 = b1; b1 = b2;
			c0 = c1; c1 = c2;
		}
		a0 = b0; a1 = b1; a2 = b2;
		b0 = c0; b1 = c1; b2 = c2;
	}
}

void dilatation_SIMD(vuint8 **img_src, vuint8 **img_dst, int m, int n)
{
	int i, j;
	vuint8 a0, a1, a2, b0, b1, b2, c0, c1, c2, s0, s1, s2, s;	// Registres alignes
	vuint8 a10, a12, b10, b12, c10, c12;	// Registres non alignes

	a0 = _mm_load_si128((vuint8 *)&img_src[-1][-1]);
	a1 = _mm_load_si128((vuint8 *)&img_src[-1][0]);
	b0 = _mm_load_si128((vuint8 *)&img_src[0][-1]);
	b1 = _mm_load_si128((vuint8 *)&img_src[0][0]);
	for (i = 0; i < m; i++) {
		c0 = _mm_load_si128((vuint8 *)&img_src[i+1][-1]);
		c1 = _mm_load_si128((vuint8 *)&img_src[i+1][0]);
		for (j = 0; j < n; j++) {
			a2 = _mm_load_si128((vuint8 *)&img_src[i-1][j+1]);
			b2 = _mm_load_si128((vuint8 *)&img_src[i][j+1]);
			c2 = _mm_load_si128((vuint8 *)&img_src[i+1][j+1]);

			a10 = FIFTEEN_R(a0, a1);
			a12 = FIFTEEN_L(a1, a2);
			b10 = FIFTEEN_R(b0, b1);
			b12 = FIFTEEN_L(b1, b2);
			c10 = FIFTEEN_R(c0, c1);
			c12 = FIFTEEN_L(c1, c2);

			s0 = OR_THREE_VAL(a10, a1, a12);
			s1 = OR_THREE_VAL(b10, b1, b12);
			s2 = OR_THREE_VAL(c10, c1, c12);
			s = OR_THREE_VAL(s0, s1, s2);

			_mm_store_si128((vuint8 *)&img_dst[i][j], s);

			a0 = a1; a1 = a2;
			b0 = b1; b1 = b2;
			c0 = c1; c1 = c2;
		}
		a0 = b0; a1 = b1; a2 = b2;
		b0 = c0; b1 = c1; b2 = c2;
	}
}