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

void erosion_SIMD_factorisee(vuint8 **img_src, vuint8 **img_dst, int m, int n)
{
	int i, j;
	vuint8 a0, a1, a2, s;	// Registres alignes
	vuint8 a10, a12;	// Registres non alignes

	for (j = 0; j < n; j++) {
		a0 = _mm_load_si128((vuint8 *)&img_src[-1][j]);
		a1 = _mm_load_si128((vuint8 *)&img_src[0][j]);
		for (i = 0; i < m; i++) {
			a2 = _mm_load_si128((vuint8 *)&img_src[i+1][j]);

			s = AND_THREE_VAL(a0, a1, a2);

			_mm_store_si128((vuint8 *)&img_dst[i][j], s);

			a0 = a1;
			a1 = a2;
		}
	}

	for (i = 0; i < m; i++) {
		a0 = _mm_load_si128((vuint8 *)&img_src[i][-1]);
		a1 = _mm_load_si128((vuint8 *)&img_src[i][0]);
		for (j = 0; j < n; j++) {
			a2 = _mm_load_si128((vuint8 *)&img_src[i][j+1]);

			a10 = FIFTEEN_R(a0, a1);
			a12 = FIFTEEN_L(a1, a2);

			s = AND_THREE_VAL(a10, a1, a12);

			_mm_store_si128((vuint8 *)&img_dst[i][j], s);

			a0 = a1;
			a1 = a2;
		}
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

void dilatation_SIMD_factorisee(vuint8 **img_src, vuint8 **img_dst, int m, int n)
{
	int i, j;
	vuint8 a0, a1, a2, s;	// Registres alignes
	vuint8 a10, a12;	// Registres non alignes

	for (j = 0; j < n; j++) {
		a0 = _mm_load_si128((vuint8 *)&img_src[-1][j]);
		a1 = _mm_load_si128((vuint8 *)&img_src[0][j]);
		for (i = 0; i < m; i++) {
			a2 = _mm_load_si128((vuint8 *)&img_src[i+1][j]);

			s = OR_THREE_VAL(a0, a1, a2);

			_mm_store_si128((vuint8 *)&img_dst[i][j], s);

			a0 = a1;
			a1 = a2;
		}
	}

	for (i = 0; i < m; i++) {
		a0 = _mm_load_si128((vuint8 *)&img_src[i][-1]);
		a1 = _mm_load_si128((vuint8 *)&img_src[i][0]);
		for (j = 0; j < n; j++) {
			a2 = _mm_load_si128((vuint8 *)&img_src[i][j+1]);

			a10 = FIFTEEN_R(a0, a1);
			a12 = FIFTEEN_L(a1, a2);

			s = OR_THREE_VAL(a10, a1, a12);

			_mm_store_si128((vuint8 *)&img_dst[i][j], s);

			a0 = a1;
			a1 = a2;
		}
	}
}

// Dilatation en version 5*5
void dilatation5_SIMD(vuint8 **img_src, vuint8 **img_dst, int m, int n)
{
	int i, j;
	vuint8 a0, a1, a2, b0, b1, b2, c0, c1, c2, d0, d1, d2, e0, e1, e2, s0, s1, s2, s3, s4, s;	// Registres alignes
	vuint8 a010, a10, a12, a122, b010, b10, b12, b122, c010, c10, c12, c122, d010, d10, d12, d122, e010, e10, e12, e122;	// Registres non alignes

	a0 = _mm_load_si128((vuint8 *)&img_src[-2][-1]);
	a1 = _mm_load_si128((vuint8 *)&img_src[-2][0]);
	b0 = _mm_load_si128((vuint8 *)&img_src[-1][-1]);
	b1 = _mm_load_si128((vuint8 *)&img_src[-1][0]);
	c0 = _mm_load_si128((vuint8 *)&img_src[0][-1]);
	c1 = _mm_load_si128((vuint8 *)&img_src[0][0]);
	d0 = _mm_load_si128((vuint8 *)&img_src[1][-1]);
	d1 = _mm_load_si128((vuint8 *)&img_src[1][0]);
	for (i = 0; i < m; i++) {
		e0 = _mm_load_si128((vuint8 *)&img_src[i+2][-1]);
		e1 = _mm_load_si128((vuint8 *)&img_src[i+2][0]);
		for (j = 0; j < n; j++) {
			a2 = _mm_load_si128((vuint8 *)&img_src[i-2][j+1]);
			b2 = _mm_load_si128((vuint8 *)&img_src[i-1][j+1]);
			c2 = _mm_load_si128((vuint8 *)&img_src[i][j+1]);
			d2 = _mm_load_si128((vuint8 *)&img_src[i+2][j+1]);
			e2 = _mm_load_si128((vuint8 *)&img_src[i+2][j+1]);

			a10 = FIFTEEN_R(a0, a1);
			a12 = FIFTEEN_L(a1, a2);
			a010 = FOURTEEN_R(a0, a1);
			a122 = FOURTEEN_L(a1, a2);
			b10 = FIFTEEN_R(b0, b1);
			b12 = FIFTEEN_L(b1, b2);
			b010 = FOURTEEN_R(b0, b1);
			b122 = FOURTEEN_L(b1, b2);
			c10 = FIFTEEN_R(c0, c1);
			c12 = FIFTEEN_L(c1, c2);
			c010 = FOURTEEN_R(c0, c1);
			c122 = FOURTEEN_L(c1, c2);
			d10 = FIFTEEN_R(d0, d1);
			d12 = FIFTEEN_L(d1, d2);
			d010 = FOURTEEN_R(d0, d1);
			d122 = FOURTEEN_L(d1, d2);
			e10 = FIFTEEN_R(e0, e1);
			e12 = FIFTEEN_L(e1, e2);
			e010 = FOURTEEN_R(e0, e1);
			e122 = FOURTEEN_L(e1, e2);

			s0 = OR_FIVE_VAL(a010, a10, a1, a12, a122);
			s1 = OR_FIVE_VAL(b010, b10, b1, b12, b122);
			s2 = OR_FIVE_VAL(c010, c10, c1, c12, c122);
			s3 = OR_FIVE_VAL(d010, d10, d1, d12, d122);
			s4 = OR_FIVE_VAL(e010, e10, e1, e12, e122);
			s = OR_FIVE_VAL(s0, s1, s2, s3, s4);

			_mm_store_si128((vuint8 *)&img_dst[i][j], s);

			a0 = a1; a1 = a2; 
			b0 = b1; b1 = b2;
			c0 = c1; c1 = c2;
			d0 = d1; d1 = d2;
			e0 = e1; e1 = e2;
		}
		a0 = b0; a1 = b1; a2 = b2;
		b0 = c0; b1 = c1; b2 = c2;
		c0 = d0; c1 = d1; c2 = d2;
		d0 = e0; d1 = e1; d2 = e2;
	}
}

// Dilatation en version 5*5
void dilatation5_SIMD_factorisee(vuint8 **img_src, vuint8 **img_dst, vuint8 **tmp, int m, int n)
{
	int i, j;
	vuint8 a0, a1, a2, a3, a4, s;	// Registres alignes
	vuint8 a010, a10, a12, a122, b010, b10, b12, b122, c010, c10, c12, c122, d010, d10, d12, d122, e010, e10, e12, e122;	// Registres non alignes

	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			a0 = _mm_load_si128((vuint8 *)&img_src[i-2][j]);
			a1 = _mm_load_si128((vuint8 *)&img_src[i-1][j]);
			a2 = _mm_load_si128((vuint8 *)&img_src[i][j]);
			a3 = _mm_load_si128((vuint8 *)&img_src[i+1][j]);
			a4 = _mm_load_si128((vuint8 *)&img_src[i+2][j]);

			s = OR_FIVE_VAL(a0, a1, a2, a3, a4);

			_mm_store_si128((vuint8 *)&tmp[i][j], s);
		}
	}

	for (i = 0; i < m; i++) {
		a0 = _mm_load_si128((vuint8 *)&tmp[i][-1]);
		a1 = _mm_load_si128((vuint8 *)&tmp[i][0]);
		for (j = 0; j < n; j++) {
			a2 = _mm_load_si128((vuint8 *)&tmp[i][j+1]);

			a10 = FIFTEEN_R(a0, a1);
			a12 = FIFTEEN_L(a1, a2);
			a010 = FOURTEEN_R(a0, a1);
			a122 = FOURTEEN_L(a1, a2);

			s = OR_FIVE_VAL(a010, a10, a1, a12, a122);

			_mm_store_si128((vuint8 *)&img_dst[i][j], s);

			a0 = a1; 
			a1 = a2; 
			a2 = a3;
			a3 = a4;
		}
	}
}

