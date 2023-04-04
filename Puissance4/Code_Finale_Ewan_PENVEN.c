/**
 * \file Code_Finale_Ewan_PENVEN.c
 * \author Ewan PENVEN (ewan.penven@etudiant.univ-rennes1.fr)
 * \version 1.0
 * \date 2022-11-20
 * 
 * \brief Ce programme est un jeu Puissance 4
 * 
 * \copyright Copyright (c) 2022
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/*****************************************************
*               DECLARATION DES CONSTANTE            *
*****************************************************/
/**
 * \def NBLIG : est égale à 6.
 * \def NBCOL : est égale à 7.
 * \def constante COLONNE_DEBUT : est égale au nombre de colonne -1 le tout divisé à 2.
 * 
 * \brief les define sont utile ici pour la définition du tableau et la constante est utile pour définir le pion à la bonne 
 *        colonne quand on affiche la grille.
 */
const char PION_A = 'X';
const char PION_B= 'O';
const char VIDE= ' ';
const char INCONNU = ' ';
#define NBLIG 6
#define NBCOL 7
const int COLONNE_DEBUT = (NBCOL-1)/2;
/*****************************************************
*                DECLARATION DU TABLEAU              *
*****************************************************/
/**
 * \typedef t_tableau.
 * 
 * \brief type tableau à 2 dimensions de NBLIG et NBCOL caractère.
 */
typedef char t_tableau [NBLIG][NBCOL];

/*****************************************************
*                DECLARATION DES FONCTION            *
*****************************************************/
void initGrille(t_tableau Grille);
void afficher(t_tableau Grille, char _caractere, int _colonne);
bool grillePleine(t_tableau Grille);
void jouer (t_tableau Grille, char _caractere, int *_ligne, int *_colonne);
int choisirColonne(t_tableau Grille, char _caractere, int _colonne);
int trouverLigne(t_tableau Grille, int _colonne);
void finDePartie(char _vainqueur);
bool estVainqueur(t_tableau Grille, int _col, int _lig);



/*****************************************************
*                  PROGRAMME PRINCIPAL               *
*****************************************************/
int main()
{
    char vainqueur;
    int ligne, colonne;
    t_tableau Grille;

    initGrille(Grille);
    vainqueur=INCONNU;
    afficher(Grille, PION_A, COLONNE_DEBUT);
    while (vainqueur==INCONNU && !grillePleine(Grille))
    {
        jouer(Grille, PION_A, &ligne, &colonne);
        afficher(Grille, PION_B, COLONNE_DEBUT);
        if (estVainqueur(Grille, colonne, ligne)==true) //Permet de savoir si le pion A est gagnant.
        {
            vainqueur=PION_A;
        }
        else if (grillePleine(Grille)==false) //On regarde si la grille es pleine ou non avant de continuer.
        {
            jouer(Grille, PION_B, &ligne, &colonne);
            afficher(Grille, PION_B, COLONNE_DEBUT);
            if (estVainqueur(Grille, colonne, ligne)==true) //Permet de savoir si le pion B est gagnant.
            {
                vainqueur=PION_B;
            }
        }
    }
    finDePartie(vainqueur);
}

/*****************************************************
*             PROGRAMME PROCEDURE/FONCTION           *
*****************************************************/

/**
 * \fn procédure initGrille.
 * \param Grille en entré/sortie : tableau t_tableau nommée dans la fonction en Grille.
 * 
 * \brief cette procédure permet d'initialiser le tableau avec le caractère VIDE.
 */
void initGrille(t_tableau Grille)
{
    int col, lgn;
    for (lgn=0; lgn<NBCOL; lgn++){
        for(col=0; col<NBCOL; col++){
            //Les boucles for permettent de parcourir le tableau Grille
            Grille[lgn][col] = VIDE;

        }
    }
}

/**
 * \fn procédure afficher.
 * 
 * \param Grille en entrée : t_tableau nommée en Grille.
 * \param _caractere en entrée : pour afficher le bon pion au dessus de la grille.
 * \param _colonne en entrée : l'indice de la colonne ou afficher le pion.
 * 
 * \brief cette procédure permet l'affichage de la Grille avec aussi l'affichage du pion à joué au dessus du tableau au bonne emplacement.
 */
