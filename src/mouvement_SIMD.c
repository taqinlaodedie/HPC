#include <stdio.h>
#include <stdlib.h>

#include "nrdef.h"
#include "nrutil.h"

#include "vnrdef.h"
#include "vnrutil.h"

#include "mutil.h"

#include "mymacro.h"
#include "mouvement_SIMD.h"

static vuint8 s0, s1, _s1, sff, Vmax, Vmin;	// Les sets constants a utiliser

// Dans ce fichier: n est le nombre de colonne et m est le nombre de ligne
// Initialisation de l'algorithme pour t = 0
void SigmaDelta_step0_SIMD(vuint8 **M0, vuint8 **I0, vuint8 **V0, int m, int n)
{
	int i, j;
	vuint8 x;

	// Initialiser les sets
	s0 = _mm_set1_epi8(0);
	s1 = _mm_set1_epi8(1);
	_s1 = _mm_set1_epi8(-1);
	sff = _mm_set1_epi8(0xff);
	Vmin = _mm_set1_epi8(1);
	Vmax = _mm_set1_epi8(0xfe);

	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			x = _mm_load_si128((vuint8 *)&I0[i][j]);
			_mm_store_si128((vuint8 *)&M0[i][j], x);
			_mm_store_si128((vuint8 *)&V0[i][j], s1);
		}
	}
}


void SigmaDelta_1step_SIMD(vuint8 **M_t0, vuint8 **M_t1, vuint8 **I_t0, vuint8 **O_t0, vuint8 **V_t0, vuint8 **V_t1, vuint8 **E_t0, int m, int n)
{
	int i, j;
	vuint8 m1, m0, i0, e0, v0, v1, o0, oN, c, k, k1, k2;

	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			// Estimation de Mt
			m1 = _mm_load_si128((vuint8 *)&M_t1[i][j]);
			i0 = _mm_load_si128((vuint8 *)&I_t0[i][j]);

			c = cmplt_vuint8(m1, i0);
			k = _mm_or_si128(_mm_and_si128(c, s1), s0);
			m0 = _mm_add_epi8(m1, k);

			c = cmpgt_vuint8(m1, i0);
			k = _mm_or_si128(_mm_and_si128(c, _s1), s0);
			m0 = _mm_add_epi8(m0, k);

			_mm_store_si128((vuint8 *)&M_t0[i][j], m0);
		}
	}

	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			// Calcul de Ot
			m0 = _mm_load_si128((vuint8 *)&M_t0[i][j]);
			i0 = _mm_load_si128((vuint8 *)&I_t0[i][j]);

			// Valeur absolue
			k1 = _mm_subs_epu8(m0, i0);
			k2 = _mm_subs_epu8(i0, m0);
			c = cmpgt_vuint8(m0, i0);
			o0 = _mm_or_si128(_mm_and_si128(c, k1), _mm_andnot_si128(c, k2));
			_mm_store_si128((vuint8 *)&O_t0[i][j], o0);

			// Vt update and clamping
			v1 = _mm_load_si128((vuint8 *)&V_t1[i][j]);
			o0 = _mm_load_si128((vuint8 *)&O_t0[i][j]);
			oN = _mm_adds_epu8(o0, o0);	// On considere que N vaut 2

			c = cmplt_vuint8(v1, oN);
			k = _mm_or_si128(_mm_and_si128(c, Vmin), s0);
			v0 = _mm_adds_epu8(v1, k);

			c = cmpgt_vuint8(v1, o0);
			k = _mm_or_si128(_mm_and_si128(c, Vmax), s0);	// 0xfe = -1
			v0 = _mm_adds_epu8(v0, k);

			v0 = _mm_max_epu8(_mm_min_epu8(v0, Vmax), Vmin); 	// Clamping
			_mm_store_si128((vuint8 *)&V_t0[i][j], v0);
		}
	}

	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			// Estimation de Et
			o0 = _mm_load_si128((vuint8 *)&O_t0[i][j]);
			v0 = _mm_load_si128((vuint8 *)&V_t0[i][j]);

			c = cmplt_vuint8(o0, v0);
			e0 = _mm_or_si128(s0, _mm_andnot_si128(c, sff));
			_mm_store_si128((vuint8 *)&E_t0[i][j], e0);
		}
	}
}