// void morpho_SIMD_pipeline(vuint8 **img_src, vuint8 **erosion1, vuint8 **dilatation1, vuint8 **dilatation2, vuint8 **img_dst, int m, int n)
// {
// 	int i, j;
// 	vuint8 e1a0, e1a1, e1a2, e1b0, e1b1, e1b2, e1c0, e1c1, e1c2, 
// 		d1a0, d1a1, d1a2, d1b0, d1b1, d1b2, d1c0, d1c1, d1c2, 
// 		d2a0, d2a1, d2a2, d2b0, d2b1, d2b2, d2c0, d2c1, d2c2, 
// 		e2a0, e2a1, e2a2, e2b0, e2b1, e2b2, e2c0, e2c1, e2c2, s0, s1, s2, s;	// Registres alignes
// 	vuint8 a10, a12, b10, b12, c10, c12;	// Registres non alignes

// 	// Prologue
// 	// Erosion 1
// 	e1a0 = _mm_load_si128((vuint8 *)&img_src[-1][-1]);
// 	e1a1 = _mm_load_si128((vuint8 *)&img_src[-1][0]);
// 	e1b0 = _mm_load_si128((vuint8 *)&img_src[0][-1]);
// 	e1b1 = _mm_load_si128((vuint8 *)&img_src[0][0]);
// 	for (i = 0; i < 3; i++) {
// 		e1c0 = _mm_load_si128((vuint8 *)&img_src[i+1][-1]);
// 		e1c1 = _mm_load_si128((vuint8 *)&img_src[i+1][0]);
// 		for (j = 0; j < n; j++) {
// 			e1a2 = _mm_load_si128((vuint8 *)&img_src[i-1][j+1]);
// 			e1b2 = _mm_load_si128((vuint8 *)&img_src[i][j+1]);
// 			e1c2 = _mm_load_si128((vuint8 *)&img_src[i+1][j+1]);

