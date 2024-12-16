#ifndef CALQUE_H
#define CALQUE_H

#include "types.h"

/// @brief type calque : grille carrée de pixels de la taille de l'image à produire et la taille de la grille
typedef struct calque *Calque;

/// @brief fonction new_calque : crée un nouveau calque
/// @param taille : taille du calque
/// @return calque
void new_calque(Calque *c);

/// @brief fonction delete_calque : supprime un calque
/// @param c : calque
void delete_calque(Calque *c);

/// @brief fonction get_calque_pixel : retourne le pixel à la position (x, y) du calque
/// @param c : calque
/// @param x : abscisse
/// @param y : ordonnée
/// @return pixel
Pixel get_calque_pixel(Calque c, int x, int y);

/// @brief fonction set_calque_pixel : modifie le pixel à la position (x, y) du calque
/// @param c : calque
/// @param x : abscisse
/// @param y : ordonnée
/// @param p : pixel
void set_calque_pixel(Calque c, int x, int y, Pixel p);

/// @brief fonction merge_two_calques : fusionne deux calques et stocke le résultat dans c1
/// @param c0 : premier calque
/// @param c1 : deuxième calque
void merge_two_calques(Calque c0, Calque c1);

/// @brief fonction decoupe_two_calques : découpe un calque en utilisant un autre calque comme masque
/// @param c1 : calque à découper
/// @param c0 : masque de découpe
void decoupe_one_calque(Calque c1, Calque c0);

/// @brief fonction free_coord : libère la mémoire allouée à une coordonnée
/// @param c : coordonnée
void free_coord(void** c);

/// @brief fonction fill_calque : remplit un calque
/// @param x : abscisse
/// @param y : ordonnée
/// @param old: ancienne couleur
/// @param new: nouvelle couleur
/// @param c : calque
void fill_calque(int x, int y, Pixel old, Pixel new, Calque c);

#endif