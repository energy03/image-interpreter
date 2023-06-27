#include <stdlib.h>
#include "../headers/pile.h"

// Fonction pile_vide
pile pile_vide()
{
    pile p;
    p.index = -1;
    return p;
}

// Fonction pile_est_vide
int pile_est_vide(pile p)
{
    return p.index == -1;
}

// Fonction pile_est_pleine
int pile_est_pleine(pile p)
{
    return p.index == TAILLE_PILE - 1;
}

// Fonction pile_push
void pile_push(pile *p, void* e)
{
    if (pile_est_pleine(*p))
    {
        exit(0);
    }
    p->index++;
    p->tab[p->index] = e;
}

// Fonction pile_pop
void* pile_pop(pile *p)
{
    if (pile_est_vide(*p))
    {
        exit(0);
    }
    void* e = p->tab[p->index];
    p->index--;
    return e;
}

// Fonction pile_top
void* pile_top(pile p)
{
    if (pile_est_vide(p))
    {
        exit(0);
    }
    return p.tab[p.index];
}

// Fonction pile_taille
int pile_taille(pile p)
{
    return p.index + 1;
}
