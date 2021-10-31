#ifndef SDL_HEAD_H_INCLUDED
#define SDL_HEAD_H_INCLUDED

typedef struct
{
    SDL_Surface *image;
    SDL_Surface *mini_image;
    int **mat_piece;
    int score;
}PIECE;


void pause_game(int score, SDL_Surface *grille); // l'affichage te3 pause
void resume_afficher(int **mapp, SDL_Surface *grille); // tafficher la grille li 7fadnaha fel fichie
void afficher_pieces(SDL_Surface *ecran, PIECE p1, PIECE p2, PIECE p3); // affichage te3 les 3 pieces
void afficher_score(int score, SDL_Surface *grille); // l'affichage te3 score
void haigh_score(SDL_Surface *grille) ;// l'affichage te3 le meilleur score
void afficher(int **mapp, SDL_Surface *grille); // l'affichage te3 la grille
SDL_Surface *mini_image(int n); // tretouner le mini_image te3 une piece
SDL_Surface *shape(int n_piece); // tretouner l'image te3 une piece
PIECE initpiece(); // initialisation te3 la piece


#endif // SDL_HEAD_H_INCLUDED
