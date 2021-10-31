#ifndef HEAD_H_INCLUDED
#define HEAD_H_INCLUDED
#include<SDL/SDL.h>
#include "sdl_head.h"
typedef struct
{
    int x;
    int y;
    int score;
}coord_score;

int part1(SDL_Surface *ecran); //partie 1
int part2(SDL_Surface *ecran); //partie 2

int choose_piece(int ** mat, PIECE p1, PIECE p2, PIECE p3);
coord_score piece_best_score(int **map, PIECE p); // tchouf le meilleur postition li tzid score (te3 2eme partie)
int **mat_mat(int **map); // matrice = matrice
void savetofile(int **mat); // tsauvgarder la grille f une fichie
int piece_blocks(int **mat_piece); // ta7seb les blocks ta3 une piece
int add_score(int **mat, PIECE p); // ta7seb score
void suppr_lc(int **mat); // tsepprimer les lignes/colonnes
void complet_lc(int **mat); //tvirifie les lignes/colonnes completes
void suppr_l(int **mat);
void suppr_c(int **mat);
void complet_l(int **mat);
void complet_c(int **mat);
int valid_piece(int **map, int **piece); //bayna
int trans_pos(int x); // tbadal men pixel vers index te3 la grille
int comparer(int**,int **,int ,int ); // tvirifie ida na9drou n7atto la piece
void fusion(int**,int **,int ,int ); // fusionner une piece f une position
int **initmap(); // initialisation la grille
int **mat_piece(int); // initialisation la matrice de piece
int random();

#endif // HEAD_H_INCLUDED
