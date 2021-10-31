#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<SDL/SDL.h>
#include<SDL_image.h>
#include <SDL_ttf.h>
#include "head.h"
#include "sdl_head.h"

//void afficher_top_scores

void read_name(SDL_Surface *ecran, SDL_Surface *grille)
{
    SDL_Surface *texte=NULL;
    SDL_Event event;
    SDL_Rect position, pos;
    position.x=90;
    position.y=250;
    pos.x=0;
    pos.y=0;
    int i=0, cpt=1;
    TTF_Init();
    TTF_Font *police = TTF_OpenFont("arial.ttf", 40);
    SDL_Color couleur = {255, 255, 255};
    char *chaine=(char *)calloc(20, sizeof(char));
    SDL_BlitSurface(grille, NULL, ecran, &pos);
    SDL_Flip(ecran);
    while(i<10 && cpt)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_q) {
                    chaine[i] = 'A';
                    i++;
                }
                else if(event.key.keysym.sym == SDLK_w) {
                    chaine[i] = 'Z';
                    i++;
                }
                else if(event.key.keysym.sym == SDLK_e) {
                    chaine[i] = 'E';
                    i++;
                }
                else if(event.key.keysym.sym == SDLK_r) {
                    chaine[i] = 'R';
                    i++;
                }
                else if(event.key.keysym.sym == SDLK_t) {
                    chaine[i] = 'T';
                    i++;
                }
                else if(event.key.keysym.sym == SDLK_y) {
                    chaine[i] = 'Y';
                    i++;
                }
                else if(event.key.keysym.sym == SDLK_u) {
                    chaine[i] = 'U';
                    i++;
                }
                else if(event.key.keysym.sym == SDLK_i) {
                    chaine[i] = 'I';
                    i++;
                }
                else if(event.key.keysym.sym == SDLK_o) {
                    chaine[i] = 'O';
                    i++;
                }
                else if(event.key.keysym.sym == SDLK_p) {
                    chaine[i] = 'P';
                    i++;
                }
                else if(event.key.keysym.sym == SDLK_a) {
                    chaine[i] = 'Q';
                    i++;
                }
                else if(event.key.keysym.sym == SDLK_s) {
                    chaine[i] = 'S';
                    i++;
                }
                else if(event.key.keysym.sym == SDLK_d) {
                    chaine[i] = 'D';
                    i++;
                }
                else if(event.key.keysym.sym == SDLK_f) {
                    chaine[i] = 'F';
                    i++;
                }
                else if(event.key.keysym.sym == SDLK_g) {
                    chaine[i] = 'G';
                    i++;
                }
                else if(event.key.keysym.sym == SDLK_h) {
                    chaine[i] = 'H';
                    i++;
                }
                else if(event.key.keysym.sym == SDLK_j) {
                    chaine[i] = 'J';
                    i++;
                }
                else if(event.key.keysym.sym == SDLK_k) {
                    chaine[i] = 'K';
                    i++;
                }
                else if(event.key.keysym.sym == SDLK_l) {
                    chaine[i] = 'L';
                    i++;
                }
                else if(event.key.keysym.sym == SDLK_SEMICOLON) {
                    chaine[i] = 'M';
                    i++;
                }
                else if(event.key.keysym.sym == SDLK_z) {
                    chaine[i] = 'W';
                    i++;
                }
                else if(event.key.keysym.sym == SDLK_x) {
                    chaine[i] = 'X';
                    i++;
                }
                else if(event.key.keysym.sym == SDLK_c) {
                    chaine[i] = 'C';
                    i++;
                }
                else if(event.key.keysym.sym == SDLK_v) {
                    chaine[i] = 'V';
                    i++;
                }
                else if(event.key.keysym.sym == SDLK_b) {
                    chaine[i] = 'B';
                    i++;
                }
                else if(event.key.keysym.sym == SDLK_n) {
                    chaine[i] = 'N';
                    i++;
                }
                else if(event.key.keysym.sym == 13 ) i=10;

                texte = TTF_RenderText_Blended(police, chaine,couleur);
                SDL_BlitSurface(grille, NULL, ecran, &pos);
                SDL_BlitSurface(texte, NULL, ecran, &position);
                SDL_Flip(ecran);
                break;
            }

    }
    FILE *file=fopen("playername.txt", "w+");
    fprintf(file, chaine);
    fclose(file);

}

