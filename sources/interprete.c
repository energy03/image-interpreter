#include "../headers/interprete.h"
#include "../headers/types.h"
#include "../headers/globals.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>



// Fonction init_calque : initialise un calque
calque* init_calque(int taille)
{
    calque* cal = malloc(sizeof(calque));
    cal->taille = taille;
    for (int i = 0; i < taille; i++)
    {
        for (int j = 0; j < taille; j++)
        {
            cal->pix[i][j].col.r = 0;
            cal->pix[i][j].col.g = 0;
            cal->pix[i][j].col.b = 0;
            cal->pix[i][j].opa = 0;
        }
    }
    return cal;
}

/// @brief set_pixel : modifie un pixel
/// @param pix
/// @param col
/// @param opa
void set_pixel(pixel* pix, couleur col, opacite opa)
{
    pix->col.r = col.r;
    pix->col.g = col.g;
    pix->col.b = col.b;
    pix->opa = opa;
}

/* Pour tracer une ligne entre la position (x0, y0) à la position (x1, y1), on utilisera l'algorithme suivant : (|x| représente la valeur absolue de x, toutes les opérations se font sur les entiers)

δx := x1 - x0
δy := y1 - y0
d := max(|δx|, |δy|)
si δx et δx sont non nuls et de même signe
alors s := 0
sinon s := 1
x := x0 * d + (d - s) / 2
y := y0 * d + (d - s) / 2
répéter d fois
  changer le pixel en (x/d, y/d) par le pixel courant
  x := x + δx
  y := y + δy
changer le pixel en (x1, y1) par le pixel courant
Le pixel courant est celui correspondant aux seaux */
// Fonction draw_line : dessine une ligne entre deux points
void draw_line(coord coord1, coord coord2, calque* cal)
{
    int x0 = coord1.x;
    int y0 = coord1.y;
    int x1 = coord2.x;
    int y1 = coord2.y;
    int dx = x1 - x0;
    int dy = y1 - y0;
    int ab_dx= dx>=0 ? dx : -dx;
    int ab_dy= dy>=0 ? dy : -dy;
    int d = ab_dx >= ab_dy ? ab_dx : ab_dy;
    int s;
    if (dx * dy > 0)
    {
        s = 0;
    }
    else
    {
        s = 1;
    }
    int x = x0 * d + (d - s) / 2;
    int y = y0 * d + (d - s) / 2;

    pixel* pix_cour= eval_pixel();
    pixel* pix_1= &cal->pix[x1][y1];

    if(d!=0){
        for (int i = 0; i < d; i++)
        {
            pixel* pix = &cal->pix[x/d][y/d];
            set_pixel(pix, pix_cour->col, pix_cour->opa);
            x += dx;
            y += dy;
        }
    }
    
    
    set_pixel(pix_1, pix_cour->col, pix_cour->opa);
}


/*Remplissage
Pour remplir une zone de couleur depuis la position (x,y) sur le calque calque, on appellera la fonction fill décrite ci-dessous avec comme paramètres x, y, calque[x,y], courant, calque où courant est le pixel courant, à condition que ce pixel courant soit différent de celui déjà en (x,y), sinon on ne fait rien.

fonction fill(x, y, ancien, nouveau, calque)
  si calque[x,y] = ancien
  alors
    calque[x,y] := nouveau
    si x > 0 alors fill(x-1, y, ancien, nouveau, calque)
    si y > 0 alors fill(x, y-1, ancien, nouveau, calque)
    si x < size-1 alors fill(x+1, y, ancien, nouveau, calque)
    si y < size-1 alors fill(x, y+1, ancien, nouveau, calque)
où size est la taille de l'image à produire.

// Fonction equals_pixel : vérifie si deux pixels sont égaux


Remarque : sur de grands calques, une implémentation récursive de la fonction fill comme décrit ci-dessus peut conduire à des dépassements de pile. Vous devrez plutôt utiliser une pile explicite dans laquelle vous mettrez l'ensemble des positions qu'il reste encore à traiter. */


// Fonction equals_pixel : vérifie si deux pixels sont égaux
int equals_pixel(pixel pix1, pixel pix2)
{
    if (pix1.col.r == pix2.col.r && pix1.col.g == pix2.col.g && pix1.col.b == pix2.col.b && pix1.opa == pix2.opa)
    {
        return 1;
    }
    return 0;
}

