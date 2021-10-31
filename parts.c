#include<stdio.h>
#include<stdlib.h>
#include  <windows.h>
#include<SDL/SDL.h>
#include<SDL_image.h>
#include <SDL_ttf.h>
#include "head.h"
#include "sdl_head.h"

int part1(SDL_Surface *ecran)
{
    int **mapp=initmap();

    SDL_Surface *grille=NULL, *pause=NULL, *over;
    PIECE p1,p2,p3,mv_piece;
    SDL_Rect position, posp, over_pos ;
    SDL_Event event1;

    position.x=0;position.y=0;
    over_pos.x=50;
    over_pos.y=100;

    pause= IMG_Load("pause.png");
    grille = IMG_Load("grille.png");
    over = IMG_Load("over.png");
    p1=initpiece();
    p2=initpiece();
    p3=initpiece();

    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,255,255,255));
    int continuer=1, mv=0,scor=0, play=1;

    while(continuer)
    {
        while(continuer && play)
        {
            if(!valid_piece(mapp, p1.mat_piece) && !valid_piece(mapp, p2.mat_piece) && !valid_piece(mapp, p3.mat_piece))
                {
                    SDL_BlitSurface(over, NULL, ecran, &over_pos);
                    topscores(scor);
                    SDL_WaitEvent(&event1);
                    if(event1.type==SDL_QUIT) continuer=0;
                    play=0;
                }

            if(!mv && p1.mini_image==NULL) p1=initpiece();
            if(!mv && p2.mini_image==NULL) p2=initpiece();
            if(!mv && p3.mini_image==NULL) p3=initpiece();
            SDL_PollEvent(&event1);//fct tb9a tstena wsh ysra
            if(event1.type==SDL_QUIT) return 0;
            else if(event1.type==SDL_MOUSEBUTTONUP && event1.button.button==SDL_BUTTON_LEFT)
            {
                if(!mv && (event1.button.y>10 && event1.button.y<50) && (event1.button.x>320 && event1.button.x<430))
                {
                    play=0;
                }
                if(!mv && (event1.button.x<320 && event1.button.y>320))
                {
                    if(valid_piece(mapp, p1.mat_piece ) && (event1.button.x>10 && event1.button.x<110)&&(event1.button.y>320 && event1.button.y<420))
                    {
                        mv_piece=p1;
                        p1.mini_image=NULL;
                    }
                    else if(valid_piece(mapp, p2.mat_piece ) && (event1.button.x>115 && event1.button.x<215)&&(event1.button.y>320 && event1.button.y<420))
                    {
                        mv_piece=p2;
                        p2.mini_image=NULL;
                    }
                    else if(valid_piece(mapp, p3.mat_piece ) && (event1.button.x>220 && event1.button.x<320)&&(event1.button.y>320 && event1.button.y<420))
                    {
                        mv_piece=p3;
                        p3.mini_image =NULL;
                    }
                    posp.x=event1.button.x;
                    posp.y=event1.button.y;
                    mv=1;
                }

            }
            else if(event1.type==SDL_MOUSEBUTTONDOWN && event1.button.button==SDL_BUTTON_LEFT && mv)
                {
                    if((event1.button.x>5 && event1.button.x<305) && (event1.button.y>5 && event1.button.y<305) && comparer(mapp,mv_piece.mat_piece,trans_pos(event1.button.y),trans_pos(event1.button.x)))
                    {
                        posp.x=(event1.button.x)-(event1.button.x)%30 +6;
                        posp.y=(event1.button.y)-(event1.button.y)%30 +6;
                        SDL_BlitSurface(mv_piece.image,NULL,grille,&posp);
                        fusion(mapp,mv_piece.mat_piece ,trans_pos(event1.button.y),trans_pos(event1.button.x));
                        complet_lc(mapp);
                        scor+=add_score(mapp, mv_piece);
                        suppr_lc(mapp);
                    }
                    else
                    {
                        if(p1.mini_image==NULL) p1=mv_piece;
                        else if(p2.mini_image==NULL) p2=mv_piece;
                        else if(p3.mini_image==NULL) p3=mv_piece;
                    }
                    mv_piece.image=NULL;
                    mv=0;
                }

            if(mv && event1.type==SDL_MOUSEMOTION)
            {
                posp.x=event1.button.x;
                posp.y=event1.button.y;
            }

            if(p1.mini_image!=NULL) SDL_SetAlpha(p1.mini_image, SDL_SRCALPHA, 255);
            if(p1.mini_image!=NULL && !valid_piece(mapp, p1.mat_piece)) SDL_SetAlpha(p1.mini_image, SDL_SRCALPHA, 150);
            if(p2.mini_image!=NULL) SDL_SetAlpha(p2.mini_image, SDL_SRCALPHA, 255);
            if(p2.mini_image!=NULL && !valid_piece(mapp, p2.mat_piece)) SDL_SetAlpha(p2.mini_image, SDL_SRCALPHA, 150);
            if(p3.mini_image!=NULL) SDL_SetAlpha(p3.mini_image, SDL_SRCALPHA, 255);
            if(p3.mini_image!=NULL && !valid_piece(mapp, p3.mat_piece)) SDL_SetAlpha(p3.mini_image, SDL_SRCALPHA, 150);


            SDL_BlitSurface(grille,NULL,ecran,&position);
            afficher(mapp, grille);
            afficher_score(scor, ecran);
            haigh_score(ecran);
            afficher_pieces(ecran, p1, p2, p3);
            if(mv_piece.image!=NULL) SDL_BlitSurface(mv_piece.image,NULL,ecran,&posp);
            if(!valid_piece(mapp, p1.mat_piece) && !valid_piece(mapp, p2.mat_piece) && !valid_piece(mapp, p3.mat_piece))
                {
                    SDL_BlitSurface(over, NULL, ecran, &over_pos);
                    topscores(scor);
                    SDL_WaitEvent(&event1);
                    if(event1.type==SDL_QUIT) continuer=0;
                }




            SDL_Flip(ecran);//fct tb9a daymn trenouvli lecran
        }

        pause_game(scor, ecran);//fct t afficher limage tae pause w wsh fiha
        SDL_PollEvent(&event1);
        if(event1.type==SDL_MOUSEBUTTONUP && (event1.button.x>50 && event1.button.x<100)&&(event1.button.y>210 && event1.button.y<260))
        {
            play=1;
        }
        else if(event1.type==SDL_MOUSEBUTTONUP && (event1.button.x>150 && event1.button.x<200)&&(event1.button.y>210 && event1.button.y<260))
        {
            play=1;
            scor=0;
            mapp=initmap();
            p1=initpiece();
            p2=initpiece();
            p3=initpiece();
            topscores(scor);
        }
        else if(event1.type==SDL_MOUSEBUTTONUP && (event1.button.x>250 && event1.button.x<300)&&(event1.button.y>210 && event1.button.y<260))
        {
            savetofile(mapp);
        }
        else if(event1.type==SDL_MOUSEBUTTONUP && (event1.button.x>350 && event1.button.x<400)&&(event1.button.y>210 && event1.button.y<260))
        {
            topscores(scor);
            continuer=0;
        }
        else if(event1.type==SDL_QUIT) continuer=0;
        SDL_Flip(ecran);
    }
    SDL_FreeSurface(grille);
    free(mapp);

    return continuer;

}