void afficher(t_tableau Grille, char _caractere, int _colonne)
{
    int col, lgn;
    char tab[NBCOL];
    system ("clear");
    for (col = 0; col < NBCOL; col++)
    {
        tab[col]=VIDE;
    }
    tab[_colonne]=_caractere;
    printf("  %c   %c   %c   %c   %c   %c   %c", tab[0], tab[1], tab[2], tab[3], tab[4], tab[5], tab[6]);
    //Permet l'affichage du pion à chaque indice du tableau de tab 0 à 6 au dessus des bonnes colonnes du tableau Grille.
    printf("\n-----------------------------\n");
    
    for(lgn=0; lgn<NBLIG; lgn++){
        printf("|");
        for (col=0; col<NBCOL; col++){
            printf(" %c |", Grille[lgn][col]);
        }
        printf("\n-----------------------------\n");
    }
}

/**
 * \fn fonction booléenne grillePleine.
 * 
 * \param Grille en entrée : pour regarder chaque colonne et ligne de la grille.
 * \return true : si la grille est pleine.
 * \return false : si la grille n'est toujours pas pleine.
 * 
 * \brief Permet de savoir si la grille est pleine ou non.
 */
bool grillePleine(t_tableau Grille)
{
    int col, lgn;
    col=0;
    lgn=0;
    bool trouve;
    trouve = false;
    while((trouve=!true) || (col=!NBCOL))
    {
        if(Grille[lgn][col]==VIDE)
        {
            trouve = false;
        }else
        {
            trouve = true;
        }
        col++;
        lgn++;
    }
    return trouve;
}

/**
 * \fn procédure jouer.
 * 
 * \param Grille en entrée: qui permet d'être utiliser dans les fonctions.
 * \param _caractere en entrée : pour utiliser le pion du joueur dans la fonction choisirColonne.
 * \param _ligne en sortie : uniquement afin de la réutiliser dans la fonction estVainqueur.
 * \param _colonne en sortie : uniquement afin de la réutiliser dans la fonction estVainqueur.
 * 
 * \brief relie les fonction choisirColonne et trouverLigne et qui permet donc de mettre le pion ou l'utilisateur veut.
 */
void jouer(t_tableau Grille, char _caractere, int *_ligne, int *_colonne)
{
    int res;
    res=0;
    while (res!=1)
    {
        *_colonne=0;
        *_ligne=0;

        *_colonne = choisirColonne(Grille, _caractere, COLONNE_DEBUT);
        *_ligne = trouverLigne(Grille, *_colonne);
        if (*_ligne==-1)
        {
            printf("La colonne est pleine, recommencez");
        }
        else
        {
            res=1;
        }

        Grille[*_ligne][*_colonne]=_caractere;
    }
}

/**
 * \fn fonction entière trouverLigne.
 * 
 * \param Grille en entrée : utile pour parcourir la ligne de la colonne ou l'utilisateur veut placer son pion.
 * \param _colonne en entrée: afin de savoir quelle colonne l'utilisateur à choisi.
 * \return int : retourne l'indice de la ligne ou le pion doit être placé dans jouer.
 * 
 * \brief permet de mettre le pion au bon emplacement en partant toujours du bas de la grille.
 */
int trouverLigne(t_tableau Grille, int _colonne)
{    
    int ligne;
    ligne = NBLIG -1;
    while((Grille[ligne][_colonne] != VIDE) && (ligne!=NBLIG))
    {
        ligne--;
    }
    if(Grille[ligne][_colonne]!= VIDE)
    {
        ligne=-1;
        return ligne;
    }
    else
    {
        return ligne;
    }
}


/**
 * \fn fonction entière choisirColonne.
 * 
 * \param Grille en entrée : utile pour son affichage.
 * \param _caractere en entrée : le pion du joueur soir A soit B.
 * \param _colonne en entrée : permet de savoir quelle colonne l'utilisateur à choisi.
 * \return int : retourne l'indice de la colonne que l'utilisateur à choisi dans jouer.
 * 
 * \brief permet à l'utilisateur de choisir quelle colonne il veut placer son pion.
 */
int choisirColonne(t_tableau Grille, char _caractere, int _colonne)
{
    char touche;
    touche = 'f';
    _colonne=3;
    afficher(Grille, _caractere, _colonne);

    while (touche != ' ')
    {
        printf("Tapez 'q' pour aller à gauche, 'd' pour aller à droite, espace pour valider\n");
        scanf("%c", &touche);

        if (touche=='q')
        {
            _colonne--;
            afficher(Grille, _caractere, _colonne);
            if (_colonne<0){ //Permet de savoir si la personne est arrivée au bout du tableau et si il essaye de sortir du tableau 
            _colonne=0;
            afficher(Grille, _caractere, _colonne);
        }
        }
        else if (touche=='d')
        {
            _colonne++;
            if (_colonne>=6){//Permet de savoir si la personne est arrivée au bout du tableau et si il essaye de sortir du tableau
            _colonne=6;
            afficher(Grille, _caractere, _colonne);
        }
        afficher(Grille, _caractere, _colonne);
        }
    }
    return _colonne;
}

