#include <stdlib.h>
#include "constantes.h"
#include "pile.h"

/// @brief type pile : structure de pile de void*
struct pile {
    void* tab[SIZE_CALQUES_STACK];
    int index;
};

// Fonction pile_vide
void pile_vide(Pile *p)
{
    *p = malloc(sizeof(struct pile));
    (*p)->index = -1;
}

// Fonction pile_est_vide
int pile_est_vide(Pile p)
{
    if ( p != NULL)
    {
        return p->index == -1;
    }

    return 1;
}

// Fonction pile_est_pleine
int pile_est_pleine(Pile p)
{
    if (p != NULL)
    {
        return p->index == SIZE_CALQUES_STACK - 1;
    }

    return 0;
}

// Fonction pile_push
void pile_push(Pile p, void* e)
{
    if (pile_est_pleine(p))
    {
        return;
    }
    else if ( p == NULL)
    {
        return;
    }

    p->index++;
    p->tab[p->index] = e;
}

// Fonction pile_pop
void* pile_pop(Pile p)
{
    if (pile_est_vide(p))
    {
        return NULL;
    }
    void* e = p->tab[p->index];
    p->index--;
    return e;
}

// Fonction pile_top
void* pile_top(Pile p)
{
    if (pile_est_vide(p))
    {
        return NULL;
    }
    return (p->tab)[p->index];
}

// Fonction pile_taille
int pile_taille(Pile p)
{
    if (p == NULL)
    {
        return 0;
    }

    return p->index + 1;
}

// Fonction pile_delete
void pile_delete(Pile *p, void (*delete_void)(void**))
{
    if (*p == NULL)
    {
        return;
    }

    int taille = (*p)->index;

    if (delete_void != NULL)
    {
        for (int i = 0; i <= taille; i++) {
            delete_void(&((*p)->tab[i]));
        }
    }

    free(*p);
}