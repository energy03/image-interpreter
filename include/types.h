#ifndef TYPES_H
#define TYPES_H

#include <stdio.h>
#include <stdlib.h>

/// @brief type composante : entier non signé sur 1 octet
typedef unsigned char composante;

/// type couleur : triplet de composantes
typedef struct color {
    composante r;
    composante g;
    composante b;
} Couleur;

/// @brief type opacite : composante de transparence
typedef composante Opacite;

/// @brief type pixel : formé d'une couleur et d'une opacité
typedef struct pixel {
    Couleur col;
    Opacite opa;
} Pixel;

/// @brief type coord : coordonnées d'un pixel
typedef struct coord {
    int x;
    int y;
} Coord;

/// @brief type direction : enumération des directions possibles
typedef enum {
    NORD,
    EST,
    SUD,
    OUEST
} Direction;

/// @brief type seau : multiensemble de void*
typedef struct seau *Seau;

/// @brief type pile : structure de pile de void*
typedef struct pile *Pile;

/// @brief type etat : informations sur l'état
typedef struct etat{
    Coord pos_cour; // position courante
    Coord pos_marq; // position marquée
    Direction dir; // direction courante
    Seau seau_coul; // seau de couleur
    Seau seau_opa; // seau d'opacité
    Pile pile_calques; // pile de calques
    int taille; // taille de l'image
} *Etat;







#endif