void haigh_score(SDL_Surface *grille)
{
    FILE *file=fopen("top5.txt", "r");
    int score;
    fscanf(file, " %d", &score);
    fclose(file);
    TTF_Init();
    TTF_Font *police = TTF_OpenFont("arial.ttf", 30);
    SDL_Color couleur = {255, 255, 255};
    SDL_Surface *texte;
    SDL_Rect position;
    position.x=325;
    position.y=150;
    char array[10];
    sprintf(array , "%d" , score);
    texte = TTF_RenderText_Blended(police, array,couleur);
    SDL_BlitSurface(texte, NULL, grille, &position);
    SDL_FreeSurface(texte);
    TTF_CloseFont(police);
    TTF_Quit();
}

void afficher_score(int score, SDL_Surface *grille)
{   TTF_Init();
    TTF_Font *police = TTF_OpenFont("arial.ttf", 30);
    SDL_Color couleur = {255, 255, 255};
    SDL_Surface *texte;
    SDL_Rect position;
    position.x=325;
    position.y=260;
    char array[20];
    sprintf(array , "%d" , score);
    texte = TTF_RenderText_Blended(police, array,couleur);
    SDL_BlitSurface(texte, NULL, grille, &position);
    SDL_FreeSurface(texte);
    TTF_CloseFont(police);
    TTF_Quit();
}

void pause_game(int score, SDL_Surface *grille)
{
    FILE *file=fopen("top5.txt", "r");
    int h_score;
    fscanf(file, " %d", &h_score);
    fclose(file);

    TTF_Init();
    TTF_Font *police = TTF_OpenFont("arial.ttf", 25);
    SDL_Color couleur = {255, 255, 255};
    SDL_Surface *texte, *texte1, *pause;
    SDL_Rect position,position1, pos;
    position.x=20;
    position.y=140;
    position1.x=240;
    position1.y=140;
    pos.x=0; pos.y=0;
    pause=IMG_Load("pause.png");
    char array[20];
    sprintf(array , "SCORE: %d" , score);
    texte = TTF_RenderText_Blended(police, array,couleur);

    char array1[20];
    sprintf(array1 , "SCORE: %d" , h_score);
    texte1 = TTF_RenderText_Blended(police, array1,couleur);

    SDL_BlitSurface(pause, NULL, grille, &pos);
    SDL_BlitSurface(texte, NULL, grille, &position);
    SDL_BlitSurface(texte1, NULL, grille, &position1);
    TTF_CloseFont(police);
    SDL_FreeSurface(texte);
    SDL_FreeSurface(texte1);
    SDL_FreeSurface(pause);

    TTF_Quit();
}

void pause_game2(int score, SDL_Surface *grille)
{
    FILE *file=fopen("top5.txt", "r");
    int h_score;
    fscanf(file, " %d", &h_score);
    fclose(file);

    TTF_Init();
    TTF_Font *police = TTF_OpenFont("arial.ttf", 25);
    SDL_Color couleur = {255, 255, 255};
    SDL_Surface *texte, *texte1, *pause;
    SDL_Rect position,position1, pos;
    position.x=20;
    position.y=140;
    position1.x=240;
    position1.y=140;
    pos.x=0; pos.y=0;
    pause=IMG_Load("pause2.png");
    char array[20];
    sprintf(array , "SCORE: %d" , score);
    texte = TTF_RenderText_Blended(police, array,couleur);

    char array1[20];
    sprintf(array1 , "SCORE: %d" , h_score);
    texte1 = TTF_RenderText_Blended(police, array1,couleur);

    SDL_BlitSurface(pause, NULL, grille, &pos);
    SDL_BlitSurface(texte, NULL, grille, &position);
    SDL_BlitSurface(texte1, NULL, grille, &position1);
    TTF_CloseFont(police);
    SDL_FreeSurface(texte);
    SDL_FreeSurface(texte1);
    SDL_FreeSurface(pause);
    TTF_Quit();
}

