#ifndef SEAU_H
#define SEAU_H
#include "constantes.h"

/// @brief type seau : multiensemble de void*
typedef struct seau {
    void* tab[TAILLE_MAX_TABLEAU];
    int nb_elem;
} seau;

/// @brief fonction seau_vide : cree un seau vide
/// @return seau vide
seau seau_vide();

/// @brief fonction seau_est_vide : teste si un seau est vide
/// @param s : seau a tester
/// @return 1 si le seau est vide, 0 sinon
int seau_est_vide(seau s);

/// @brief fonction seau_est_plein : teste si un seau est plein
/// @param s : seau a tester
/// @return 1 si le seau est plein, 0 sinon
int seau_est_plein(seau s);

/// @brief fonction seau_ajout : ajoute un element dans un seau
/// @param s : seau dans lequel ajouter
/// @param e : element a ajouter
void seau_ajout(seau *s, void* e);

/// @brief fonction seau_suppr : supprime un element dans un seau
/// @param s : seau dans lequel supprimer
/// @param e : element a supprimer
void seau_suppr(seau *s, void* e);

/// @brief fonction seau_vider : vide un seau
/// @param s : seau a vider
void seau_vider(seau *s);

/// @brief fonction seau_taille : retourne la taille du seau
/// @param s : seau dont on veut la taille
/// @return taille du seau
int seau_taille(seau s);


#endif