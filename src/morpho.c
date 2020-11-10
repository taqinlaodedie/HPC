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