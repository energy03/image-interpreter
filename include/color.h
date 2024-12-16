#ifndef COLOR_H
#define COLOR_H

#include "types.h"

/// @brief get_color_r : retourne la composante rouge d'une couleur
/// @param col : couleur
/// @return composante rouge
composante get_color_r(Couleur col);

/// @brief get_color_g : retourne la composante verte d'une couleur
/// @param col : couleur
/// @return composante verte
composante get_color_g(Couleur col);

/// @brief get_color_b : retourne la composante bleue d'une couleur
/// @param col : couleur
/// @return composante bleue
composante get_color_b(Couleur col);

/// @brief set_color : modifie une couleur
/// @param col
/// @param val
void set_color_1(Couleur *col, Couleur val);

/// @brief set_color : modifie une couleur
/// @param col
/// @param tab
void set_color_2(Couleur *col, composante r, composante g, composante b);

/// @brief equals_color : vérifie si deux couleurs sont égales
int equals_color(Couleur col1, Couleur col2);

/// @brief new_color : crée une nouvelle couleur
/// @param r
/// @param g
/// @param b
Couleur new_color(composante r, composante g, composante b);

/// @brief new_color_1 : crée une nouvelle couleur
/// @param tab
Couleur new_color_1(composante tab[]);

#endif