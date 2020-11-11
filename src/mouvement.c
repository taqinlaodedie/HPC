#include <stdio.h>
#include <stdlib.h>
#include "nrdef.h"
#include "mymacro.h"
#include "mouvement.h"

// Dans ce fichier: n est le nombre de colonne et m est le nombre de ligne
// Initialisation de l'algorithme pour t = 0
void SigmaDelta_step0(uint8 **M0, uint8 **I0, uint8 **V0, int m, int n)
{
	int i, j, Vmin = 1;

	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			M0[i][j] = I0[i][j];
			V0[i][j] = Vmin;
		}
	}
}


void SigmaDelta_1step(uint8 **M_t0, uint8 **M_t1, uint8 **I_t0, uint8 **O_t0, uint8 **V_t0, uint8 **V_t1, uint8 **E_t0, int m, int n)
{
	int i, j;
	int Vmin = 1, Vmax = 254;

	// Estimation de Mt
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			if (M_t1[i][j] < I_t0[i][j]) M_t0[i][j] = M_t1[i][j] + 1;
			else if (M_t1[i][j] > I_t0[i][j]) M_t0[i][j] = M_t1[i][j] - 1;
			else M_t0[i][j] = M_t1[i][j];
		}
	}

	// Calcul de Ot
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			O_t0[i][j] = (uint8)abs(M_t0[i][j] - I_t0[i][j]);
		}
	}

	// Vt update and clamping
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			if (V_t1[i][j] < (2 * (O_t0[i][j]))) V_t0[i][j] = V_t1[i][j] + 1;
			else if (V_t1[i][j] > (2 * (O_t0[i][j]))) V_t0[i][j] = V_t1[i][j] - 1;
			else V_t0[i][j] = V_t1[i][j];
			V_t0[i][j] = MAX(MIN(V_t0[i][j], 254), 1);

		}
	}

	// Estimation de Et
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			if (O_t0[i][j] < V_t0[i][j]) E_t0[i][j] = 0;
			else E_t0[i][j] = 255;
		}
	}
}