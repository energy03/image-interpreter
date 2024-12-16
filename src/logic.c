#include "pile.h"
#include "globals.h"
#include "constantes.h"
#include "seau.h"
#include "types.h"
#include "logic.h"
#include "color.h"
#include "pixel.h"
#include "calque.h"

// Fonction add_color_to_seau
void add_color_to_seau(Couleur c)
{
    Seau s = STATE->seau_coul;
    SeauData e;
    set_seau_data_couleur(&e, c);
    seau_ajout(s, e);
}

// Fonction add_opacity_to_seau
void add_opacity_to_seau(Opacite o)
{
    Seau s = STATE->seau_opa;
    SeauData e;
    set_seau_data_opacite(&e, o);
    seau_ajout(s, e);
}

// Fonction clear_seaux
void clear_seaux()
{
    seau_vider(STATE->seau_coul);
    seau_vider(STATE->seau_opa);
}

// Fonction step_forward
void step_forward()
{
    switch (STATE->dir) {
        case NORD:
            (STATE->pos_cour).y = ((STATE->pos_cour).y + STATE->taille - 1) % STATE->taille;
            break;

        case EST:
            (STATE->pos_cour).x = ((STATE->pos_cour).x + 1) % STATE->taille;
            break;
        case SUD:
            (STATE->pos_cour).y = ((STATE->pos_cour).y + 1) % STATE->taille;
            break;
        case OUEST:
            (STATE->pos_cour).x = ((STATE->pos_cour).x + STATE->taille - 1) % STATE->taille;
            break;
    }
}

// Fonction turn_clockwise
void turn_clockwise()
{
    switch (STATE->dir) {
        case NORD:
            STATE->dir = EST;
            break;
        case EST:
            STATE->dir = SUD;
            break;
        case SUD:
            STATE->dir = OUEST;
            break;
        case OUEST:
            STATE->dir = NORD;
            break;
    }
}

// Fonction turn_counterclockwise
void turn_counterclockwise()
{
    switch (STATE->dir) {
        case NORD:
            STATE->dir = OUEST;
            break;
        case EST:
            STATE->dir = NORD;
            break;
        case SUD:
            STATE->dir = EST;
            break;
        case OUEST:
            STATE->dir = SUD;
            break;
    }
}

// Fonction update_marqued_position
void update_marqued_position()
{
    STATE->pos_marq.x = STATE->pos_cour.x;
    STATE->pos_marq.y = STATE->pos_cour.y;
}

// Fonction current_pixel
Pixel current_pixel()
{
    Seau s_coul = STATE->seau_coul;
    Seau s_opa = STATE->seau_opa;
    Opacite moy_opa;
    composante moy_col[3] = {0, 0, 0};
    
    int nb_col = seau_taille(s_coul);

    if (seau_est_vide(s_opa)) {
        moy_opa = 255;
    }
    else {
        moy_opa = 0;
        int nb_opa = seau_taille(s_opa);
        for (int i = 0; i < nb_opa; i++) {
            moy_opa += seau_data_opacite(seau_get(s_opa, i));
        }

        moy_opa /= nb_opa;
    }

    if (!seau_est_vide(s_coul)) {
        for (int i = 0; i < nb_col; i++) {
            SeauData e = seau_get(s_coul, i);
            Couleur c = seau_data_couleur(e);
            moy_col[0] += get_color_r(c);
            moy_col[1] += get_color_g(c);
            moy_col[2] += get_color_b(c);
        }
        for (int j = 0; j < 3; j++) {
            moy_col[j] /= nb_col;
        }
    }

    Couleur c = new_color(moy_col[0], moy_col[1], moy_col[2]);

    return new_pixel(c, moy_opa);
}

// Fonction draw_line
void draw_line()
{
    int x0 = STATE->pos_cour.x;
    int y0 = STATE->pos_cour.y;
    int x1 = STATE->pos_marq.x;
    int y1 = STATE->pos_marq.y;
    if (x0 == x1 && y0 == y1) {
        return;
    }
    int dx = x1 - x0;
    int dy = y1 - y0;
    int ab_dx = dx >= 0 ? dx : -dx;
    int ab_dy = dy >= 0 ? dy : -dy;
    int d = ab_dx >= ab_dy ? ab_dx : ab_dy;
    int s;
    if (dx * dy > 0) {
        s = 0;
    } else {
        s = 1;
    }
    int x = x0 * d + (d - s) / 2;
    int y = y0 * d + (d - s) / 2;

    Calque c = (Calque) pile_top(STATE->pile_calques);
    Pixel p = current_pixel();
    for (int i = 0; i <= d; i++) {
        set_calque_pixel(c, x / d, y / d, p);
        x += dx;
        y += dy;
    }
    set_calque_pixel(c, x1, y1, p);
}