// Fonction fill : 
void fill(int x, int y, pixel anc_pix, pixel nouv_pix, calque* cal){
    if (equals_pixel(cal->pix[x][y], anc_pix))
    {
        cal->pix[x][y].col.b = nouv_pix.col.b;
        cal->pix[x][y].col.g = nouv_pix.col.g;
        cal->pix[x][y].col.r = nouv_pix.col.r;
        cal->pix[x][y].opa = nouv_pix.opa;
        if (x > 0)
        {
            fill(x - 1, y, anc_pix, nouv_pix, cal);
        }
        if (y > 0)
        {
    
            fill(x, y - 1, anc_pix, nouv_pix, cal);
        }
        if (x < cal->taille - 1)
        {
            fill(x + 1, y, anc_pix, nouv_pix, cal);
        }
        if (y < cal->taille - 1)
        {
            fill(x, y + 1, anc_pix, nouv_pix, cal);
        }
    }
}

/* Fusion de calques
Pour fusionner deux calques c0 et c1, on procède de la manière suivante pour chacun des pixels du nouveau calque :

on note α0 l'opacité de c0 à cette position ;
la valeur de chacune des composantes du nouveau pixel (couleur et opacité) vaut celle en c0 plus (celle en c1 fois (255 - α0) divisé par 255).
Par exemple, si le pixel de c0 a pour couleur (127, 42, 0) et pour opacité 127, et que celui en c1 a pour couleur (0, 100, 200) et pour opacité 200, le pixel de la fusion aura pour couleur (127, 92, 100) et pour opacité 227.

Remarque : il n'y a pas de dépassement de capacité pour les nouvelles composantes, parce que de la façon dont est calculé le pixel courant, les composantes des couleurs ne peuvent pas être plus grandes que la composante de l'opacité. */
// fonction merge_calque : fusionne deux calques
calque* merge_calque(calque cal0, calque cal1)
{
    calque* cal= init_calque(cal0.taille);
    cal->taille = cal0.taille;
    for (int i = 0; i < cal->taille; i++)
    {
        for (int j = 0; j < cal->taille; j++)
        {
            cal->pix[i][j].col.r = (cal0.pix[i][j].col.r + cal1.pix[i][j].col.r * (255 - cal0.pix[i][j].opa) / 255);
            cal->pix[i][j].col.g = (cal0.pix[i][j].col.g + cal1.pix[i][j].col.g * (255 - cal0.pix[i][j].opa) / 255);
            cal->pix[i][j].col.b = (cal0.pix[i][j].col.b + cal1.pix[i][j].col.b * (255 - cal0.pix[i][j].opa) / 255);
            cal->pix[i][j].opa = cal0.pix[i][j].opa + cal1.pix[i][j].opa * (255 - cal0.pix[i][j].opa) / 255;
        }
    }
    return cal;
}

/* Découpage de calques
Pour découper un calque c1 en utilisant l'opacité d'un calque c0 comme masque, on procède de la manière suivante pour chacun des pixels du nouveau calque :

on note α0 l'opacité de c0 à cette position ;
la valeur de chacune des composantes du nouveau pixel (couleur et opacité) vaut celle en c1 fois α0 divisé par 255.
Par exemple, si le pixel de c0 a pour couleur (127, 42, 0) et pour opacité 127, et que celui en c1 a pour couleur (0, 100, 200) et pour opacité 200, le pixel de la fusion aura pour couleur (0, 49, 99) et pour opacité 99.

 */
// Fonction decoupe_calque : découpe un calque utilisant le un autre calque comme masque
calque* decoupe_calque(calque cal1, calque cal0)
{
    calque* cal= init_calque(cal0.taille);
    cal->taille = cal0.taille;
    
    for (int i = 0; i < cal->taille; i++)
    {
        for (int j = 0; j < cal->taille; j++)
        {
            cal->pix[i][j].col.r = (cal1.pix[i][j].col.r * cal0.pix[i][j].opa / 255);
            cal->pix[i][j].col.g = (cal1.pix[i][j].col.g * cal0.pix[i][j].opa / 255);
            cal->pix[i][j].col.b = (cal1.pix[i][j].col.b * cal0.pix[i][j].opa / 255);
            cal->pix[i][j].opa = cal1.pix[i][j].opa * cal0.pix[i][j].opa / 255;
        }
    }
    return cal;
}

