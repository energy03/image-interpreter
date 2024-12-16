#include <stdio.h>
#include <stdlib.h>
#include "constantes.h"
#include "types.h"
#include "seau.h"
#include "color.h"
#include "globals.h"

struct seau {
    SeauData *tab;
    int nb_elem;
    int max_elem;
};

// Fonction seau_vide
void seau_vide(Seau* s)
{
    *s = malloc(sizeof(struct seau));
    (*s)->tab = malloc(sizeof(SeauData) * STATE->taille);
    (*s)->nb_elem = 0;
    (*s)->max_elem = STATE->taille;
}

// Fonction seau_est_vide
int seau_est_vide(Seau s)
{
    return s->nb_elem == 0;
}

// Fonction seau_est_plein
int seau_est_plein(Seau s)
{
    return s->nb_elem == s->max_elem;
}

// Fonction seau_ajout
void seau_ajout(Seau s, SeauData e)
{
    if (seau_est_plein(s))
    {
        return;
    }
    s->tab[s->nb_elem] = e;
    s->nb_elem++;
}
// Fonction seau_vider
void seau_vider(Seau s)
{
    s->nb_elem = 0;
}

// Fonction seau_taille
int seau_taille(Seau s)
{
    return s->nb_elem;
}

// Fonction seau_get
SeauData seau_get(Seau s, int i)
{
    return s->tab[i];
}

// Fonction seau_data_couleur
Couleur seau_data_couleur(SeauData e)
{
    return e.couleur;
}

// Fonction seau_data_opacite
Opacite seau_data_opacite(SeauData e)
{
    return e.opacite;
}

// Fonction set_seau_data_couleur
void set_seau_data_couleur(SeauData *e, Couleur c)
{
    e->couleur = c;
}

// Fonction set_seau_data_opacite
void set_seau_data_opacite(SeauData *e, Opacite o)
{
    e->opacite = o;
}

// Fonction delete_seau
void delete_seau(Seau *s)
{
    if (*s == NULL)
    {
        return;
    }
    free((*s)->tab);
    free(*s);
}

