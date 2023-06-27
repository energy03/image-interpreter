#ifndef TYPES_H
#define TYPES_H
#include "seau.h"
#include "pile.h"
#include "constantes.h"

/// @brief type composante : entier non signé sur 1 octet
typedef unsigned char composante;

/// type couleur : triplet de composantes
typedef struct {
    composante r;
    composante g;
    composante b;
} couleur;

/// @brief type opacite : composante de transparence
typedef composante opacite;

/// @brief type pixel : formé d'une couleur et d'une opacité
typedef struct {
    couleur col;
    opacite opa;
} pixel;

/// @brief type calque : grille carrée de pixels de la taille de l'image à produire et la taille de la grille
typedef struct calque {
    pixel pix[TAILLE_MAX_TABLEAU][TAILLE_MAX_TABLEAU];
    int taille;
} calque;

/// @brief type coord : coordonnées d'un pixel
typedef struct {
    int x;
    int y;
} coord;

/// @brief type direction : enumération des directions possibles
typedef enum {
    NORD,
    EST,
    SUD,
    OUEST
} direction;

/// @brief type etat : informations sur l'état
typedef struct etat{
    coord pos_cour; // position courante
    coord pos_marq; // position marquée
    direction dir; // direction courante
    seau seau_coul; // seau de couleur
    seau seau_opa; // seau d'opacité
    pile pile_calques; // pile de calques
} etat;







#endif