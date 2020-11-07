#include <stdio.h>
#include <stdlib.h>
#include "mymacro.h"
#include "nrdef.h"
#include "nrutil.h"
#include "vnrdef.h"
#include "vnrutil.h"
#include "morpho.h"

// Dans ce fichier: m est le nombre de colonne et n est le nombre de ligne
void erosion(uint8 **img_src, uint8 **img_dst, int m, int n)
{
	int i, j, k, l, flag;

	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			flag = 1;
			for (k = i - 1; k <= i + 1; k++) {
				for (l = j - 1; l <= j + 1; l++) {
					if ((img_src[i][j] == 0) || (img_src[k][l] == 0)) {
						flag = 0;
						break;
					}
				}
				if (flag == 0) break;
			}
			if (flag == 0) img_dst[i][j] = 0;
			else img_dst[i][j] = 255;
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
					if ((img_src[i][j] != 0) || (img_src[k][l] != 0)) {
						flag = 1;
						break;
					}
				}
				if (flag == 1) break;
			}
			if (flag == 0) img_dst[i][j] = 0;
			else img_dst[i][j] = 255;
		}
	}
}