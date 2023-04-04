#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// les constantes
#define NB_LIGNES 6
#define NB_COLONNES 7
#define PION_A 'X'
#define PION_B 'O'
#define VIDE ' '
#define INCONNU ' '

// les types
typedef int Grille[NB_LIGNES][NB_COLONNES];

// prototypes des fonctions
void initGrille(Grille laGrille);
void afficher(Grille laGrille, char pion);
bool grillePleine(Grille laGrille);
void jouer(Grille laGrille, char pion, int * ligne, int * colonne);
int choisirColonne(Grille laGrille, char pion);
int chercherLigne(Grille laGrille, int col);
bool estVainqueur(Grille laGrille, int lig, int col);
void finDePartie(char vainqueur);
void jouerB(Grille laGrille, char pion, int * ligne, int * colonne);
int ChoisirColonneStratLoin(Grille laGrille, int ligne, int colonne, char lePion);
int choisirColonneStrategie4();


// Programme principal. C'est le pion A qui commence Ã  jouer
int main()
{
    Grille laGrille;
    char vainqueur=INCONNU;
    int ligne, colonne;
    initGrille(laGrille);
    afficher(laGrille, PION_A);
    while (vainqueur==INCONNU && !grillePleine(laGrille)){
        jouerB(laGrille,PION_A, &ligne, &colonne);
        afficher(laGrille, PION_B);
        if (estVainqueur(laGrille, ligne, colonne) ){
            vainqueur = PION_A;
        } else if (!grillePleine(laGrille)){
            jouer(laGrille, PION_B, &ligne, &colonne);
            afficher(laGrille, PION_A);
            if (estVainqueur(laGrille, ligne, colonne) ){
                vainqueur = PION_B;
            }
        }
    }
    finDePartie(vainqueur);
    system(EXIT_SUCCESS);
}


void initGrille(Grille laGrille){
    int l, c;
    for (l=0 ; l<NB_LIGNES ; l++){
        for (c=0 ; c<NB_COLONNES ; c++){
            laGrille[l][c] = VIDE;
        }
    }
}

void afficher(Grille laGrille, char pion){
    int l, c;
    system("clear");
    printf("\t");
    printf("  %c\n", pion);
    printf("\t");
    for (c=0; c<NB_COLONNES ; c++){
        printf("----");
    }
    printf("-\n");
    for (l=0 ; l<NB_LIGNES ; l++){
        printf("\t");
        for (c=0; c<NB_COLONNES ; c++){
            printf("| %c ", laGrille[l][c]);
        }
        printf("|\n");
        printf("\t");
        for (c=0; c<NB_COLONNES ; c++){
            printf("----");
        }
        printf("-\n");
    }
    printf("\t");
    for (c=0; c<NB_COLONNES ; c++){
            printf("  %d ",c);
    }
    printf("\n\n");

}

bool grillePleine(Grille laGrille){
    bool pleine = true;
    int c = 0;
    while (pleine && c<NB_COLONNES){
        if (laGrille[0][c] == VIDE){
            pleine = false;
        }
        c++;
    }
    return pleine;
}

void jouer(Grille laGrille, char pion, int * ligne, int * colonne){
        *colonne = choisirColonne(laGrille, pion);
        *ligne = chercherLigne(laGrille, *colonne);
        laGrille[*ligne][*colonne] = pion;
}

void jouerB(Grille laGrille, char pion, int * ligne, int * colonne){
    *colonne = ChoisirColonneStratLoin(laGrille, *ligne, *colonne, pion);
    *ligne = chercherLigne(laGrille, *colonne);
    laGrille[*ligne][*colonne] = pion;
}

/**
 * \brief Ici c'est ma stratégie qui place le pion 2 case vers la gauche ou la droite en fonction du dernier pion jouer 
 * 
 * \param laGrille 
 * \param ligne 
 * \param colonne 
 * \param lePion 
 * \return "int" retourne la colonne ou le pion est jouer
 */
