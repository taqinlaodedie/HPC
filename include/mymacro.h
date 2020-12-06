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

#define HAUTMORPH	240
#define LARGMORPH	320

// Pour test
#define IMG_LENGTH	576
#define IMG_HEIGHT	576

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

#define cmplt_vuint8(a, b) _mm_cmplt_epi8(_mm_add_epi8(_mm_set1_epi8(0x80), a), _mm_add_epi8(_mm_set1_epi8(0x80), b))
#define cmpgt_vuint8(a, b) _mm_cmpgt_epi8(_mm_add_epi8(_mm_set1_epi8(0x80), a), _mm_add_epi8(_mm_set1_epi8(0x80), b))
#define cmpeq_vuint8(a, b) _mm_cmpeq_epi8(_mm_add_epi8(_mm_set1_epi8(0x80), a), _mm_add_epi8(_mm_set1_epi8(0x80), b))

#define FIFTEEN_L(a, b) _mm_add_epi8(_mm_srli_si128(a, 1), _mm_slli_si128(b, 15))
#define FIFTEEN_R(a, b) _mm_add_epi8(_mm_srli_si128(a, 15), _mm_slli_si128(b, 1))
#define FOURTEEN_L(a, b) _mm_add_epi8(_mm_srli_si128(a, 2), _mm_slli_si128(b, 14))
#define FOURTEEN_R(a, b) _mm_add_epi8(_mm_srli_si128(a, 14), _mm_slli_si128(b, 2))

#define AND_THREE_VAL(a, b, c) _mm_and_si128(_mm_and_si128(a, b), c)
#define OR_THREE_VAL(a, b, c) _mm_or_si128(_mm_or_si128(a, b), c)
#define OR_FIVE_VAL(a, b, c, d, e) _mm_or_si128(_mm_or_si128(a, b), OR_THREE_VAL(c, d, e))

#define INIT_MATRICES(I0, M0, V0, I1, M1, V1, O1, E1)	\
		uint8 **I0 = ui8matrix(0, HAUT, 0, LARG);		\
		uint8 **M0 = ui8matrix(0, HAUT, 0, LARG);		\
		uint8 **V0 = ui8matrix(0, HAUT, 0, LARG);		\
		uint8 **I1 = ui8matrix(0, HAUT, 0, LARG);		\
		uint8 **M1 = ui8matrix(0, HAUT, 0, LARG);		\
		uint8 **V1 = ui8matrix(0, HAUT, 0, LARG);		\
		uint8 **O1 = ui8matrix(0, HAUT, 0, LARG);		\
		uint8 **E1 = ui8matrix(0, HAUT, 0, LARG)
#define FREE_MATRICES(I0, M0, V0, I1, M1, V1, O1, E1)	\
		free_ui8matrix(I0, 0, HAUT, 0, LARG);			\
		free_ui8matrix(M0, 0, HAUT, 0, LARG);			\
		free_ui8matrix(V0, 0, HAUT, 0, LARG);			\
		free_ui8matrix(I1, 0, HAUT, 0, LARG);			\
		free_ui8matrix(M1, 0, HAUT, 0, LARG);			\
		free_ui8matrix(V1, 0, HAUT, 0, LARG);			\
		free_ui8matrix(O1, 0, HAUT, 0, LARG);			\
		free_ui8matrix(E1, 0, HAUT, 0, LARG)

#define INIT_VMATRICES(I0, M0, V0, I1, M1, V1, O1, E1)	\
		vuint8 **I0 = vui8matrix(0, HAUT, 0, LARSIMD);	\
		vuint8 **M0 = vui8matrix(0, HAUT, 0, LARSIMD);	\
		vuint8 **V0 = vui8matrix(0, HAUT, 0, LARSIMD);	\
		vuint8 **I1 = vui8matrix(0, HAUT, 0, LARSIMD);	\
		vuint8 **M1 = vui8matrix(0, HAUT, 0, LARSIMD);	\
		vuint8 **V1 = vui8matrix(0, HAUT, 0, LARSIMD);	\
		vuint8 **O1 = vui8matrix(0, HAUT, 0, LARSIMD);	\
		vuint8 **E1 = vui8matrix(0, HAUT, 0, LARSIMD)
#define FREE_VMATRICES(I0, M0, V0, I1, M1, V1, O1, E1)	\
		free_vui8matrix(I0, 0, HAUT, 0, LARSIMD);		\
		free_vui8matrix(M0, 0, HAUT, 0, LARSIMD);		\
		free_vui8matrix(V0, 0, HAUT, 0, LARSIMD);		\
		free_vui8matrix(I1, 0, HAUT, 0, LARSIMD);		\
		free_vui8matrix(M1, 0, HAUT, 0, LARSIMD);		\
		free_vui8matrix(V1, 0, HAUT, 0, LARSIMD);		\
		free_vui8matrix(O1, 0, HAUT, 0, LARSIMD);		\
		free_vui8matrix(E1, 0, HAUT, 0, LARSIMD)

#define INIT_MORPHO_VMATRICES(I0, E0, D0, D1, E1)						\
		vuint8 **I0 = vui8matrix(-2, HAUT+2, -2, LARSIMD+3);	\
		vuint8 **E0 = vui8matrix(-2, HAUT+2, -2, LARSIMD+3);	\
		vuint8 **D0 = vui8matrix(-2, HAUT+2, -2, LARSIMD+3);	\
		vuint8 **D1 = vui8matrix(-2, HAUT+2, -2, LARSIMD+3);	\
		vuint8 **E1 = vui8matrix(-2, HAUT+2, -2, LARSIMD+3)
#define FREE_MORPHO_VMATRICES(I0, E0, D0, D1, E1)						\
		free_vui8matrix(I0, -2, HAUT+2, -2, LARSIMD+3);			\
		free_vui8matrix(E0, -2, HAUT+2, -2, LARSIMD+3);			\
		free_vui8matrix(D0, -2, HAUT+2, -2, LARSIMD+3);			\
		free_vui8matrix(D1, -2, HAUT+2, -2, LARSIMD+3);			\
		free_vui8matrix(E1, -2, HAUT+2, -2, LARSIMD+3)


#define SIGMADELTA(Iprec,Iact,Mprec,Mact,Oact,Vprec,Vact,Eact,m,n)	\
		SigmaDelta_step0(Mprec,Iprec,Vprec,m,n);					\
		SigmaDelta_1step(Mact,Mprec,Iact,Oact,Vact,Vprec,Eact,m,n)
#define COPIER_MATRICES(src1,dst1,src2,dst2,src3,dst3)				\
		copy_ui8matrix_ui8matrix(src1, 0, HAUT, 0, LARG, dst1);		\
		copy_ui8matrix_ui8matrix(src2, 0, HAUT, 0, LARG, dst2);		\
		copy_ui8matrix_ui8matrix(src3, 0, HAUT, 0, LARG, dst3)

#define CHRONO(instr, msg)				\
		gettimeofday(&t1, NULL);	\
		instr;						\
		gettimeofday(&t2, NULL);	\
		timeused = (t2.tv_sec - t1.tv_sec) + (double)(t2.tv_usec - t1.tv_usec)/1000000.0;;	\
		printf("Temps pour %s: %f s\n", msg, timeused);

#endif
