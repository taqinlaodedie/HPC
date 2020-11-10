#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "nrdef.h"
#include "nrutil.h"
#include "vnrdef.h"
#include "vnrutil.h"
#include "myutils.h"
#include "mymacro.h"

/* ------------------------------------------------------------------------------- */
void MLoadPGM_vui8matrix(char *filename, int nrl, int nrh, int ncl, int nch, vuint8 **m)
/* ------------------------------------------------------------------------------- */
{
    /* cette version ne lit plus que le type P5 */
    
    int height, width, gris;
    FILE *file;
    
    char *buffer;
    int i;
    
    buffer = (char*) calloc(80, sizeof(char));
    /* ouverture du fichier */
    file = fopen(filename,"rb");
    if (file==NULL) 
        nrerror("ouverture du fichier impossible\n");
    //nrerror("ouverture du fichier %s impossible\n", filename);
    
    /* lecture de l'entete du fichier pgm */
    readitem(file, buffer);
    /*fscanf(fichier, "%s", buffer);*/

    if(strcmp(buffer, "P5") != 0)
        nrerror("entete du fichier %s invalide\n");
    //nrerror("entete du fichier %s invalide\n", filename);
    
    width  = atoi(readitem(file, buffer));	
    height = atoi(readitem(file, buffer));
    gris   = atoi(readitem(file, buffer));
    
    for(i=0; i<height; i++) {
        fread(&(m[i][0]), sizeof(vuint8), width/16, file);// sizeof(vuint8) = sizeof(uint8)*16
    }
    
    fclose(file);
    free(buffer);
}

/* ----------------------------------------------------------------------------------- */
void SavePGM_vui8matrix(vuint8 **m, int nrl, int nrh, int ncl, int nch, char *filename)
/* ----------------------------------------------------------------------------------- */
{
  int nrow = nrh-nrl+1;
  int ncol = nch-ncl+1;

  char buffer[80];
  
  FILE *file;
  int  i;

  file = fopen(filename, "wb");
  if (file == NULL)
    //nrerror("ouverture du fichier %s impossible dans SavePGM_bmatrix\n", filename);
    nrerror("ouverture du fichier %s impossible dans SavePGM_ui8matrix\n");

  /* enregistrement de l'image au format rpgm */

  sprintf(buffer,"P5\n%d %d\n255\n",ncol, nrow);
  fwrite(buffer,strlen(buffer),1,file);
  for(i=nrl; i<=nrh; i++)
    fwrite(&(m[i][0]), sizeof(vuint8), ncol/16, file);

  /* fermeture du fichier */
  fclose(file);
}