void afficher_pieces(SDL_Surface *ecran, PIECE p1, PIECE p2, PIECE p3)
{
    SDL_Rect pos1, pos2, pos3;
    pos1.x=10  ;pos1.y=320;
    pos2.x=115;pos2.y=320;
    pos3.x=220 ;pos3.y=320;
    if(p1.mini_image!=NULL) SDL_BlitSurface(p1.mini_image,NULL,ecran,&pos1);
    if(p2.mini_image!=NULL) SDL_BlitSurface(p2.mini_image,NULL,ecran,&pos2);
    if(p3.mini_image!=NULL) SDL_BlitSurface(p3.mini_image,NULL,ecran,&pos3);
}

void resume_afficher(int **mapp, SDL_Surface *grille)
{
    SDL_Surface *vide=NULL, *block=NULL;
    SDL_Rect ppc;
    vide=IMG_Load("vide.png");
    block=IMG_Load("pieces/0.png");
    int i,j;
    ppc.y=6;
    for(i=1;i<11;i++)
    {
        ppc.x=6;
        for(j=1;j<11;j++)
        {
            if(mapp[i][j]==0) SDL_BlitSurface(vide,NULL,grille,&ppc);
            else SDL_BlitSurface(block,NULL,grille,&ppc);

            ppc.x+=30;
        }
        ppc.y+=30;
    }
    SDL_FreeSurface(vide);
    SDL_FreeSurface(block);
}
void afficher(int **mapp, SDL_Surface *grille)
{
    SDL_Surface *vide=NULL;
    SDL_Rect ppc;
    vide=IMG_Load("vide.png");
    int i,j;
    ppc.y=6;
    for(i=1;i<11;i++)
    {
        ppc.x=6;
        for(j=1;j<11;j++)
        {
            if(mapp[i][j]==0) SDL_BlitSurface(vide,NULL,grille,&ppc);
            ppc.x+=30;
        }
        ppc.y+=30;
    }
    SDL_FreeSurface(vide);
}

PIECE initpiece()
{
    int n=random();
    PIECE p;
    p.image=shape(n);
    p.mini_image=mini_image(n);
    p.mat_piece=mat_piece(n);
    p.score=piece_blocks(p.mat_piece);
    return p;
}
SDL_Surface *shape(int n)
{
    SDL_Surface *images[27]={NULL};
    int i;
    char array[27];
    for (i=0;i<27;i++)
    {
        sprintf(array,"pieces/%d.png",i);
        images[i]=IMG_Load(array);
        SDL_SetColorKey(images[i], SDL_SRCCOLORKEY, SDL_MapRGB(images[i]->format, 255,255, 255));
    }
    return images[n];
    SDL_FreeSurface(images);
}

SDL_Surface *mini_image(int n)
{
    SDL_Surface *image[27]={NULL};
    int i;
    char array[27];
    for (i=0;i<27;i++)
    {
        sprintf(array,"mini_pieces/%d.png",i);
        image[i]=IMG_Load(array);
        SDL_SetColorKey(image[i], SDL_SRCCOLORKEY, SDL_MapRGB(image[i]->format, 255,255, 255));
    }
    return image[n];
    SDL_FreeSurface(image);
}

SDL_Surface *upload_colors(SDL_Surface *pc[6])
{
    pc[0] = IMG_Load("0.png");
    pc[1] = IMG_Load("red.png");
    pc[2] = IMG_Load("rose.png");
    pc[3] = IMG_Load("green.png");
    pc[4] = IMG_Load("yellow.png");
    pc[5] = IMG_Load("orange.png");
    return *pc;
}
