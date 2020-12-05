#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
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

void test_multi_morpho()
{
	clock_t start_t, end_t;
	double total_t;
	start_t = clock();

	char *fname0  = (char*)malloc(sizeof(char*) * 16);
	char *outfile = (char*)malloc(sizeof(char*) * 16);
	int aux;
	strcpy(fname0, "output/output_e001.pgm");
	strcpy(outfile,"output/xmorph_e001.pgm");
				//  012345678901234567890123

	uint8 **I0 = ui8matrix(-1, HAUTMORPH, -1, LARGMORPH);
	uint8 **I1 = ui8matrix(-1, HAUTMORPH, -1, LARGMORPH);

	for(int i = 2; i <= 200; i++)
	{
		MLoadPGM_ui8matrix(fname0, 0, HAUTMORPH, 0, LARGMORPH, I0);
		erosion(I0, I1, HAUT+1, LARG+1);
		dilatation(I1, I0, HAUT+1, LARG+1);
		dilatation(I0, I1, HAUT+1, LARG+1);
		erosion(I1, I0, HAUT+1, LARG+1);
		// printf("hola0 %d\n", i);
		SavePGM_ui8matrix(I0, 0, HAUTMORPH, 0, LARGMORPH, outfile);
		// printf("hola1 %d\n", i);

		aux = (fname0[15]-'0')*100 + (fname0[16]-'0')*10 + (fname0[17]-'0') + 1;
		fname0[15] = outfile[15] = aux / 100 + '0';
		fname0[16] = outfile[16] = (aux / 10) % 10 + '0';
		fname0[17] = outfile[17] = aux % 10 + '0';
	}

	free(fname0);
	free(outfile);
	free_ui8matrix(I0, -1, HAUTMORPH, -1, LARGMORPH);
	free_ui8matrix(I1, -1, HAUTMORPH, -1, LARGMORPH);

	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("Temps pour 200 morphos en: %f\n", total_t);
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
