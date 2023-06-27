#ifndef GLOBALS_H
#define GLOBALS_H

#include "types.h"

extern etat STATE;

/* n
Ajoute la couleur noire (c'est-à-dire (0,0,0)) dans le seau de couleurs.
r
Ajoute la couleur rouge (c'est-à-dire (255,0,0)) dans le seau de couleurs.
g
Ajoute la couleur verte (c'est-à-dire (0,255,0)) dans le seau de couleurs.
b
Ajoute la couleur bleue (c'est-à-dire (0,0,255)) dans le seau de couleurs.
y
Ajoute la couleur jaune (c'est-à-dire (255,255,0)) dans le seau de couleurs.
m
Ajoute la couleur magenta (c'est-à-dire (255,0,255)) dans le seau de couleurs.
c
Ajoute la couleur cyan (c'est-à-dire (0,255,255)) dans le seau de couleurs.
w
Ajoute la couleur blanche (c'est-à-dire (255,255,255)) dans le seau de couleurs. */

extern const couleur NOIR;
extern const couleur ROUGE;
extern const couleur VERT;
extern const couleur BLEU;
extern const couleur JAUNE;
extern const couleur MAGENTA;
extern const couleur CYAN;
extern const couleur BLANC;

/* t
Ajoute l'opacité transparente (0) dans le seau d'opacités.
o
Ajoute l'opacité complète (255) dans le seau d'opacités. */
extern const opacite TRANSPARENT;
extern const opacite OPAQUE;

#endif