// Fonction fill
void fill() {
    Calque c = (Calque) pile_top(STATE->pile_calques);
    if ( c == NULL) {
        return;
    }
    Pixel p = current_pixel();
    Pixel old = get_calque_pixel(c, STATE->pos_cour.x, STATE->pos_cour.y);
    fill_calque(STATE->pos_cour.x, STATE->pos_cour.y, old, p, c);
}

// Fonction add_new_calque
void add_new_calque()
{
    Calque c;
    new_calque(&c);
    pile_push(STATE->pile_calques, c);
}

// Fonction merge_calques
void merge_calques()
{
    if (pile_taille(STATE->pile_calques) < 2) {
        return;
    }
    Calque c0 = (Calque) pile_pop(STATE->pile_calques);
    Calque c1 = (Calque) pile_top(STATE->pile_calques);
    merge_two_calques(c0, c1);
    delete_calque(&c0);
}

// Fonction decoupe_calque
void decoupe_calque() {
    if (pile_taille(STATE->pile_calques) < 2) {
        return;
    }
    Calque c0 = (Calque) pile_pop(STATE->pile_calques);
    Calque c1 = (Calque) pile_top(STATE->pile_calques);
    decoupe_one_calque(c1, c0);
    delete_calque(&c0);
}

// Fonction write_image
void write_stream(FILE* fd_out)
{
    Calque c = (Calque) pile_top(STATE->pile_calques);
    Pixel p;
    int taille = STATE->taille;
    
    fprintf(fd_out, "P6\n%d %d\n255\n", taille ,taille);
    for (int j = 0; j < taille; j++) {
        for (int i = 0; i < taille; i++) {
            p = get_calque_pixel(c, i, j);
            Couleur col = get_pixel_color(p);
            fwrite(&col, sizeof(Couleur), 1, fd_out);
        }
    }
}

// Fonction init_state
void init_state(int taille)
{
    STATE = malloc(sizeof(struct etat));
    STATE->pos_cour.x = 0;
    STATE->pos_cour.y = 0;
    STATE->pos_marq.x = 0;
    STATE->pos_marq.y = 0;
    STATE->dir = EST;
    STATE->taille = taille;
    seau_vide(&STATE->seau_coul);
    seau_vide(&STATE->seau_opa);
    pile_vide(&STATE->pile_calques);
    add_new_calque();
}

// Fonction delete_state
void delete_state()
{
    delete_seau(&STATE->seau_coul);
    delete_seau(&STATE->seau_opa);
    pile_delete(&STATE->pile_calques, (void(*)(void**)) delete_calque);
    free(STATE);
}

// Fonction read_stream
void read_stream(FILE* fd_in) {
    char ch;
    int i = 0;
    while ((ch = getc(fd_in)) != EOF) {
        switch (ch) {
            case 'n':
                composante color1[3] = NOIR;
                add_color_to_seau(new_color(color1[0], color1[1], color1[2]));
                break;

            case 'b':
                composante color2[3] = BLEU;
                add_color_to_seau(new_color(color2[0], color2[1], color2[2]));
                break;

            case 'r':
                composante color3[3] = ROUGE;
                add_color_to_seau(new_color(color3[0], color3[1], color3[2]));
                break;

            case 'g':
                composante color4[3] = VERT;
                add_color_to_seau(new_color(color4[0], color4[1], color4[2]));
                break;

            case 'y':
                composante color5[3] = JAUNE;
                add_color_to_seau(new_color(color5[0], color5[1], color5[2]));
                break;

            case 'm':
                composante color6[3] = MAGENTA;
                add_color_to_seau(new_color(color6[0], color6[1], color6[2]));
                break;

            case 'c':
                composante color7[3] = CYAN;
                add_color_to_seau(new_color(color7[0], color7[1], color7[2]));
                break;

            case 'w':
                composante color8[3] = BLANC;
                add_color_to_seau(new_color(color8[0], color8[1], color8[2]));
                break;

            case 't':
                add_opacity_to_seau(TRANSPARENT);
                break;

            case 'o':
                add_opacity_to_seau(OPAQUE);
                break;

            case 'i':
                clear_seaux();
                break;

            case 'v':
                step_forward();
                break;

            case 'h':
                turn_clockwise();
                break;

            case 'a':
                turn_counterclockwise();
                break;

            case 'p':
                update_marqued_position();
                break;

            case 'l':
                draw_line();
                break;

            case 'f':
                fill();
                break;

            case 's':
                add_new_calque();
                break;

            case 'e':
                merge_calques();
                break;

            case 'j':
                decoupe_calque();
                break;
            default:
                break;            
        }
        i++;
        fprintf(stderr, "Commande %d: %c\n", i, ch);
    }
}