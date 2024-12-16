#include "color.h"

// Fonction get_color_r
composante get_color_r(Couleur col)
{
    return col.r;
}

// Fonction get_color_g
composante get_color_g(Couleur col)
{
    return col.g;
}

// Fonction get_color_b
composante get_color_b(Couleur col)
{
    return col.b;
}

// Fonction set_color
void set_color_1(Couleur *col, Couleur val)
{
    col->r = val.r;
    col->g = val.g;
    col->b = val.b;
}

// Fonction set_color
void set_color_2(Couleur *col, composante r, composante g, composante b)
{
    col->r = r;
    col->g = g;
    col->b = b;
}

// Fonction equals_color
int equals_color(Couleur col1, Couleur col2)
{
    return col1.r == col2.r && col1.g == col2.g && col1.b == col2.b;
}

// Fonction new_color
Couleur new_color(composante r, composante g, composante b)
{
    Couleur c;
    c.r = r;
    c.g = g;
    c.b = b;
    return c;
}

Couleur new_color_1(composante tab[]) {
    return new_color(tab[0], tab[1], tab[2]);
}