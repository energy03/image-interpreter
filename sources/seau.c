#include <stdio.h>
#include <stdlib.h>
#include "../headers/seau.h"

// Fonction seau_vide
seau seau_vide()
{
    seau s;
    s.nb_elem = 0;
    return s;
}

// Fonction seau_est_vide
int seau_est_vide(seau s)
{
    return s.nb_elem == 0;
}

// Fonction seau_est_plein
int seau_est_plein(seau s)
{
    return s.nb_elem == TAILLE_MAX_TABLEAU;
}

// Fonction seau_ajout
void seau_ajout(seau *s, void* e)
{
    if (seau_est_plein(*s))
    {
        exit(0);
    }
    s->tab[s->nb_elem] = e;
    s->nb_elem++;
}

// Fonction seau_suppr
void seau_suppr(seau *s, void* e)
{
    if (seau_est_vide(*s))
    {
        exit(0);
    }
    int i = 0;
    while (s->tab[i] != e)
    {
        i++;
    }
    s->tab[i] = s->tab[s->nb_elem - 1];
    s->nb_elem--;
}

// Fonction seau_vider
void seau_vider(seau *s)
{
    for(int i = 0; i < s->nb_elem; i++)
    {
        s->tab[i] = NULL;
    }
    s->nb_elem = 0;
}

// Fonction seau_taille
int seau_taille(seau s)
{
    return s.nb_elem;
}


