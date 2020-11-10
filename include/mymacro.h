#ifndef MYMACRO_H
#define MYMACRO_H

#include <stdio.h>
#include <stdlib.h>

#include "nrdef.h"
#include "nrutil.h"

#include "vnrdef.h"
#include "vnrutil.h"

#include "mutil.h"

#define IMG_LENGTH	320
#define IMG_HEIGHT	240

// Pour test
// #define IMG_LENGTH	576
// #define IMG_HEIGHT	576

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

#define FIFTEEN_L(a, b) _mm_add_epi8(_mm_srli_si128(a, 1), _mm_slli_si128(b, 15))
#define FIFTEEN_R(a, b) _mm_add_epi8(_mm_srli_si128(a, 15), _mm_slli_si128(b, 1))

#define AND_THREE_VAL(a, b, c) _mm_and_si128(_mm_and_si128(a, b), c)
#define OR_THREE_VAL(a, b, c) _mm_or_si128(_mm_or_si128(a, b), c)

#endif