// 			a10 = FIFTEEN_R(e1a0, e1a1);
// 			a12 = FIFTEEN_L(e1a1, e1a2);
// 			b10 = FIFTEEN_R(e1b0, e1b1);
// 			b12 = FIFTEEN_L(e1b1, e1b2);
// 			c10 = FIFTEEN_R(e1c0, e1c1);
// 			c12 = FIFTEEN_L(e1c1, e1c2);

// 			s0 = AND_THREE_VAL(a10, e1a1, a12);
// 			s1 = AND_THREE_VAL(b10, e1b1, b12);
// 			s2 = AND_THREE_VAL(c10, e1c1, c12);
// 			s = AND_THREE_VAL(s0, s1, s2);

// 			_mm_store_si128((vuint8 *)&erosion1[i][j], s);

// 			e1a0 = e1a1; e1a1 = e1a2;
// 			e1b0 = e1b1; e1b1 = e1b2;
// 			e1c0 = e1c1; e1c1 = e1c2;
// 		}
// 		e1a0 = e1b0; e1a1 = e1b1; e1a2 = e1b2;
// 		e1b0 = e1c0; e1b1 = e1c1; e1b2 = e1c2;
// 	}

// 	// Dilatation 1
// 	d1a0 = _mm_load_si128((vuint8 *)&erosion1[-1][-1]);
// 	d1a1 = _mm_load_si128((vuint8 *)&erosion1[-1][0]);
// 	d1b0 = _mm_load_si128((vuint8 *)&erosion1[0][-1]);
// 	d1b1 = _mm_load_si128((vuint8 *)&erosion1[0][0]);
// 	for (i = 0; i < 2; i++) {
// 		d1c0 = _mm_load_si128((vuint8 *)&erosion1[i+1][-1]);
// 		d1c1 = _mm_load_si128((vuint8 *)&erosion1[i+1][0]);
// 		for (j = 0; j < n; j++) {
// 			d1a2 = _mm_load_si128((vuint8 *)&erosion1[i-1][j+1]);
// 			d1b2 = _mm_load_si128((vuint8 *)&erosion1[i][j+1]);
// 			d1c2 = _mm_load_si128((vuint8 *)&erosion1[i+1][j+1]);

