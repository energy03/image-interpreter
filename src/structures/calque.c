#include "calque.h"
#include "pixel.h"
#include "globals.h"
#include "color.h"
#include "pile.h"

// Structure calque
struct calque
{
    Pixel **pixels;
    int taille;
};

// Fonction new_calque
void new_calque(Calque *c)
{
    *c = malloc(sizeof(struct calque));
    (*c)->pixels = malloc(STATE->taille * sizeof(Pixel*));
    for (int i = 0; i < STATE->taille; i++)
    {
        (*c)->pixels[i] = malloc(STATE->taille * sizeof(Pixel));

        for (int j = 0; j < STATE->taille; j++)
        {
            (*c)->pixels[i][j].col = new_color(0, 0, 0);
            (*c)->pixels[i][j].opa = 0;
        }
    }
    (*c)->taille = STATE->taille;
}

// Fonction delete_calque
void delete_calque(Calque *c)
{
    if (*c == NULL)
    {
        return;
    }
    
    for (int i = 0; i < STATE->taille; i++)
    {
        free((*c)->pixels[i]);
    }
    free((*c)->pixels);
    free(*c);
}

// Fonction get_calque_pixel
Pixel get_calque_pixel(Calque c, int x, int y)
{
    return c->pixels[x][y];
}

// Fonction set_calque_pixel
void set_calque_pixel(Calque c, int x, int y, Pixel p)
{
    c->pixels[x][y].col = get_pixel_color(p);
    c->pixels[x][y].opa = get_pixel_opacity(p);
}

composante merge_composantes(composante c0, composante c1, Opacite a0)
{
    return c0 + ( ( c1 * (255 - a0) ) / 255 );
}

composante decoupe_composante(composante c, Opacite a0)
{
    return ( c * a0 ) / 255;
}

// Fonction merge_two_calques
void merge_two_calques(Calque c0, Calque c1)
{
    Pixel p0, p1;
    Opacite a0, a1, a;
    Couleur col0, col1;
    composante r, g, b;
    for (int i = 0; i < c0->taille; i++)
    {
        for (int j = 0; j < c0->taille; j++)
        {
            p0 = get_calque_pixel(c0, i, j);
            p1 = get_calque_pixel(c1, i, j);
            a0 = get_pixel_opacity(p0); 
            a1 = get_pixel_opacity(p1);
            col0 = get_pixel_color(p0);
            col1 = get_pixel_color(p1);
            a = merge_composantes(a0, a1, a0);
            r = merge_composantes(get_color_r(col0), get_color_r(col1), a0);
            g = merge_composantes(get_color_g(col0), get_color_g(col1), a0);
            b = merge_composantes(get_color_b(col0), get_color_b(col1), a0);
            set_color_2(&col1, r, g, b);
            set_pixel(&p1, col1, a);
            set_calque_pixel(c1, i, j, p1);
        }
    }
}

// Fonction decoupe_one_calque
void decoupe_one_calque(Calque c1, Calque c0)
{
    Pixel p;
    Opacite a, a0;
    Couleur c;
    composante r, g, b;
    for (int i = 0; i < c1->taille; i++)
    {
        for (int j = 0; j < c1->taille; j++)
        {
            a0 = get_pixel_opacity(get_calque_pixel(c0, i, j));
            p = get_calque_pixel(c1, i, j);
            a = get_pixel_opacity(p);
            c = get_pixel_color(p);
            r = decoupe_composante(get_color_r(c), a0);
            g = decoupe_composante(get_color_g(c), a0);
            b = decoupe_composante(get_color_b(c), a0);
            a = decoupe_composante(a, a0);
            set_color_2(&c, r, g, b);
            set_pixel(&p, c, a);
            set_calque_pixel(c1, i, j, p);
        }
    }
}

void free_coord(void** c)
{
    free(*c);
}

// Fonction fill_calque_acc (fonction auxiliaire)
// Prend en plus la pile p des coordonnées à traiter
void fill_calque_acc(Pixel old, Pixel new, Calque c, Pile p)
{
    if (equals_pixel(old, new))
    {
        return;
    }
    Coord* pos = (Coord*) pile_pop(p);
    int x = pos->x;
    int y = pos->y;
    pile_push(p, pos);

    while (!pile_est_vide(p))
    {
        pos = (Coord*) pile_pop(p);
        x = pos->x;
        y = pos->y;
        free_coord((void**) &pos);

        if (equals_pixel(get_calque_pixel(c, x, y), old))
        {
            set_calque_pixel(c, x, y, new);
            if (x > 0 && equals_pixel(get_calque_pixel(c, x - 1, y), old))
            {
                pos = malloc(sizeof(Coord));
                pos->x = x - 1;
                pos->y = y;
                pile_push(p, pos);
            }
            if (x < c->taille - 1 && equals_pixel(get_calque_pixel(c, x + 1, y), old))
            {
                pos = malloc(sizeof(Coord));
                pos->x = x + 1;
                pos->y = y;
                pile_push(p, pos);
            }
            if (y > 0 && equals_pixel(get_calque_pixel(c, x, y - 1), old))
            {
                pos = malloc(sizeof(Coord));
                pos->x = x;
                pos->y = y - 1;
                pile_push(p, pos);
            }
            if (y < c->taille - 1 && equals_pixel(get_calque_pixel(c, x, y + 1), old))
            {
                pos = malloc(sizeof(Coord));
                pos->x = x;
                pos->y = y + 1;
                pile_push(p, pos);
            }
        }
    }

    return fill_calque_acc(old, new, c, p);
}

// Fonction fill_calque
void fill_calque(int x, int y, Pixel old, Pixel new, Calque c)
{
    Pile p;
    pile_vide(&p);
    Coord* pos = malloc(sizeof(Coord));
    pos->x = x;
    pos->y = y;
    pile_push(p, pos);
    fill_calque_acc(old, new, c, p);

    pile_delete(&p, NULL);
}