// Fonction ecrire_image : écrit l'image dans un fichier
void ecrire_image(calque cal, FILE *fd_out)
{
    fprintf(fd_out, "P6\n%d %d\n255\n", cal.taille, cal.taille);
    for (int i = 0; i < cal.taille; i++)
    {
        for (int j = 0; j < cal.taille; j++)
        {
            /*fwrite(&cal.pix[i][j].col.r, 1, 1, fd_out);
            fwrite(&cal.pix[i][j].col.g, 1, 1, fd_out);
            fwrite(&cal.pix[i][j].col.b, 1, 1, fd_out);*/
            fwrite(&cal.pix[i][j].col, 1, sizeof(couleur), fd_out);
        }
    }
}



// Fonction init_state : initialise l'état
void init_state(int taille)
{
    STATE.pos_cour.x = 0;
    STATE.pos_cour.y = 0;
    STATE.pos_marq.x = 0;
    STATE.pos_marq.y = 0;
    STATE.dir = EST;
    STATE.seau_coul = seau_vide();
    STATE.seau_opa = seau_vide();
    STATE.pile_calques = pile_vide();
    pile_push(&(STATE.pile_calques), init_calque(taille));
}


/* n
Ajoute la couleur noire (c'est-à-dire (0,0,0)) dans le seau de couleurs.
r
Ajoute la couleur rouge (c'est-à-dire (255,0,0)) dans le seau de couleurs.
g
Ajoute la couleur verte (c'est-à-dire (0,255,0)) dans le seau de couleurs.
b
Ajoute la couleur bleue (c'est-à-dire (0,0,255)) dans le seau de couleurs.
y
Ajoute la couleur jaune (c'est-à-dire (255,255,0)) dans le seau de couleurs.
m
Ajoute la couleur magenta (c'est-à-dire (255,0,255)) dans le seau de couleurs.
c
Ajoute la couleur cyan (c'est-à-dire (0,255,255)) dans le seau de couleurs.
w
Ajoute la couleur blanche (c'est-à-dire (255,255,255)) dans le seau de couleurs.
t
Ajoute l'opacité transparente (0) dans le seau d'opacités.
o
Ajoute l'opacité complète (255) dans le seau d'opacités.
i
Vide les seaux de couleurs et d'opacité.
v
Avance la position du curseur d'un pas dans la direction courante ; si le bord de l'image est atteint, on repasse de l'autre coté.
h
Tourne la direction courante dans le sens horaire.
a
Tourne la direction courante dans le sens anti-horaire.
p
Met à jour la position marquée en y mettant la position actuelle du curseur.
l
Trace une ligne entre la position du curseur et la position marquée, en utilisant l'algorithme décrit ci-dessous.
f
Remplit la zone de même couleur autour du curseur, en la remplaçant par la couleur courante, à l'aide de l'algorithme décrit ci-dessous.
s
Ajoute un nouveau calque dans la pile de calques ; chaque pixel de ce nouveau calque sera formé de la couleur (0,0,0) et de l'opacité 0 ; s'il y a déjà 10 calques dans la pile, ne fait rien.
e
Fusionne les deux calques les plus hauts dans la pile, comme décrit ci-dessous ; il y aura donc un calque de moins dans la pile ; s'il n'y a qu'un seul calque, ne fait rien.
j
Découpe le calque situé juste en dessous du sommet de la pile en utilisant comme masque les opacités de celui au sommet (cf. ci-dessous) ; retire celui au sommet ; s'il n'y a qu'un seul calque, ne fait rien.
Les autres caractères seront ignorés, y compris les versions en majuscule des caractères ci-dessus. */
// Fonction apply_char : appliquer un effet sur l'état en fonction d'un caractère
void effet_char(int c)
{ 
    int taille = ((calque*)pile_top(STATE.pile_calques))->taille;

    switch (c){
    pixel anc_pix;
    pixel* pix;
    calque* cal;
    case 'n':
        seau_ajout(&STATE.seau_coul, (void*)&NOIR);
        //pix = eval_pixel();
        //cal = (calque*)pile_top(STATE.pile_calques);
        //set_pixel(&cal->pix[STATE.pos_cour.x][STATE.pos_cour.y], pix->col, pix->opa);
        break;
    
    case 'r':
        seau_ajout(&STATE.seau_coul, (void*)&ROUGE);
        //pix = eval_pixel();
        //cal = (calque*)pile_top(STATE.pile_calques);
        //set_pixel(&cal->pix[STATE.pos_cour.x][STATE.pos_cour.y], pix->col, pix->opa);
        break;
    case 'g':
        seau_ajout(&STATE.seau_coul, (void*)&VERT);
        //pix = eval_pixel();
        //cal = (calque*)pile_top(STATE.pile_calques);
        //set_pixel(&cal->pix[STATE.pos_cour.x][STATE.pos_cour.y], pix->col, pix->opa);
        break;
    case 'b':
        seau_ajout(&STATE.seau_coul, (void*)&BLEU);
        //pix = eval_pixel();
        //cal = (calque*)pile_top(STATE.pile_calques);
        //set_pixel(&cal->pix[STATE.pos_cour.x][STATE.pos_cour.y], pix->col, pix->opa);
        break;
    case 'y':
        seau_ajout(&STATE.seau_coul, (void*)&JAUNE);
        //pix = eval_pixel();
        //cal = (calque*)pile_top(STATE.pile_calques);
        //set_pixel(&cal->pix[STATE.pos_cour.x][STATE.pos_cour.y], pix->col, pix->opa);
        break;
    case 'm':
        seau_ajout(&STATE.seau_coul, (void*)&MAGENTA);
        //pix = eval_pixel();
        //cal = (calque*)pile_top(STATE.pile_calques);
        //set_pixel(&cal->pix[STATE.pos_cour.x][STATE.pos_cour.y], pix->col, pix->opa);
        break;
    case 'c':
        seau_ajout(&STATE.seau_coul, (void*)&CYAN);
        //pix = eval_pixel();
        //cal = (calque*)pile_top(STATE.pile_calques);
        //set_pixel(&cal->pix[STATE.pos_cour.x][STATE.pos_cour.y], pix->col, pix->opa);
        break;
    case 'w':
        seau_ajout(&STATE.seau_coul, (void*)&BLANC);
        //pix = eval_pixel();
        //cal = (calque*)pile_top(STATE.pile_calques);
        //set_pixel(&cal->pix[STATE.pos_cour.x][STATE.pos_cour.y], pix->col, pix->opa);
        break;
    case 't':
        seau_ajout(&STATE.seau_opa, (void*)&TRANSPARENT);
        //pix = eval_pixel();
        //cal = (calque*)pile_top(STATE.pile_calques);
        //set_pixel(&cal->pix[STATE.pos_cour.x][STATE.pos_cour.y], pix->col, pix->opa);
        break;
    case 'o':
        seau_ajout(&STATE.seau_opa, (void*)&OPAQUE);
        //pix = eval_pixel();
        //cal = (calque*)pile_top(STATE.pile_calques);
        //set_pixel(&cal->pix[STATE.pos_cour.x][STATE.pos_cour.y], pix->col, pix->opa);
        break;
    case 'i':
        seau_vider(&STATE.seau_coul);
        seau_vider(&STATE.seau_opa);
        //pix = eval_pixel();
        //cal = (calque*)pile_top(STATE.pile_calques);
        //set_pixel(&cal->pix[STATE.pos_cour.x][STATE.pos_cour.y], pix->col, pix->opa);
        break;
    case 'v':
        switch (STATE.dir)
        {
        case NORD:
            STATE.pos_cour. x= (STATE.pos_cour.x - 1 + taille) % taille;
            break;
        case EST:
            STATE.pos_cour.y = (STATE.pos_cour.y + 1) % taille;
            break;
        case SUD:
            STATE.pos_cour.x = (STATE.pos_cour.x + 1) % taille;
            break;
        case OUEST:
            STATE.pos_cour.y = (STATE.pos_cour.y - 1 + taille) % taille;
            break;
        }
        break;
    case 'h': // sens horaire
        switch (STATE.dir)
        {
        case NORD:
            STATE.dir = EST;
            break;
        case EST:
            STATE.dir = SUD;
            break;
        case SUD:
            STATE.dir = OUEST;
            break;
        case OUEST:
            STATE.dir = NORD;
            break;
        }
        break;
    
     case 'a': // sens anti-horaire
        switch (STATE.dir)
        {
        case NORD:
            STATE.dir = OUEST;
            break;
        case EST:
            STATE.dir = NORD;
            break;
        case SUD:
            STATE.dir = EST;
            break;
        case OUEST:
            STATE.dir = SUD;
            break;
        }
        break;
    case 'p':
        STATE.pos_marq.x = STATE.pos_cour.x;
        STATE.pos_marq.y = STATE.pos_cour.y;
        break;

    case 'l':
        draw_line(STATE.pos_cour, STATE.pos_marq, ((calque*)pile_top(STATE.pile_calques)));
        break;

    case 'f':
        
        anc_pix = ((calque*)pile_top(STATE.pile_calques))->pix[STATE.pos_cour.x][STATE.pos_cour.y];
        pix = eval_pixel();
        
        fill(STATE.pos_cour.x, STATE.pos_cour.y, anc_pix, *pix , (calque*)pile_top(STATE.pile_calques)); 
        break;
    
    case 's':
        if (!pile_est_pleine(STATE.pile_calques)) 
        {
            pile_push(&STATE.pile_calques, init_calque(taille));
        }
        break;
    
    case 'e':
        if (pile_taille(STATE.pile_calques) > 1)
        {
            calque cal1 = *((calque*)pile_pop(&STATE.pile_calques));
            calque cal2 = *((calque*)pile_pop(&STATE.pile_calques));
            calque* cal = merge_calque(cal1, cal2);
            pile_push(&STATE.pile_calques, cal);
        }
        break;
    
    /*case 'j':
        if (pile_taille(STATE.pile_calques) > 1)
        {
            calque cal1 = *(calque*)pile_pop(&STATE.pile_calques);
            calque cal2 = *((calque*)pile_top(STATE.pile_calques));
            calque* cal = decoupe_calque(cal2, cal1);
            pile_push(&STATE.pile_calques, cal);
        }
        break;
    */
    default:
        break;
    }

}

