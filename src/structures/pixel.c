#include "pixel.h"
#include "color.h"


// Fonction set_pixel
void set_pixel(Pixel *pix, Couleur col, Opacite opa)
{
    pix->col = col;
    pix->opa = opa;
}

// Fonction equals_pixel
int equals_pixel(Pixel pix1, Pixel pix2)
{
    return equals_color(pix1.col, pix2.col) && pix1.opa == pix2.opa;
}

// Fonction new_pixel
Pixel new_pixel(Couleur col, Opacite opa)
{
    Pixel p;
    p.col = col;
    p.opa = opa;
    return p;
}

// Fonction get_pixel_color
Couleur get_pixel_color(Pixel pix)
{
    return pix.col;
}

// Fonction get_pixel_opacity
Opacite get_pixel_opacity(Pixel pix)
{
    return pix.opa;
}