// 			a10 = FIFTEEN_R(d1a0, d1a1);
// 			a12 = FIFTEEN_L(d1a1, d1a2);
// 			b10 = FIFTEEN_R(d1b0, d1b1);
// 			b12 = FIFTEEN_L(d1b1, d1b2);
// 			c10 = FIFTEEN_R(d1c0, d1c1);
// 			c12 = FIFTEEN_L(d1c1, d1c2);

// 			s0 = OR_THREE_VAL(a10, d1a1, a12);
// 			s1 = OR_THREE_VAL(b10, d1b1, b12);
// 			s2 = OR_THREE_VAL(c10, d1c1, c12);
// 			s = OR_THREE_VAL(s0, s1, s2);

// 			_mm_store_si128((vuint8 *)&dilatation1[i][j], s);

// 			d1a0 = d1a1; d1a1 = d1a2;
// 			d1b0 = d1b1; d1b1 = d1b2;
// 			d1c0 = d1c1; d1c1 = d1c2;
// 		}
// 		d1a0 = d1b0; d1a1 = d1b1; d1a2 = d1b2;
// 		d1b0 = d1c0; d1b1 = d1c1; d1b2 = d1c2;
// 	}

// 	// Dilatation 2
// 	d2a0 = _mm_load_si128((vuint8 *)&dilatation1[-1][-1]);
// 	d2a1 = _mm_load_si128((vuint8 *)&dilatation1[-1][0]);
// 	d2b0 = _mm_load_si128((vuint8 *)&dilatation1[0][-1]);
// 	d2b1 = _mm_load_si128((vuint8 *)&dilatation1[0][0]);
// 	for (i = 0; i < 1; i++) {
// 		d2c0 = _mm_load_si128((vuint8 *)&dilatation1[i+1][-1]);
// 		d2c1 = _mm_load_si128((vuint8 *)&dilatation1[i+1][0]);
// 		for (j = 0; j < n; j++) {
// 			d2a2 = _mm_load_si128((vuint8 *)&dilatation1[i-1][j+1]);
// 			d2b2 = _mm_load_si128((vuint8 *)&dilatation1[i][j+1]);
// 			d2c2 = _mm_load_si128((vuint8 *)&dilatation1[i+1][j+1]);

// 			a10 = FIFTEEN_R(d2a0, d2a1);
// 			a12 = FIFTEEN_L(d2a1, d2a2);
// 			b10 = FIFTEEN_R(d2b0, d2b1);
// 			b12 = FIFTEEN_L(d2b1, d2b2);
// 			c10 = FIFTEEN_R(d2c0, d2c1);
// 			c12 = FIFTEEN_L(d2c1, d2c2);

// 			s0 = OR_THREE_VAL(a10, d2a1, a12);
// 			s1 = OR_THREE_VAL(b10, d2b1, b12);
// 			s2 = OR_THREE_VAL(c10, d2c1, c12);
// 			s = OR_THREE_VAL(s0, s1, s2);

// 			_mm_store_si128((vuint8 *)&dilatation2[i][j], s);

// 			d2a0 = d2a1; d2a1 = d2a2;
// 			d2b0 = d2b1; d2b1 = d2b2;
// 			d2c0 = d2c1; d2c1 = d2c2;
// 		}
// 		d2a0 = d2b0; d2a1 = d2b1; d2a2 = d2b2;
// 		d2b0 = d2c0; d2b1 = d2c1; d2b2 = d2c2;
// 	}

// 	// Pipeline
// 	for (i = 3; i < m; i++) {
// 		// Erosion 1
// 		e1c0 = _mm_load_si128((vuint8 *)&img_src[i+1][-1]);
// 		e1c1 = _mm_load_si128((vuint8 *)&img_src[i+1][0]);
// 		for (j = 0; j < n; j++) {
// 			e1a2 = _mm_load_si128((vuint8 *)&img_src[i-1][j+1]);
// 			e1b2 = _mm_load_si128((vuint8 *)&img_src[i][j+1]);
// 			e1c2 = _mm_load_si128((vuint8 *)&img_src[i+1][j+1]);

// 			a10 = FIFTEEN_R(e1a0, e1a1);
// 			a12 = FIFTEEN_L(e1a1, e1a2);
// 			b10 = FIFTEEN_R(e1b0, e1b1);
// 			b12 = FIFTEEN_L(e1b1, e1b2);
// 			c10 = FIFTEEN_R(e1c0, e1c1);
// 			c12 = FIFTEEN_L(e1c1, e1c2);

