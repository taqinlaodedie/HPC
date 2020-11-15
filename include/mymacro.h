#ifndef MYMACRO_H
#define MYMACRO_H

#include <stdio.h>
#include <stdlib.h>

#include "nrdef.h"
#include "nrutil.h"

#include "vnrdef.h"
#include "vnrutil.h"

#include "mutil.h"

#define LARG		319
#define HAUT		239
#define LARSIMD		19

// Pour test
#define IMG_LENGTH	576
#define IMG_HEIGHT	576

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

#define cmplt_vuint8(a, b) _mm_cmplt_epi8(_mm_add_epi8(_mm_set1_epi8(0x80), a), _mm_add_epi8(_mm_set1_epi8(0x80), b))
#define cmpgt_vuint8(a, b) _mm_cmpgt_epi8(_mm_add_epi8(_mm_set1_epi8(0x80), a), _mm_add_epi8(_mm_set1_epi8(0x80), b))

#define FIFTEEN_L(a, b) _mm_add_epi8(_mm_srli_si128(a, 1), _mm_slli_si128(b, 15))
#define FIFTEEN_R(a, b) _mm_add_epi8(_mm_srli_si128(a, 15), _mm_slli_si128(b, 1))

#define AND_THREE_VAL(a, b, c) _mm_and_si128(_mm_and_si128(a, b), c)
#define OR_THREE_VAL(a, b, c) _mm_or_si128(_mm_or_si128(a, b), c)

#define SIGMADELTA(Iprec,Iact,Mprec,Mact,Oact,Vprec,Vact,Eact,m,n)	\
		SigmaDelta_step0(Mprec,Iprec,Vprec,m,n);					\
		SigmaDelta_1step(Mact,Mprec,Iact,Oact,Vact,Vprec,Eact,m,n)
#define COPIER_MATRICES(src1,dst1,src2,dst2,src3,dst3)				\
		copy_ui8matrix_ui8matrix(src1, 0, HAUT, 0, LARG, dst1);		\
		copy_ui8matrix_ui8matrix(src2, 0, HAUT, 0, LARG, dst2);		\
		copy_ui8matrix_ui8matrix(src3, 0, HAUT, 0, LARG, dst3)

#endif