/**
 * \fn procédure finDePartie.
 * 
 * \param _vainqueur pour savoir quelle pion de joueur à gagner ou si le vainqueur est INCONNU alors cela veut dire qu'il y'a égalité.
 * 
 * \brief permet d'afficher qui à gagner ou si il y a égalité du à la grille qui est pleine.
 */
void finDePartie(char _vainqueur)
{
    if (_vainqueur == PION_A)
    {
        printf("*******************************************\n");
        printf("*******************BRAVO*******************\n");
        printf("***********Le joueur 1 à gagner !**********\n");
        printf("*******************************************\n");
    }
    else if (_vainqueur == PION_B)
    {
        printf("*******************************************\n");
        printf("*******************BRAVO*******************\n");
        printf("***********Le joueur 2 à gagner !**********\n");
        printf("*******************************************\n");
    }
    else if (_vainqueur ==  INCONNU)
    {
        printf("*******************************************\n");
        printf("******************DOMMAGE******************\n");
        printf("**********Aucun joueur à gagner !**********\n");
        printf("*******************************************\n");
    }
    
}

/**
 * \fn fonction booléenne estVainqueur.
 * 
 * \param Grille en entrée : utile pour parcourir le tableau et savoir si le pion est gagnant.
 * \param _col en entrée : l'indice de la colonne pour savoir si le pion à cette ligne fait un puissance 4.
 * \param _lig en entrée : l'indice de la ligne pour savoir si le pion à cette ligne fait un puissance 4.
 * \return true : retourne vrai si le pion à colonne et à la ligne qui est rentrer fait un puissance 4.
 * \return false : retourne faux si le pion à colonne et à la ligne qui est rentrer ne fait pas un puissance 4.
 * 
 * \brief permet de savoir si le pion fait un puissance 4, verticalement, horizontalement, et diagonalement.
 */
bool estVainqueur(t_tableau Grille, int _col, int _lig)
{
    int i, j, res;
    res=0;
    char pion;
    pion=Grille[_lig][_col];
    i=_lig;
    j=_col;
    bool vainqueur;
    vainqueur=false;


    //pour voir si il y'a un puissance 4 horizontalement.
    while ((Grille[i][j]==pion) && (res!=4))
    {
        i++;
        res++;
    }
    if (res==4)
    {
        vainqueur=true;
    }
    else
    {
        res=0;
        i=_lig;
        j=_col;
    }
    while ((Grille[i][j]==pion) && (res!=4))
    {
        i--;
        res++;
    }
    if (res==4)
    {
        vainqueur=true;
    }
    else
    {
        res=0;
        i=_lig;
        j=_col;
    }


    //pour savoir si il y'a un puissance 4 verticalement.
    while ((Grille[i][j]==pion) && (res!=4))
    {
        j++;
        res++;
    }
    if (res==4)
    {
        vainqueur=true;
    }
    else
    {
        res=0;
        i=_lig;
        j=_col;
    }
    while ((Grille[i][j]==pion) && (res!=4))
    {
        j--;
        res++;
    }
    if (res==4)
    {
        vainqueur=true;
    }
    else
    {
        res=0;
        i=_lig;
        j=_col;
    }
    

    //pour savoir si il y'a un puissance 4 diagonalement de bas droite à haut gauche.
    while ((Grille[i][j]==pion) && (res!=4))
    {
        j++;
        i++;
        res++;
    }
    if (res==4)
    {
        vainqueur=true;
    }
    else
    {
        res=0;
        i=_lig;
        j=_col;
    }

    // pour savoir si il y'a un puissance 4 diagonalement de haut droite à bas gauche.
    while ((Grille[i][j]==pion) && (res!=4))
    {
        j--;
        i++;
        res++;
    }
    if (res==4)
    {
        vainqueur=true;
    }
    else
    {
        res=0;
        i=_lig;
        j=_col;
    }

    // pour savoir si il y'a un puissance 4 diagonalement de bas gauche à haut droit.
    while ((Grille[i][j]==pion) && (res!=4))
    {
        j++;
        i--;
        res++;
    }
    if (res==4)
    {
        vainqueur=true;
    }
    else
    {
        res=0;
        i=_lig;
        j=_col;
    }

    // pour savoir si il y'a un puissance 4 diagonalement de haut gauche à bas droit.
    while ((Grille[i][j]==pion) && (res!=4))
    {
        j--;
        i--;
        res++;
    }
    if (res==4)
    {
        vainqueur=true;
    }
    else
    {
        res=0;
        i=_lig;
        j=_col;
    }

    return vainqueur;    
}