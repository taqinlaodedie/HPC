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

	for (i = 0; i < larg; i++) {
		img[i][-1] = img[i][0];
		img[i][haut] = img[i][haut-1];
	}

	for (i = -1; i <= haut; i++) {
		img[-1][i] = img[0][i];
		img[haut][i] = img[haut-1][i];
	}
}

void test_morpho()
{
	struct timeval t1, t2;
	double timeused;

	/* Test unitaire avec des images de 5*5 */
  	uint8 **I0 = ui8matrix(-1, 5, -1, 5);
	uint8 **I1 = ui8matrix(-1, 5, -1, 5);

	/* Benchmark */
	char *fname0 = "test_img/mouvement/output.pgm";
	I0 = ui8matrix(-1, IMG_HEIGHT+1, -1, IMG_LENGTH+1);
	I1 = ui8matrix(-1, IMG_HEIGHT+1, -1, IMG_LENGTH+1);

	MLoadPGM_ui8matrix(fname0, 0, IMG_HEIGHT-1, 0, IMG_LENGTH-1, I0);
	traitement_bord(I0, IMG_HEIGHT, IMG_LENGTH);

	CHRONO(erosion(I0, I1, IMG_HEIGHT, IMG_LENGTH);	\
		dilatation(I1, I0, IMG_HEIGHT, IMG_LENGTH);	\
		dilatation(I0, I1, IMG_HEIGHT, IMG_LENGTH);	\
		erosion(I1, I0, IMG_HEIGHT, IMG_LENGTH), "chaine de morpho sur 5*5");
	SavePGM_ui8matrix(I0, 0, IMG_HEIGHT-1, 0, IMG_LENGTH-1, "test_img/morpho/chaine_de_morpho.pgm");


	free_ui8matrix(I0, -1, IMG_HEIGHT+1, -1, IMG_LENGTH+1);
	free_ui8matrix(I1, -1, IMG_HEIGHT+1, -1, IMG_LENGTH+1);
}

void test_multi_morpho()
{
	clock_t start_t, end_t;
	double total_t;
	start_t = clock();

	char *fname0  = (char*)malloc(sizeof(char*) * 24);
	char *outfile = (char*)malloc(sizeof(char*) * 24);
	int aux;
	strcpy(fname0, "output/1_sigdel_e001.pgm");
	strcpy(outfile,"output/2_xmorph_e001.pgm");
				//  0123456789012345678901234

	uint8 **I0 = ui8matrix(-1, HAUT+1, -1, LARG+1);
	uint8 **I1 = ui8matrix(-1, HAUT+1, -1, LARG+1);

	for(int i = 2; i <= 200; i++)
	{
		MLoadPGM_ui8matrix(fname0, 0, HAUT, 0, LARG, I0);
		traitement_bord(I0, HAUT+1, LARG+1);
		erosion(I0, I1, HAUT+1, LARG+1);
		// traitement_bord(I1, HAUT+1, LARG+1);
		dilatation(I1, I0, HAUT+1, LARG+1);
		// traitement_bord(I0, HAUT+1, LARG+1);
		dilatation(I0, I1, HAUT+1, LARG+1);
		// traitement_bord(I1, HAUT+1, LARG+1);
		erosion(I1, I0, HAUT+1, LARG+1);
		SavePGM_ui8matrix(I0, 0, HAUT+1, 0, LARG+1, outfile);

		aux = (fname0[17]-'0')*100 + (fname0[18]-'0')*10 + (fname0[19]-'0') + 1;
		fname0[17] = outfile[17] = aux / 100 + '0';
		fname0[18] = outfile[18] = (aux / 10) % 10 + '0';
		fname0[19] = outfile[19] = aux % 10 + '0';
	}

	free(fname0);
	free(outfile);
	free_ui8matrix(I0, -1, HAUT+1, -1, LARG+1);
	free_ui8matrix(I1, -1, HAUT+1, -1, LARG+1);

	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("Temps pour 200 morphos\t\t\t\t\t: %f s\n", total_t);
}