// 			s0 = AND_THREE_VAL(a10, e1a1, a12);
// 			s1 = AND_THREE_VAL(b10, e1b1, b12);
// 			s2 = AND_THREE_VAL(c10, e1c1, c12);
// 			s = AND_THREE_VAL(s0, s1, s2);

// 			_mm_store_si128((vuint8 *)&erosion1[i][j], s);

// 			e1a0 = e1a1; e1a1 = e1a2;
// 			e1b0 = e1b1; e1b1 = e1b2;
// 			e1c0 = e1c1; e1c1 = e1c2;
// 		}
// 		e1a0 = e1b0; e1a1 = e1b1; e1a2 = e1b2;
// 		e1b0 = e1c0; e1b1 = e1c1; e1b2 = e1c2;

// 		// Dilatation 1
// 		d1c0 = _mm_load_si128((vuint8 *)&erosion1[i+1][-1]);
// 		d1c1 = _mm_load_si128((vuint8 *)&erosion1[i+1][0]);
// 		for (j = 0; j < n; j++) {
// 			d1a2 = _mm_load_si128((vuint8 *)&erosion1[i-1][j+1]);
// 			d1b2 = _mm_load_si128((vuint8 *)&erosion1[i][j+1]);
// 			d1c2 = _mm_load_si128((vuint8 *)&erosion1[i+1][j+1]);

// 			a10 = FIFTEEN_R(d1a0, d1a1);
// 			a12 = FIFTEEN_L(d1a1, d1a2);
// 			b10 = FIFTEEN_R(d1b0, d1b1);
// 			b12 = FIFTEEN_L(d1b1, d1b2);
// 			c10 = FIFTEEN_R(d1c0, d1c1);
// 			c12 = FIFTEEN_L(d1c1, d1c2);

// 			s0 = OR_THREE_VAL(a10, d1a1, a12);
// 			s1 = OR_THREE_VAL(b10, d1b1, b12);
// 			s2 = OR_THREE_VAL(c10, d1c1, c12);
// 			s = OR_THREE_VAL(s0, s1, s2);

// 			_mm_store_si128((vuint8 *)&dilatation1[i][j], s);

// 			d1a0 = d1a1; d1a1 = d1a2;
// 			d1b0 = d1b1; d1b1 = d1b2;
// 			d1c0 = d1c1; d1c1 = d1c2;
// 		}
// 		d1a0 = d1b0; d1a1 = d1b1; d1a2 = d1b2;
// 		d1b0 = d1c0; d1b1 = d1c1; d1b2 = d1c2;

// 		// Dilatation 2
// 		d2c0 = _mm_load_si128((vuint8 *)&dilatation1[i+1][-1]);
// 		d2c1 = _mm_load_si128((vuint8 *)&dilatation1[i+1][0]);
// 		for (j = 0; j < n; j++) {
// 			d2a2 = _mm_load_si128((vuint8 *)&dilatation1[i-1][j+1]);
// 			d2b2 = _mm_load_si128((vuint8 *)&dilatation1[i][j+1]);
// 			d2c2 = _mm_load_si128((vuint8 *)&dilatation1[i+1][j+1]);

// 			a10 = FIFTEEN_R(d2a0, d2a1);
// 			a12 = FIFTEEN_L(d2a1, d2a2);
// 			b10 = FIFTEEN_R(d2b0, d2b1);
// 			b12 = FIFTEEN_L(d2b1, d2b2);
// 			c10 = FIFTEEN_R(d2c0, d2c1);
// 			c12 = FIFTEEN_L(d2c1, d2c2);

// 			s0 = OR_THREE_VAL(a10, d2a1, a12);
// 			s1 = OR_THREE_VAL(b10, d2b1, b12);
// 			s2 = OR_THREE_VAL(c10, d2c1, c12);
// 			s = OR_THREE_VAL(s0, s1, s2);

// 			_mm_store_si128((vuint8 *)&dilatation2[i][j], s);

// 			d2a0 = d2a1; d2a1 = d2a2;
// 			d2b0 = d2b1; d2b1 = d2b2;
// 			d2c0 = d2c1; d2c1 = d2c2;
// 		}
// 		d2a0 = d2b0; d2a1 = d2b1; d2a2 = d2b2;
// 		d2b0 = d2c0; d2b1 = d2c1; d2b2 = d2c2;

