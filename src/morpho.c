#include <stdio.h>
#include <stdlib.h>
#include "mymacro.h"
#include "nrdef.h"
#include "nrutil.h"
#include "vnrdef.h"
#include "vnrutil.h"
#include "morpho.h"

// Dans ce fichier: n est le nombre de colonne et m est le nombre de ligne
void erosion(uint8 **img_src, uint8 **img_dst, int m, int n)
{
	int i, j, k, l, flag;

	// matrice [-1..LARGMORPH][-1..HAUTMORPH] = [-1..LARG+1][-1..HAUT+1]
	// aka     [0..LARGMORPH+1][0..HAUTMORPH+1] = [0..LARG+2][0..HAUT+2]
	// du coup on va evaluer les matrices de [1..LARG+1][1..HAUT+1]
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			flag = 255;
			for (k = i - 1; k <= i + 1; k++) {
				for (l = j - 1; l <= j + 1; l++) {
					flag &= img_src[k][l];
				}
			}
			img_dst[i][j] = flag;
		}
	}
}

void dilatation(uint8 **img_src, uint8 **img_dst, int m, int n)
{
	int i, j, k, l, flag;

	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			flag = 0;
			for (k = i - 1; k <= i + 1; k++) {
				for (l = j - 1; l <= j + 1; l++) {
					flag |= img_src[k][l];
				}
			}
			img_dst[i][j] = flag;
		}
	}
}

void morpho_pipeline(uint8 **img_src, uint8 **erosion1, uint8 **dilatation1, uint8 **dilatation2, uint8 **img_dst, int m, int n)
{
	int i, j, k, l, flag;

	// Prologue
	// Erosion 1
	for (i = 0; i < 3; i++) {
		for (j = 0; j < n; j++) {
			flag = 255;
			for (k = i - 1; k <= i + 1; k++) {
				for (l = j - 1; l <= j + 1; l++) {
					flag &= img_src[k][l];
				}
			}
			erosion1[i][j] = flag;
		}
		erosion1[i][-1] = erosion1[i][0];
		erosion1[i][n] = erosion1[i][n-1];
	}
	for (j = -1; j <= n; j++) {
		erosion1[-1][j] = erosion1[0][j];
	}

	// Dilatation 1
	for (i = 0; i < 2; i++) {
		for (j = 0; j < n; j++) {
			flag = 0;
			for (k = i - 1; k <= i + 1; k++) {
				for (l = j - 1; l <= j + 1; l++) {
					flag |= erosion1[k][l];
				}
			}
			dilatation1[i][j] = flag;
		}
		dilatation1[i][-1] = dilatation1[i][0];
		dilatation1[i][n] = dilatation1[i][n-1];
	}
	for (j = -1; j <= n; j++) {
		dilatation1[-1][j] = dilatation1[0][j];
	}

	// Dilatation 2
	for (i = 0; i < 1; i++) {
		for (j = 0; j < n; j++) {
			flag = 0;
			for (k = i - 1; k <= i + 1; k++) {
				for (l = j - 1; l <= j + 1; l++) {
					flag |= dilatation1[k][l];
				}
			}
			dilatation2[i][j] = flag;
		}
		dilatation2[i][-1] = dilatation2[i][0];
		dilatation2[i][n] = dilatation2[i][n-1];
	}
	for (j = -1; j <= n; j++) {
		dilatation2[-1][j] = dilatation2[0][j];
	}

	// Pipeline
	for (i = 3; i < m; i++) {
		// Erosion 1
		for (j = 0; j < n; j++) {
			flag = 255;
			for (k = i - 1; k <= i + 1; k++) {
				for (l = j - 1; l <= j + 1; l++) {
					flag &= img_src[k][l];
				}
			}
			erosion1[i][j] = flag;
		}
		erosion1[i][-1] = erosion1[i][0];
		erosion1[i][n] = erosion1[i][n-1];

		// Dilatation 1
		for (j = 0; j < n; j++) {
			flag = 0;
			for (k = i - 1; k <= i + 1; k++) {
				for (l = j - 1; l <= j + 1; l++) {
					flag |= erosion1[k-1][l];
				}
			}
			dilatation1[i][j] = flag;
		}
		dilatation1[i][-1] = dilatation1[i][0];
		dilatation1[i][n] = dilatation1[i][n-1];

		// Dilatation 2
		for (j = 0; j < n; j++) {
			flag = 0;
			for (k = i - 1; k <= i + 1; k++) {
				for (l = j - 1; l <= j + 1; l++) {
					flag |= dilatation1[k-2][l];
				}
			}
			dilatation2[i][j] = flag;
		}
		dilatation2[i][-1] = dilatation2[i][0];
		dilatation2[i][n] = dilatation2[i][n-1];

		// Erosion 2
		for (j = 0; j < n; j++) {
			flag = 255;
			for (k = i - 1; k <= i + 1; k++) {
				for (l = j - 1; l <= j + 1; l++) {
					flag &= dilatation2[k-3][l];
				}
			}
			img_dst[i][j] = flag;
		}
	}

	// Epilogue
	// Dilatation 1
	for (i = m-2; i < m; i++) {
		for (j = 0; j < n; j++) {
			flag = 255;
			for (k = i - 1; k <= i + 1; k++) {
				for (l = j - 1; l <= j + 1; l++) {
					flag |= erosion1[k][l];
				}
			}
			dilatation1[i][j] = flag;
		}
		dilatation1[i][-1] = dilatation1[i][0];
		dilatation1[i][n] = dilatation1[i][n-1];
	}
	for (j = -1; j <= n; j++) {
		dilatation1[n][j] = dilatation1[n-1][j];
	}

	// Dilatation 2
	for (i = m-3; i < m; i++) {
		for (j = 0; j < n; j++) {
			flag = 0;
			for (k = i - 1; k <= i + 1; k++) {
				for (l = j - 1; l <= j + 1; l++) {
					flag |= dilatation1[k][l];
				}
			}
			dilatation2[i][j] = flag;
		}
		dilatation2[i][-1] = dilatation2[i][0];
		dilatation2[i][n] = dilatation2[i][n-1];
	}
	for (j = -1; j <= n; j++) {
		dilatation2[n][j] = dilatation2[n-1][j];
	}

	// Erosion 2
	for (i = m-4; i < 1; i++) {
		for (j = 0; j < n; j++) {
			flag = 0;
			for (k = i - 1; k <= i + 1; k++) {
				for (l = j - 1; l <= j + 1; l++) {
					flag &= dilatation2[k][l];
				}
			}
			img_dst[i][j] = flag;
		}
	}
}
