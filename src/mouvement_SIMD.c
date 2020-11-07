#include <stdio.h>
#include <stdlib.h>

#include "nrdef.h"
#include "nrutil.h"

#include "vnrdef.h"
#include "vnrutil.h"

#include "mutil.h"

#include "mymacro.h"
#include "mouvement_SIMD.h"

// Comparaison less than pour les vuint8
vuint8 cmplt_vuint8(vuint8 a, vuint8 b)
{
	vuint8 dst, a_lt_0, b_lt_0, s0, s1, s;

	s0 = _mm_set_epi8(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	s1 = _mm_set_epi8(0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff);
	dst = _mm_cmplt_epi8(a, b);	// Comparaison avec signe
	a_lt_0 = _mm_cmplt_epi8(a, s0);	// Trouver les valeurs negatives dans a
	b_lt_0 = _mm_cmplt_epi8(b, s0);	// Trouver les valeurs negatives dans b
	// La somme va etre 0xff s'il y a une seule valeur negative dans a et b
	s = _mm_add_epi8(a_lt_0, b_lt_0);
	s = _mm_cmpeq_epi8(s, s1);
	// Inverser le resultat s'il y a une seule valeur negative
	dst = _mm_sub_epi8(dst, s);	// Si s[i] = 0, dst[i] ne change pas, sinon, si dst[i] = 0xff, dst[i] devient 0x00, si dst[i] = 0x00, dst[i] devient -0xfe
	// toutes les dst[i] == -0xfe sont des 0 a inverser, donc elles doivent etre 0xff.
	dst = _mm_cmpeq_epi8(dst, s0);	
	dst = _mm_andnot_si128(dst, s1);

	return dst;
}

// Comparaison less than pour les vuint8
vuint8 cmpgt_vuint8(vuint8 a, vuint8 b)
{
	vuint8 dst, a_lt_0, b_lt_0, s0, s1, s;

	s0 = _mm_set_epi8(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	s1 = _mm_set_epi8(0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff);
	dst = _mm_cmpgt_epi8(a, b);	// Comparaison avec signe
	a_lt_0 = _mm_cmplt_epi8(a, s0);	// Trouver les valeurs negatives dans a
	b_lt_0 = _mm_cmplt_epi8(b, s0);	// Trouver les valeurs negatives dans b
	// La somme va etre 0xff s'il y a une seule valeur negative dans a et b
	s = _mm_add_epi8(a_lt_0, b_lt_0);
	s = _mm_cmpeq_epi8(s, s1);
	// Inverser le resultat s'il y a une seule valeur negative
	dst = _mm_sub_epi8(dst, s);	// Si s[i] = 0, dst[i] ne change pas, sinon, si dst[i] = 0xff, dst[i] devient 0x00, si dst[i] = 0x00, dst[i] devient -0xfe
	// toutes les dst[i] == -0xfe sont des 0 a inverser, donc elles doivent etre 0xff.
	dst = _mm_cmpeq_epi8(dst, s0);	
	dst = _mm_andnot_si128(dst, s1);

	return dst;
}

// Dans ce fichier: m est le nombre de colonne et n est le nombre de ligne
// Initialisation de l'algorithme pour t = 0
void SigmaDelta_step0_SIMD(vuint8 **M0, vuint8 **I0, vuint8 **V0, int m, int n)
{
	int i, j;
	vuint8 x, s;

	s = _mm_set_epi8(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			x = _mm_load_si128((vuint8 *)&I0[i][j]);
			_mm_store_si128((vuint8 *)&M0[i][j], x);
			_mm_store_si128((vuint8 *)&V0[i][j], s);
		}
	}
}

// Estimation de Mt
void SigmaDelta_1step_SIMD(vuint8 **M_t0, vuint8 **M_t1, vuint8 **I_t, int m, int n)
{
	int i, j;
	vuint8 m1, m0, i0, s0, s1, s2, c, k;

	s0 = _mm_set_epi8(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	s1 = _mm_set_epi8(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
	s2 = _mm_set_epi8(-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);

	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			m1 = _mm_load_si128((vuint8 *)&M_t1[i][j]);
			i0 = _mm_load_si128((vuint8 *)&I_t[i][j]);

			c = cmplt_vuint8(m1, i0);
			k = _mm_or_si128(_mm_and_si128(c, s1), s0);
			m0 = _mm_add_epi8(m1, k);

			c = cmpgt_vuint8(m1, i0);
			k = _mm_or_si128(_mm_and_si128(c, s2), s0);
			m0 = _mm_add_epi8(m0, k);

			_mm_store_si128((vuint8 *)&M_t0[i][j], m0);
		}
	}
}

// Calcul de Ot
void SigmaDelta_2step_SIMD(vuint8 **O_t, vuint8 **M_t, vuint8 **I_t, int m, int n)
{
	int i, j;
	vuint8 m0, o0, i0, c, k1, k2;

	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			m0 = _mm_load_si128((vuint8 *)&M_t[i][j]);
			i0 = _mm_load_si128((vuint8 *)&I_t[i][j]);

			// Valeur absolue
			k1 = _mm_subs_epu8(m0, i0);
			k2 = _mm_subs_epu8(i0, m0);
			c = cmpgt_vuint8(m0, i0);
			o0 = _mm_or_si128(_mm_and_si128(c, k1), _mm_andnot_si128(c, k2));
			_mm_store_si128((vuint8 *)&O_t[i][j], o0);
		}
	}
}

// Vt update and clamping
void SigmaDelta_3step_SIMD(vuint8 **V_t0, vuint8 **V_t1, vuint8 **O_t, int m, int n)
{
	int i, j;
	vuint8 Vmin, Vmax, v0, v1, o0, c, s0, k;

	s0 = _mm_set_epi8(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	Vmin = _mm_set_epi8(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
	Vmax = _mm_set_epi8(0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe);

	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			v1 = _mm_load_si128((vuint8 *)&V_t1[i][j]);
			o0 = _mm_load_si128((vuint8 *)&O_t[i][j]);
			o0 = _mm_adds_epu8(o0, o0);	// On considere que N vaut 2

			c = cmplt_vuint8(v1, o0);
			k = _mm_or_si128(_mm_and_si128(c, Vmin), s0);
			v0 = _mm_adds_epu8(v1, k);

			c = cmpgt_vuint8(v1, o0);
			k = _mm_or_si128(_mm_and_si128(c, Vmax), s0);	// 0xfe = -1
			v0 = _mm_adds_epu8(v0, k);

			v0 = _mm_max_epu8(_mm_min_epu8(v0, Vmax), Vmin); 	// Clamping
			_mm_store_si128((vuint8 *)&V_t0[i][j], v0);
		}
	}
}

// Estimation de Et
void SigmaDelta_4step_SIMD(vuint8 **O_t, vuint8 **V_t, vuint8 **E_t, int m, int n)
{
	int i, j;
	vuint8 o0, v0, e0, c, s0, s1;

	s0 = _mm_set_epi8(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	s1 = _mm_set_epi8(0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff);

	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			o0 = _mm_load_si128((vuint8 *)&O_t[i][j]);
			v0 = _mm_load_si128((vuint8 *)&V_t[i][j]);

			c = cmplt_vuint8(o0, v0);
			e0 = _mm_or_si128(s0, _mm_andnot_si128(c, s1));
			_mm_store_si128((vuint8 *)&E_t[i][j], e0);
		}
	}
}