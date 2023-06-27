#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/types.h"
#include "../headers/seau.h"
#include "../headers/pile.h"
#include "../headers/interprete.h"

etat STATE;

// Couleurs de base
const couleur NOIR={0,0,0};
const couleur ROUGE={255,0,0};
const couleur VERT={0,255,0};
const couleur BLEU={0,0,255};
const couleur JAUNE={255,255,0};
const couleur MAGENTA={255,0,255};
const couleur CYAN={0,255,255};
const couleur BLANC={255,255,255};

// Opacités de base
const opacite TRANSPARENT=0;
const opacite OPAQUE=255;



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
    
    
    // Récupération d'un caractère
    int ch=getc(fd_in);
    // Tant que le fichier n'est pas fini
    while(ch != EOF && ch != '#')
    {
        
        
        // On interprete la pile
        effet_char(ch);
        // On récupère le caractère suivant
        ch = getc(fd_in);
    }

    calque* calc = (calque*)pile_top(STATE.pile_calques);
    // Ecrire l'image sur la sortie standard
    ecrire_image(*calc, fd_out);


    return 0;
}