/* Calcul du pixel courant
Le pixel courant correspondant au contenu des seaux est calculé de la façon suivante :

on fait la moyenne (entière) des opacités du seau d'opacités, ce qui nous donne l'opacité courante ;
si ce seau est vide, on prend 255 comme valeur pour l'opacité courante ;
on fait la moyenne (entière) de chacune des composantes des couleurs contenues dans le seau de couleurs ;
la valeur de chaque composante de la couleur du pixel courant est alors cette moyenne multipliée par l'opacité calculée précédemment puis divisée par 255 ;
si le seau de couleurs est vide, on prend comme valeur 0 pour chacune des composantes de la couleur courante.
Par exemple, si le seau de couleurs contient deux doses de rouge (255,0,0) et une dose de jaune (255,255,0), et que le seau d'opacités contient une dose d'opacité complète (255) et une dose de transparence totale (0), la moyenne des doses d'opacité sera de 127. La moyenne des composantes des doses de couleur sera (255,85,0). Le pixel courant aura donc pour couleur (127, 42, 0) et pour opacité 127. */

/// @brief eval_pixel : evalue le pixel courant en fonction des seaux de couleur et d'opacité
/// @param state : état
pixel* eval_pixel(){
    // Recuperation des seaux
    pixel* pix = malloc(sizeof(pixel));
    seau* seau_coul = &STATE.seau_coul;
    seau* seau_opa = &STATE.seau_opa;
    // Calcul de l'opacité courante
    int opa_cour =255;
    if (!seau_est_vide(*seau_opa))
    {
        opa_cour = 0;
        int taille = seau_taille(*seau_opa);
        for (int i = 0; i < taille; i++)
        {
            opa_cour += *((opacite*)seau_opa->tab[i]);
        }
        opa_cour /= taille;
          
    }

    couleur coul_cour = {0,0,0};
    int moy_coul[3] = {0,0,0};
    /// Calcul de la couleur courante
    if (!seau_est_vide(*seau_coul))
    {
        int taille = seau_taille(*seau_coul);
        for (int i = 0; i < taille; i++)
        {
            moy_coul[0] += ((couleur*)seau_coul->tab[i])->r;
            moy_coul[1] += ((couleur*)seau_coul->tab[i])->g;
            moy_coul[2] += ((couleur*)seau_coul->tab[i])->b;
        }
        moy_coul[0] /= taille;
        moy_coul[1] /= taille;
        moy_coul[2] /= taille;

        coul_cour.r = moy_coul[0] * opa_cour / 255;
        coul_cour.g = moy_coul[1] * opa_cour / 255;
        coul_cour.b = moy_coul[2] * opa_cour / 255;
    }
    // Recuperation de la position courante
    coord pos_cour = STATE.pos_cour;
    // Affectation du pixel courant
    pix->col.b=coul_cour.b;
    pix->col.g=coul_cour.g;
    pix->col.r=coul_cour.r;
    pix->opa=opa_cour;
    return pix;

}

