#ifndef PILE_H
#define PILE_H

#define TAILLE_PILE 10

/// @brief type pile : structure de pile de void*
typedef struct pile {
    void* tab[TAILLE_PILE];
    int index;
} pile;

/// @brief fonction pile_vide : cree une pile vide
/// @return pile vide
pile pile_vide();

/// @brief fonction pile_est_vide : teste si une pile est vide
/// @param p : pile a tester
/// @return 1 si la pile est vide, 0 sinon
int pile_est_vide(pile p);

/// @brief fonction pile_est_pleine : teste si une pile est pleine
/// @param p : pile a tester
/// @return 1 si la pile est pleine, 0 sinon
int pile_est_pleine(pile p);

/// @brief fonction pile_push : empile un element dans une pile
/// @param p : pile dans laquelle empiler
/// @param e : element a empiler
void pile_push(pile *p, void* e);

/// @brief fonction pile_pop : depile un element dans une pile
/// @param p : pile dans laquelle depiler
/// @return element depile
void* pile_pop(pile *p);

/// @brief fonction pile_top : retourne l'element au sommet de la pile
/// @param p : pile dans laquelle chercher
/// @return element au sommet de la pile
void* pile_top(pile p);

/// @brief fonction pile_taille : retourne la taille de la pile
/// @param p : pile dont on veut la taille
/// @return taille de la pile
int pile_taille(pile p);







#endif