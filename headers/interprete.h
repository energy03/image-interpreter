#ifndef INTREPRETE_H
#define INTREPRETE_H
#include <stdio.h>

#include "types.h"
#include "pile.h"
#include "seau.h"

/// @brief fonction set_pixel : modifie la couleur d'un pixel
/// @param pix : pixel
/// @param col : couleur
/// @param opa : opacité
void set_pixel(pixel* pix, couleur col, opacite opa);

/// @brief fonction draw_line : dessine une ligne entre deux points
/// @param coord1 : coordonnées du premier point
/// @param coord2 : coordonnées du second point
/// @param cal : calque
void draw_line(coord coord1, coord coord2, calque* cal);

/// @brief fonction fill : Pour remplir une zone de couleur depuis la position (x,y) sur le calque calque
/// @param x : coordonnée x du point de départ
/// @param y : coordonnée y du point de départ
/// @param anc_pix : ancien pixel
/// @param nouv_pix : nouveau pixel
/// @param cal : calque
void fill(int x, int y, pixel anc_pix, pixel nouv_pix, calque * cal);

/// @brief fonction merge_calque : fusionne deux calques
/// @param cal1 : premier calque
/// @param cal2 : second calque
/// @return calque : calque fusionné
calque* merge_calque(calque cal1, calque cal2);

/// @brief fonction decoupe_calque : découpe un calque utilisant le un autre calque comme masque
/// @param cal1 : calque à découper
/// @param cal0 : calque masque
/// @return calque : calque découpé
calque* decoupe_calque(calque cal1, calque cal0);

/// @brief fonction ecrire_image : écrit l'image dans un fichier
/// @param cal : calque
/// @param fd_out : descripteur de fichier
void ecrire_image(calque cal, FILE* fd_out);

/// @brief fonction pour initialiser l'état
/// @param state : état
/// @param taille : taille du calque
void init_state(int taille);

/// @brief fonction apply_char : appliquer un effet sur l'état en fonction d'un caractère
/// @param state : état
/// @param c : caractère
void effet_char(int c);

/// @brief eval_pixel : evalue le pixel courant en fonction des seaux de couleur et d'opacité
/// @param state : état
pixel* eval_pixel();










#endif