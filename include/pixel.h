#ifndef PIXEL_H
#define PIXEL_H

#include "types.h"


/// @brief set_pixel : modifie un pixel
/// @param pix
/// @param col
/// @param opa
void set_pixel(Pixel *pix, Couleur col, Opacite opa);

/// @brief equals_pixel : vérifie si deux pixels sont égaux
int equals_pixel(Pixel pix1, Pixel pix2);

/// @brief new_pixel : crée un nouveau pixel
/// @param col
/// @param opa
Pixel new_pixel(Couleur col, Opacite opa);

/// @brief get_pixel_color : retourne la couleur d'un pixel
/// @param pix
/// @return couleur du pixel
Couleur get_pixel_color(Pixel pix);

/// @brief get_pixel_opacity : retourne l'opacité d'un pixel
/// @param pix
/// @return opacité du pixel
Opacite get_pixel_opacity(Pixel pix);

#endif