void test_unitaire_morpho()
{
	uint8 **tab0 = ui8matrix(-1, 1, -1, 1);
	uint8 **tab1 = ui8matrix(-1, 1, -1, 1);
  	uint8 **tab2 = ui8matrix(-1, 5, -1, 5);
	uint8 **tab3 = ui8matrix(-1, 5, -1, 5);

	printf("\n\nTESTS UNITAIRES MORPHOLOGIE\n");

	/***************** TESTS UNITAIRES EROSION *****************/

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
				printf("KO\n");
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
				printf("KO\n");
			tab0[i][j] = 255;
		}
	}

	/***** TEST 3															*******
	****** Test d'érosion sur une matrice 5*5 initialisée comme ceci :		*******
	******			[000]  [000]  [000]  [000]  [000]						*******
	******			[255]  [255]  [255]  [000]  [000]						*******
	******			[255]  [255]  [255]  [255]  [000]						*******
	******			[255]  [255]  [255]  [255]  [000]						*******
	******			[000]  [000]  [000]  [255]  [000]						*******
	****** Bords initialisés à 255 pour ne pas influencer le résultat		*******
	****** Résultat attendu de la fonction érosion : 						*******
	******			[000]  [000]  [000]  [000]  [000]						*******
	******			[000]  [000]  [000]  [000]  [000]						*******
	******			[255]  [255]  [000]  [000]  [000]						*******
	******			[000]  [000]  [000]  [000]  [000]						*******
	******			[000]  [000]  [000]  [000]  [000]						******/

	// Initialisation
	for( int i = -1; i <= 5; i++ ) {
		tab2[0][i] = tab2[4][i] = 0;
		tab2[1][i] = tab2[2][i] = tab2[3][i] = 255;
		tab2[-1][i] = tab2[5][i] = 255;	// bords supérieur et inférieur
	}
	for( int i = 0; i < 4; i++ ) {
		tab2[i][-1] = tab2[i][5] = 255;	// bords gauche et droit
		tab2[i][4] = 0;
	}
	tab2[1][3] = 0;
	tab2[4][3] = 255;

	display_ui8matrix(tab2, 0, 4, 0, 4, " [%03d] ", "\nTest 3 EROSION");
	erosion(tab2, tab3, 5, 5);
	display_ui8matrix(tab3, 0, 4, 0, 4, " [%03d] ", "\nRésultat attendu : 255 en [2][0] et [2][1], le reste à 0");

	/***************** TESTS UNITAIRES DILATATION *****************/

	/***** TEST 4															*******
	****** Toute la matrice tab0 à 255 initialement, puis					*******
	****** chaque élément devient 0 un par un								*******
	****** Résultat attendu de la fonction dilatation : 255 à chaque fois	******/

	display_ui8matrix(tab0, -1, 1, -1, 1, " [%03d] ", "\nTest 4 DILATATION");

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
				printf("KO\n");
			tab0[i][j] = 255;
		}
	}

	/***** TEST 5															*******
	****** Toute la matrice tab0 à 0 initialement, puis						*******
	****** chaque élément devient 255 un par un								*******
	****** Résultat attendu de la fonction dilatation : 255 à chaque fois	******/

	// Initialisation à 0
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			tab0[i][j] = 0;
		}
	}

	display_ui8matrix(tab0, -1, 1, -1, 1, " [%03d] ", "\nTest 5 DILATATION");

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
				printf("KO\n");
			tab0[i][j] = 0;
		}
	}

	/***** TEST 6															*******
	****** Test d'érosion sur une matrice 5*5 initialisée comme le test 3 :	*******
	******			[000]  [000]  [000]  [000]  [000]						*******
	******			[255]  [255]  [255]  [000]  [000]						*******
	******			[255]  [255]  [255]  [255]  [000]						*******
	******			[255]  [255]  [255]  [255]  [000]						*******
	******			[000]  [000]  [000]  [255]  [000]						*******
	****** Bords initialisés à 0 pour ne pas influencer le résultat			*******
	****** Résultat attendu de la fonction érosion : 						*******
	******			[255]  [255]  [255]  [255]  [000]						*******
	******			[255]  [255]  [255]  [255]  [255]						*******
	******			[255]  [255]  [255]  [255]  [255]						*******
	******			[255]  [255]  [255]  [255]  [255]						*******
	******			[255]  [255]  [255]  [255]  [255]						******/

	// Initialisation
	for( int i = -1; i <= 5; i++ ) {
		tab2[-1][i] = tab2[5][i] = 0;	// bords supérieur et inférieur
		tab2[i][-1] = tab2[i][5] = 0;	// bords gauche et droit
	}

	display_ui8matrix(tab2, 0, 4, 0, 4, " [%03d] ", "\nTest 6 DILATATION");
	dilatation(tab2, tab3, 5, 5);
	display_ui8matrix(tab3, 0, 4, 0, 4, " [%03d] ", "\nRésultat attendu : uniquement [0][4] à 0, le reste à 255");

	free_ui8matrix(tab0, -1, 5, -1, 5);
  	free_ui8matrix(tab1, -1, 5, -1, 5);
	free_ui8matrix(tab2, -1, 5, -1, 5);
  	free_ui8matrix(tab3, -1, 5, -1, 5);
}
