#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "nrdef.h"
#include "nrutil.h"
#include "morpho.h"
#include "test_morpho.h"
#include "mymacro.h"
#include "sys/time.h"

void traitement_bord(uint8 **img, int larg, int haut)
{
	int i;

	for (i = 0; i < haut; i++) {
		img[i][-1] = img[i][0];
		img[i][haut] = img[i][haut-1];
	}

	for (i = -1; i <= larg; i++) {
		img[-1][i] = img[0][i];
		img[haut][i] = img[haut-1][i];
	}
}

void test_morpho()
{
	struct timeval t1, t2;
	double timeused;

	test_unitaire_morpho();

	/* Test unitaire avec des images de 5*5*/
  	uint8 **I0 = ui8matrix(-1, 5, -1, 5);
	uint8 **I1 = ui8matrix(-1, 5, -1, 5);

	// Initialisation en 0
	for (int i = -1; i <= 5; i++) {
		for (int j = -1; j <= 5; j++) {
			I0[i][j] = 0;
		}
	}

	for (int i = -1; i <= 5; i++) {
		I0[1][i] = 255;
		I0[2][i] = 255;
		I0[3][i] = 255;
	}

	printf("\nTest unitaire pour morpho\n");
	display_ui8matrix(I0, 0, 4, 0, 4, " [%03d] ", "I0");
	// display_ui8matrix(I0, -1, 5, -1, 5, " [%03d] ", "I0");
	erosion(I0, I1, 5, 5);
	display_ui8matrix(I1, 0, 4, 0, 4, " [%03d] ", "erosion");
	dilatation(I0, I1, 5, 5);
	display_ui8matrix(I1, 0, 4, 0, 4, " [%03d] ", "dilatation");

	free_ui8matrix(I0, -1, 5, -1, 5);
  	free_ui8matrix(I1, -1, 5, -1, 5);

	/* Benchmark */
	char *fname0 = "test_img/mouvement/output.pgm";
	I0 = ui8matrix(-1, IMG_HEIGHT+1, -1, IMG_LENGTH+1);
	I1 = ui8matrix(-1, IMG_HEIGHT+1, -1, IMG_LENGTH+1);

	MLoadPGM_ui8matrix(fname0, 0, IMG_HEIGHT-1, 0, IMG_LENGTH-1, I0);
	traitement_bord(I0, IMG_HEIGHT, IMG_LENGTH);

	CHRONO(erosion(I0, I1, IMG_HEIGHT, IMG_LENGTH);	\
		dilatation(I1, I0, IMG_HEIGHT, IMG_LENGTH);	\
		dilatation(I0, I1, IMG_HEIGHT, IMG_LENGTH);	\
		erosion(I1, I0, IMG_HEIGHT, IMG_LENGTH), "chaine de morpho");
	SavePGM_ui8matrix(I0, 0, IMG_HEIGHT-1, 0, IMG_LENGTH-1, "test_img/morpho/chaine_de_morpho.pgm");


	free_ui8matrix(I0, -1, IMG_HEIGHT+1, -1, IMG_LENGTH+1);
	free_ui8matrix(I1, -1, IMG_HEIGHT+1, -1, IMG_LENGTH+1);
}

void test_unitaire_morpho()
{
	uint8 **tab0 = ui8matrix(-1, 1, -1, 1);
	uint8 **tab1 = ui8matrix(-1, 1, -1, 1);

	/***** TESTS UNITAIRES EROSION *****/

	/***** TEST 1															*******
	****** Toute la matrice tab0 à 0 initialement, puis						*******
	****** chaque élément devient 255 un par un								*******
	****** Résultat attendu de la fonction érosion : 0 à chaque fois		******/

	// Initialisation à 0
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			tab0[i][j] = 0;
			tab1[i][j] = 111;
		}
	}

	// printf("\nTest 1\n");
	display_ui8matrix(tab0, -1, 1, -1, 1, " [%03d] ", "\nTest 1 EROSION");

	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			tab0[i][j] = 255;
			erosion(tab0, tab1, 1, 1);
			// display_ui8matrix(tab0, -1, 1, -1, 1, " [%03d] ", "\nModifie");
			// display_ui8matrix(tab1, -1, 1, -1, 1, " [%03d] ", "Resultat");
			if(tab1[0][0] == 0)
				printf("OK\n");
			else
			{
				printf("KO\n");
				return;
			}
			tab0[i][j] = 0;
		}
	}

	/***** TEST 2															*******
	****** Toute la matrice tab0 à 255 initialement, puis					*******
	****** chaque élément devient 0 un par un								*******
	****** Résultat attendu de la fonction érosion : 0 à chaque fois		******/

	// Initialisation à 255
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			tab0[i][j] = 255;
		}
	}

	// printf("\nTest 2\n");
	display_ui8matrix(tab0, -1, 1, -1, 1, " [%03d] ", "\nTest 2 EROSION");

	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			tab0[i][j] = 0;
			erosion(tab0, tab1, 1, 1);
			// display_ui8matrix(tab0, -1, 1, -1, 1, " [%03d] ", "\nModifie");
			// display_ui8matrix(tab1, -1, 1, -1, 1, " [%03d] ", "Resultat");
			if(tab1[0][0] == 0)
				printf("OK\n");
			else
			{
				printf("KO\n");
				return;
			}
			tab0[i][j] = 255;
		}
	}

	/***** TESTS UNITAIRES DILATATION *****/

	/***** TEST 3															*******
	****** Toute la matrice tab0 à 255 initialement, puis					*******
	****** chaque élément devient 0 un par un								*******
	****** Résultat attendu de la fonction dilatation : 255 à chaque fois	******/

	// printf("\nTest 3\n");
	display_ui8matrix(tab0, -1, 1, -1, 1, " [%03d] ", "\nTest 3 DILATATION");

	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			tab0[i][j] = 0;
			dilatation(tab0, tab1, 1, 1);
			// display_ui8matrix(tab0, -1, 1, -1, 1, " [%03d] ", "\nModifie");
			// display_ui8matrix(tab1, -1, 1, -1, 1, " [%03d] ", "Resultat");
			if(tab1[0][0] == 255)
				printf("OK\n");
			else
			{
				printf("KO\n");
				return;
			}
			tab0[i][j] = 255;
		}
	}

	/***** TEST 4															*******
	****** Toute la matrice tab0 à 0 initialement, puis						*******
	****** chaque élément devient 255 un par un								*******
	****** Résultat attendu de la fonction dilatation : 255 à chaque fois	******/

	// Initialisation à 0
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			tab0[i][j] = 0;
		}
	}

	// printf("\nTest 4\n");
	display_ui8matrix(tab0, -1, 1, -1, 1, " [%03d] ", "\nTest 4 DILATATION");

	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			tab0[i][j] = 255;
			dilatation(tab0, tab1, 1, 1);
			// display_ui8matrix(tab0, -1, 1, -1, 1, " [%03d] ", "\nModifie");
			// display_ui8matrix(tab1, -1, 1, -1, 1, " [%03d] ", "Resultat");
			if(tab1[0][0] == 255)
				printf("OK\n");
			else
			{
				printf("KO\n");
				return;
			}
			tab0[i][j] = 0;
		}
	}

	free_ui8matrix(tab0, -1, 1, -1, 1);
  	free_ui8matrix(tab1, -1, 1, -1, 1);
}
