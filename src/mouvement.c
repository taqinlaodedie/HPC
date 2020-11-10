#include <stdio.h>
#include <stdlib.h>
#include "nrdef.h"
#include "mymacro.h"
#include "mouvement.h"

// Dans ce fichier: m est le nombre de colonne et n est le nombre de ligne
// Initialisation de l'algorithme pour t = 0
void SigmaDelta_0step(uint8 **M0, uint8 **I0, uint8 **V0, int m, int n)
{
	int i, j, Vmin = 1;

	for (i = 0; i <= m; i++) {
		for (j = 0; j <= n; j++) {
			M0[i][j] = I0[i][j];
			V0[i][j] = Vmin;
		}
	}
}

// Estimation de Mt
void SigmaDelta_1step(uint8 **M_t0, uint8 **M_t1, uint8 **I_t, int m, int n)
{
	int i, j;

	for (i = 0; i <= m; i++) {
		for (j = 0; j <= n; j++) {
			if (M_t1[i][j] < I_t[i][j]) M_t0[i][j] = M_t1[i][j] + 1;
			else if (M_t1[i][j] > I_t[i][j]) M_t0[i][j] = M_t1[i][j] - 1;
			else M_t0[i][j] = M_t1[i][j];
		}
	}
}

// Calcul de Ot
void SigmaDelta_2step(uint8 **O_t, uint8 **M_t, uint8 **I_t, int m, int n)
{
	int i, j;

	for (i = 0; i <= m; i++) {
		for (j = 0; j <= n; j++) {
			// Valeur absolue
			if (M_t[i][j] > I_t[i][j]) O_t[i][j] = M_t[i][j] - I_t[i][j];
			else O_t[i][j] = I_t[i][j] - M_t[i][j];
		}
	}
}

// Vt update and clamping
void SigmaDelta_3step(uint8 **V_t0, uint8 **V_t1, uint8 **O_t, int m, int n, int N)
{
	int i, j, Vmin = 1, Vmax = 254;

	for (i = 0; i <= m; i++) {
		for (j = 0; j <= n; j++) {
			if (V_t1[i][j] < (N * O_t[i][j])) V_t0[i][j] = V_t1[i][j] + 1;
			else if (V_t1[i][j] > (N * O_t[i][j])) V_t0[i][j] = V_t1[i][j] - 1;
			else V_t0[i][j] = V_t1[i][j];
			V_t0[i][j] = MAX(MIN(V_t0[i][j], Vmax), Vmin);	// Clamping
		}
	}
}

// Estimation de Et
void SigmaDelta_4step(uint8 **O_t, uint8 **V_t, uint8 **E_t, int m, int n)
{
	int i, j;

	for (i = 0; i <= m; i++) {
		for (j = 0; j <= n; j++) {
			if (O_t[i][j] < V_t[i][j]) E_t[i][j] = 0;
			else E_t[i][j] = 255;
		}
	}
}