// 		// Erosion 2
// 		e2c0 = _mm_load_si128((vuint8 *)&dilatation2[i+1][-1]);
// 		e2c1 = _mm_load_si128((vuint8 *)&dilatation2[i+1][0]);
// 		for (j = 0; j < n; j++) {
// 			e2a2 = _mm_load_si128((vuint8 *)&dilatation2[i-1][j+1]);
// 			e2b2 = _mm_load_si128((vuint8 *)&dilatation2[i][j+1]);
// 			e2c2 = _mm_load_si128((vuint8 *)&dilatation2[i+1][j+1]);

// 			a10 = FIFTEEN_R(e2a0, e2a1);
// 			a12 = FIFTEEN_L(e2a1, e2a2);
// 			b10 = FIFTEEN_R(e2b0, e2b1);
// 			b12 = FIFTEEN_L(e2b1, e2b2);
// 			c10 = FIFTEEN_R(e2c0, e2c1);
// 			c12 = FIFTEEN_L(e2c1, e2c2);

// 			s0 = AND_THREE_VAL(a10, e2a1, a12);
// 			s1 = AND_THREE_VAL(b10, e2b1, b12);
// 			s2 = AND_THREE_VAL(c10, e2c1, c12);
// 			s = AND_THREE_VAL(s0, s1, s2);

// 			_mm_store_si128((vuint8 *)&img_dst[i][j], s);

// 			e2a0 = e2a1; e2a1 = e2a2;
// 			e2b0 = e2b1; e2b1 = e2b2;
// 			e2c0 = e2c1; e2c1 = e2c2;
// 		}
// 		e2a0 = e1b0; e2a1 = e2b1; e2a2 = e2b2;
// 		e2b0 = e1c0; e2b1 = e2c1; e2b2 = e2c2;
// 	}

// 	// Epilogue
// 	// Dilatation 1
// 	d1a0 = _mm_load_si128((vuint8 *)&erosion1[-1][-1]);
// 	d1a1 = _mm_load_si128((vuint8 *)&erosion1[-1][0]);
// 	d1b0 = _mm_load_si128((vuint8 *)&erosion1[0][-1]);
// 	d1b1 = _mm_load_si128((vuint8 *)&erosion1[0][0]);
// 	for (i = m-2; i < m; i++) {
// 		d1c0 = _mm_load_si128((vuint8 *)&erosion1[i+1][-1]);
// 		d1c1 = _mm_load_si128((vuint8 *)&erosion1[i+1][0]);
// 		for (j = 0; j < n; j++) {
// 			d1a2 = _mm_load_si128((vuint8 *)&erosion1[i-1][j+1]);
// 			d1b2 = _mm_load_si128((vuint8 *)&erosion1[i][j+1]);
// 			d1c2 = _mm_load_si128((vuint8 *)&erosion1[i+1][j+1]);

// 			a10 = FIFTEEN_R(d1a0, d1a1);
// 			a12 = FIFTEEN_L(d1a1, d1a2);
// 			b10 = FIFTEEN_R(d1b0, d1b1);
// 			b12 = FIFTEEN_L(d1b1, d1b2);
// 			c10 = FIFTEEN_R(d1c0, d1c1);
// 			c12 = FIFTEEN_L(d1c1, d1c2);

// 			s0 = OR_THREE_VAL(a10, d1a1, a12);
// 			s1 = OR_THREE_VAL(b10, d1b1, b12);
// 			s2 = OR_THREE_VAL(c10, d1c1, c12);
// 			s = OR_THREE_VAL(s0, s1, s2);

// 			_mm_store_si128((vuint8 *)&dilatation1[i][j], s);

// 			d1a0 = d1a1; d1a1 = d1a2;
// 			d1b0 = d1b1; d1b1 = d1b2;
// 			d1c0 = d1c1; d1c1 = d1c2;
// 		}
// 		d1a0 = d1b0; d1a1 = d1b1; d1a2 = d1b2;
// 		d1b0 = d1c0; d1b1 = d1c1; d1b2 = d1c2;
// 	}

