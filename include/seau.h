#ifndef SEAU_H
#define SEAU_H
#include "types.h"

typedef union seau_data {
    Couleur couleur;
    Opacite opacite;
} SeauData;

/// @brief fonction seau_vide : cree un seau vide
/// @return seau vide
void seau_vide(Seau *s);

/// @brief fonction seau_est_vide : teste si un seau est vide
/// @param s : seau a tester
/// @return 1 si le seau est vide, 0 sinon
int seau_est_vide(Seau s);

/// @brief fonction seau_est_plein : teste si un seau est plein
/// @param s : seau a tester
/// @return 1 si le seau est plein, 0 sinon
int seau_est_plein(Seau s);

/// @brief fonction seau_ajout : ajoute un element dans un seau
/// @param s : seau dans lequel ajouter
/// @param e : element a ajouter
void seau_ajout(Seau s, SeauData e);

/// @brief fonction seau_vider : vide un seau
/// @param s : seau a vider
void seau_vider(Seau s);

/// @brief fonction seau_taille : retourne la taille du seau
/// @param s : seau dont on veut la taille
/// @return taille du seau
int seau_taille(Seau s);

/// @brief fonction seau_get : retourne l'element a l'indice i du seau
/// @param s : seau dans lequel chercher
/// @param i : indice de l'element a retourner
/// @return element a l'indice i du seau
SeauData seau_get(Seau s, int i);

/// @brief fonction seau_data_couleur : retourne la couleur d'un SeauData
/// @param e : SeauData dont on veut la couleur
/// @return couleur de l'element
Couleur seau_data_couleur(SeauData e);

/// @brief fonction seau_data_opacite : retourne l'opacite d'un SeauData
/// @param e : SeauData dont on veut l'opacite
/// @return opacite de l'element
Opacite seau_data_opacite(SeauData e);

/// @brief fonction set_seau_data_couleur : modifie la couleur d'un SeauData
/// @param e : SeauData a modifier
/// @param c : nouvelle couleur
void set_seau_data_couleur(SeauData *e, Couleur c);

/// @brief fonction set_seau_data_opacite : modifie l'opacite d'un SeauData
/// @param e : SeauData a modifier
/// @param o : nouvelle opacite
void set_seau_data_opacite(SeauData *e, Opacite o);

/// @brief fonction delete_seau: supprime un seau
/// @param s : seau a supprimer
void delete_seau(Seau *s);

#endif