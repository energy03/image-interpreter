#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "seau.h"
#include "pile.h"
#include "calque.h"
#include "logic.h"

Etat STATE;
int main()
{   
    FILE* fd_in = stdin;
    FILE* fd_out = stdout;
    char buf[100];
    int size;
    // lecture de la premiere ligne du fichier et récupération de la taille de l'image
    fgets(buf, 100, fd_in);
    sscanf(buf, "%d", &size);

    // initialisation de l'etat
    init_state(size);

    // lecture du fichier et interprétation des commandes
    read_stream(fd_in);

    write_stream(fd_out);
    delete_state();
    return 0;
}