int part2(SDL_Surface *ecran)
{
    int **mapp=initmap();
    SDL_Surface *pause=NULL, *grille=NULL, *over ;
    PIECE p1,p2,p3,mv_piece;
    SDL_Rect position,pos1, pos2, pos3, mv_pos, over_pos;//sdl rect huwa typee tae position fih x wy
    SDL_Event event1;
    over_pos.x=20;
    over_pos.y=100;
    position.x=0;position.y=0;
    pos1.x=10   ;pos1.y=320;
    pos2.x=165 ;pos2.y=320;
    pos3.x=320 ;pos3.y=320;
    grille = IMG_Load("grille.png");
    over= IMG_Load("over.png");
    p1=initpiece();
    p2=initpiece();
    p3=initpiece();

    //SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,255,255,255));
    int continuer=1,mv=0, scor=0, play=1;
    coord_score c;
    while(continuer)
    {
        while(continuer && play)
        {
            if(!valid_piece(mapp, p1.mat_piece) && !valid_piece(mapp, p2.mat_piece) && !valid_piece(mapp, p3.mat_piece))
                {
                    SDL_BlitSurface(over, NULL, ecran, &over_pos);
                }

            SDL_PollEvent(&event1);
            if(event1.type==SDL_QUIT) return 0;
            if(event1.type==SDL_MOUSEBUTTONUP && event1.button.button== SDL_BUTTON_LEFT)
            {
                if((event1.button.y>10 && event1.button.y<50) && (event1.button.x>320 && event1.button.x<430)) //cooro taepause
                play=0;
                topscores(scor);
            }

            if(c.x!=0 && c.y!=0 && c.score!=0 )
                {
                if(mv && mv_pos.x-6==(c.y*30 - 30 )  && mv_pos.y-6==(c.x*30 - 30))
                {
                    SDL_BlitSurface(mv_piece.image,NULL,grille,&mv_pos);
                    fusion(mapp,mv_piece.mat_piece,c.x,c.y);
                    complet_lc(mapp);
                    scor+=add_score(mapp, mv_piece);
                    suppr_lc(mapp);
                    mv_piece.image=NULL;
                    if(p1.mini_image==NULL)
                    {   p1=initpiece();
                    }
                    if(p2.mini_image==NULL)
                    {   p2=initpiece();
                    }
                    if(p3.mini_image==NULL)
                    {   p3=initpiece();
                    }
                    mv=0;
                    c.x=0;
                    c.y=0;
                }
                else if (mv)
                {
                    if(mv_pos.x-6>c.y*30 - 30) mv_pos.x-=2;
                    if(mv_pos.y-6>c.x*30 - 30) mv_pos.y-=2;
                    if(mv_pos.x-6<c.y*30 - 30) mv_pos.x++;
                    if(mv_pos.y-6<c.x*30 - 30) mv_pos.y++;
                }
            }

            if(!mv)
            {
                if(valid_piece(mapp,p1.mat_piece) && choose_piece(mapp, p1, p2, p3)==1)
                {
                    mv_piece=p1;
                    p1.mini_image=NULL;
                    c=piece_best_score(mapp,p1);
                    mv_pos.x=pos1.x;
                    mv_pos.y=pos1.y;
                    mv=1;
                }
                else if(valid_piece(mapp,p2.mat_piece ) && choose_piece(mapp, p1, p2, p3)==2)
                {
                    mv_piece=p2;
                    p2.mini_image=NULL;
                    c=piece_best_score(mapp,p2);
                    mv_pos.x=pos2.x;
                    mv_pos.y=pos2.y;
                    mv=1;
                }
                else if(valid_piece(mapp,p3.mat_piece ) && choose_piece(mapp, p1, p2, p3)==3)
                {
                    mv_piece=p3;
                    p3.mini_image=NULL;
                    c=piece_best_score(mapp,p3);
                    mv_pos.x=pos3.x;
                    mv_pos.y=pos3.y;
                    mv=1;
                }

            }

            if(p1.mini_image!=NULL) SDL_SetAlpha(p1.mini_image, SDL_SRCALPHA, 255);
            if(p1.mini_image!=NULL && !valid_piece(mapp, p1.mat_piece)) SDL_SetAlpha(p1.mini_image, SDL_SRCALPHA, 150);
            if(p2.mini_image!=NULL) SDL_SetAlpha(p2.mini_image, SDL_SRCALPHA, 255);
            if(p2.mini_image!=NULL && !valid_piece(mapp, p2.mat_piece)) SDL_SetAlpha(p2.mini_image, SDL_SRCALPHA, 150);
            if(p3.mini_image!=NULL) SDL_SetAlpha(p3.mini_image, SDL_SRCALPHA, 255);
            if(p3.mini_image!=NULL && !valid_piece(mapp, p3.mat_piece)) SDL_SetAlpha(p3.mini_image, SDL_SRCALPHA, 150);
            SDL_BlitSurface(grille,NULL,ecran,&position);
            afficher(mapp, grille);
            afficher_score(scor, ecran);
            haigh_score(ecran);
            afficher_pieces(ecran, p1, p2, p3);
            SDL_BlitSurface(mv_piece.image,NULL,ecran,&mv_pos);
            if(!valid_piece(mapp, p1.mat_piece) && !valid_piece(mapp, p2.mat_piece) && !valid_piece(mapp, p3.mat_piece))
                {
                    SDL_BlitSurface(over, NULL, ecran, &over_pos);
                }

            SDL_Flip(ecran);
        }

        pause_game2(scor, ecran);
        SDL_PollEvent(&event1);
        if(event1.type==SDL_MOUSEBUTTONUP && (event1.button.x>50 && event1.button.x<100)&&(event1.button.y>210 && event1.button.y<260))
        {
            play=1;

        }
        else if(event1.type==SDL_MOUSEBUTTONUP && (event1.button.x>150 && event1.button.x<200)&&(event1.button.y>210 && event1.button.y<260))
        {
            play=1;
            scor=0;
            mapp=initmap();
            p1=initpiece();
            p2=initpiece();
            p3=initpiece();
            mv_piece.image=NULL;
        }
        else if(event1.type==SDL_MOUSEBUTTONUP && (event1.button.x>250 && event1.button.x<300)&&(event1.button.y>210 && event1.button.y<260))
        {
            continuer=0;
        }
        else if(event1.type==SDL_QUIT) continuer=0;

        SDL_Flip(ecran);
    }
    SDL_FreeSurface(grille);
    return continuer;
}

