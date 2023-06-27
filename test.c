#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "headers/types.h"

int main(int argc, char *argv[]) {
    srand(time(NULL));
    if(argc != 3) {
        printf("Usage: %s <filename> <size>\n", argv[0]);
        return 1;
    }
    int size = atoi(argv[2]);
    if(size > TAILLE_MAX_TABLEAU) {
        printf("Size must be less than %d\n", TAILLE_MAX_TABLEAU);
        return 1;
    }
    FILE *f = fopen(argv[1], "w");
    if(f == NULL) {
        printf("Error opening file %s\n", argv[1]);
        return 1;
    }

    calque c;
    c.taille = size;
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            c.pix[i][j].col.r = 0;
            c.pix[i][j].col.g = 0;
            c.pix[i][j].col.b = 0;
            c.pix[i][j].opa = 0;
        }
    }
    c.pix[5][5].col = (couleur){80, 0, 0};
    // ecriture de l'image
    fprintf(f, "P6\n%d %d\n255\n", size, size);
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            fwrite(&c.pix[i][j].col, sizeof(couleur), 1, f);
        }
    }

}