// 	// Dilatation 2
// 	d2a0 = _mm_load_si128((vuint8 *)&dilatation1[-1][-1]);
// 	d2a1 = _mm_load_si128((vuint8 *)&dilatation1[-1][0]);
// 	d2b0 = _mm_load_si128((vuint8 *)&dilatation1[0][-1]);
// 	d2b1 = _mm_load_si128((vuint8 *)&dilatation1[0][0]);
// 	for (i = m-3; i < m; i++) {
// 		d2c0 = _mm_load_si128((vuint8 *)&dilatation1[i+1][-1]);
// 		d2c1 = _mm_load_si128((vuint8 *)&dilatation1[i+1][0]);
// 		for (j = 0; j < n; j++) {
// 			d2a2 = _mm_load_si128((vuint8 *)&dilatation1[i-1][j+1]);
// 			d2b2 = _mm_load_si128((vuint8 *)&dilatation1[i][j+1]);
// 			d2c2 = _mm_load_si128((vuint8 *)&dilatation1[i+1][j+1]);

// 			a10 = FIFTEEN_R(d2a0, d2a1);
// 			a12 = FIFTEEN_L(d2a1, d2a2);
// 			b10 = FIFTEEN_R(d2b0, d2b1);
// 			b12 = FIFTEEN_L(d2b1, d2b2);
// 			c10 = FIFTEEN_R(d2c0, d2c1);
// 			c12 = FIFTEEN_L(d2c1, d2c2);

// 			s0 = OR_THREE_VAL(a10, d2a1, a12);
// 			s1 = OR_THREE_VAL(b10, d2b1, b12);
// 			s2 = OR_THREE_VAL(c10, d2c1, c12);
// 			s = OR_THREE_VAL(s0, s1, s2);

// 			_mm_store_si128((vuint8 *)&dilatation2[i][j], s);

// 			d2a0 = d2a1; d2a1 = d2a2;
// 			d2b0 = d2b1; d2b1 = d2b2;
// 			d2c0 = d2c1; d2c1 = d2c2;
// 		}
// 		d2a0 = d2b0; d2a1 = d2b1; d2a2 = d2b2;
// 		d2b0 = d2c0; d2b1 = d2c1; d2b2 = d2c2;
// 	}

// 	// Erosion 2
// 	e2a0 = _mm_load_si128((vuint8 *)&dilatation2[-1][-1]);
// 	e2a1 = _mm_load_si128((vuint8 *)&dilatation2[-1][0]);
// 	e2b0 = _mm_load_si128((vuint8 *)&dilatation2[0][-1]);
// 	e2b1 = _mm_load_si128((vuint8 *)&dilatation2[0][0]);
// 	for (i = m-4; i < m; i++) {
// 		e2c0 = _mm_load_si128((vuint8 *)&dilatation2[i+1][-1]);
// 		e2c1 = _mm_load_si128((vuint8 *)&dilatation2[i+1][0]);
// 		for (j = 0; j < n; j++) {
// 			e2a2 = _mm_load_si128((vuint8 *)&dilatation2[i-1][j+1]);
// 			e2b2 = _mm_load_si128((vuint8 *)&dilatation2[i][j+1]);
// 			e2c2 = _mm_load_si128((vuint8 *)&dilatation2[i+1][j+1]);

// 			a10 = FIFTEEN_R(e2a0, e2a1);
// 			a12 = FIFTEEN_L(e2a1, e2a2);
// 			b10 = FIFTEEN_R(e2b0, e2b1);
// 			b12 = FIFTEEN_L(e2b1, e2b2);
// 			c10 = FIFTEEN_R(e2c0, e2c1);
// 			c12 = FIFTEEN_L(e2c1, e2c2);

// 			s0 = AND_THREE_VAL(a10, e2a1, a12);
// 			s1 = AND_THREE_VAL(b10, e2b1, b12);
// 			s2 = AND_THREE_VAL(c10, e2c1, c12);
// 			s = AND_THREE_VAL(s0, s1, s2);

// 			_mm_store_si128((vuint8 *)&img_dst[i][j], s);

// 			e2a0 = e2a1; e2a1 = e2a2;
// 			e2b0 = e2b1; e2b1 = e2b2;
// 			e2c0 = e2c1; e2c1 = e2c2;
// 		}
// 		e2a0 = e2b0; e2a1 = e2b1; e2a2 = e2b2;
// 		e2b0 = e2c0; e2b1 = e2c1; e2b2 = e2c2;
// 	}
// }