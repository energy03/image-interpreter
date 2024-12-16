#ifndef LOGIC_H
#define LOGIC_H

#include "types.h"
#include <stdio.h>

/// @brief fonction add_color_to_seau : ajoute une couleur à un seau
/// @param c : couleur
void add_color_to_seau(Couleur c);

/// @brief fonction add_opacity_to_seau : ajoute une opacité à un seau
/// @param o : opacité
void add_opacity_to_seau(Opacite o);

/// @brief fonction clear_seaux : vide les seaux de couleur et d'opacité
void clear_seaux();

/// @brief fonction step_forward : avance d'un pas dans la direction courante
void step_forward();

/// @brief fonction turn_clockwise : tourne dans le sens horaire
void turn_clockwise();

/// @brief fonction turn_counterclockwise : tourne dans le sens anti-horaire
void turn_counterclockwise();

/// @brief fonction update_marqued_position : met à jour la position marquée
void update_marqued_position();

/// @brief fonction draw_line : dessine une ligne entre la position courante et la position marquée
void draw_line();

/// @brief fonction fill : remplit une zone de couleur
void fill();

/// @brief fonction add_new_calque : ajoute un nouveau calque à la pile
void add_new_calque();


/// @brief fonction merge_calques : fusionne les deux calques les plus hauts de la pile
void merge_calques();

/// @brief fonction decoupe_calque : découpe un calque en utilisant un autre calque comme masque
void decoupe_calque();

/// @brief fonction init_state : initialise l'état
/// @param taille : taille de l'image
void init_state(int taille);

/// @brief fonction delete_state : supprime l'état
void delete_state();

/// @brief function read_stream : lit un fichier et interprète les commandes
/// @param fd_in : fichier d'entrée
void read_stream(FILE* fd_in);

/// @brief function write_stream : écrit l'image sur un fichier
/// @param fd_out : fichier de sortie
void write_stream(FILE* fd_out);


#endif