int ChoisirColonneStratLoin(Grille laGrille, int ligne, int colonne, char lePion)
{
    /**
     * \brief Je verifie si je commence premier ou pas (en gros je regarde si y'a aucun pion)
     *        Si y'a aucun pion alors la colonne est à 3 sinon je fait ma stratégie
     */
    bool col0 = true;
    bool pleine = true;
    bool vide;
    vide = false;
    for (int c = 0; c < NB_COLONNES; c++){
        if (laGrille[5][c] != VIDE){
            vide = true;
        }
    }
    if (vide == false)
    {
        colonne = 3;
    }else{

/**
 * \brief Ici c'est ma stratégie qui place le pion de 2 case à coté de celui du joueur qui vient d'être placer
 *        Ou à la case du milieu si je commence
 */
        if (colonne >=0 && colonne<5)
        {
            colonne+=2;
        } else {
            colonne-=2;
        }

/**
 * \brief ici je verifie si la ligne ou je place le pion est pleine, si elle est pleine alors je place en 0 si 0 et pleine alors je place en 1
*/
    ligne = 0;
    while (pleine && ligne<NB_LIGNES){
        if (laGrille[ligne][colonne] == VIDE){
            pleine = false;
        }
        ligne++;
    }
    if (pleine == true)
    {
        ligne = 0;
        colonne = 1;
        while (col0 && ligne<NB_LIGNES){
        if (laGrille[0][colonne] != VIDE){
            col0 = false;
        }
        ligne++;
    }
        if (col0 == false)
        {
            colonne = 0;
        }
    }
 
    }
    return colonne;
}

int choisirColonneStrategie4(){
    srand(time(NULL));
    int alea;
    alea=rand() % NB_COLONNES;
    return alea;
}

int choisirColonne(Grille laGrille, char pion){
    int col;

    do{
        printf("Numero de colonne ? ");
        scanf("%d", &col);
    } while (col<0 ||col>6);
    return col;
}

int chercherLigne(Grille laGrille, int col){
    int ligne = -1;

    while (ligne<NB_LIGNES-1 && laGrille[ligne+1][col]==VIDE){
        ligne++;
    }
    return ligne;
}

bool estVainqueur(Grille laGrille, int lig, int col){
    // consiste Ã  regarder si une ligne de 4 pions s'est formÃ©e autour du pion qui vient de tomber en (lig, col)
    char lePion = laGrille[lig][col];
    int cpt,i,j;

    // regarder la verticale, en comptant le nombre de pions au Sud (inutile de regarder au Nord du pion qui vient de tomber)
    i = lig;
    cpt = 0;
    while (i<NB_LIGNES && laGrille[i][col]==lePion){
        cpt++;
        i++;
    }
    if (cpt>=4){
        return true;
    }
    // regarder l'horizontale, en comptant le nombre de pions Ã  l'Est et Ã  l'Ouest
    j = col;
    cpt = 0;
    // on regarde Ã  l'est
    while (j>=0 && laGrille[lig][j]==lePion){
        cpt++;
        j--;
    }
    j = col+1;
    // on regarde Ã  l'ouest
    while (j<NB_COLONNES && laGrille[lig][j]==lePion){
        cpt++;
        j++;
    }
    if (cpt>=4){
        return true;
    }
    // regarder la diagonale descendante, en comptant le nombre de pions au Nord Ouest et au Sud Est
    i = lig;
    j = col;
    cpt = 0;
    // on regarde au Nord Ouest
    while (j>=0 && i>=0 && laGrille[i][j]==lePion){
        cpt++;
        i--;
        j--;
    }
    i = lig+1;
    j = col+1;
    // on regarde au Sud Est
    while (i<NB_LIGNES && j<NB_COLONNES && laGrille[i][j]==lePion){
        cpt++;
        i++;
        j++;
    }
    if (cpt>=4 ){
        return true;
    }
    // regarder la diagonale descendante, en comptant le nombre de pions au Nord Est et au Sud Ouest
    i = lig;
    j = col;
    cpt = 0;
    // on regarde au Nord Est
    while (j<NB_COLONNES && i>=0 && laGrille[i][j]==lePion){
        cpt++;
        i--;
        j++;
    }
    i = lig+1;
    j = col-1;
    // on regarde au Sud Ouest
    while (i<NB_LIGNES && j>=0 && laGrille[i][j]==lePion){
        cpt++;
        i++;
        j--;
    }
    if (cpt>=4 ){
        return true;
    }
    return false;
}

void finDePartie(char vainqueur){
    if (vainqueur != INCONNU){
        printf("Joueur %c vainqueur\n", vainqueur);
    } else {
        printf("MATCH NUL\n");
    }
}

/**
 * Numéro de colonne pour remplir : 4 5 4 5 3 4 6 3 5 4 4 5
 * 
*/