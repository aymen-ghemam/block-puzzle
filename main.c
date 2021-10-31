#include<stdio.h>
#include<stdlib.h>
#include<SDL/SDL.h>
#include<SDL_image.h>
#include <SDL_ttf.h>
#include "head.h"
#include "sdl_head.h"
#include <string.h>

int main(int argc, char *argv[])
{
    srand(time(0));
    SDL_Surface *ecran, *menu_principal=NULL, *intro, *name;
    SDL_Rect position, intro_pos;
    SDL_Event event;
    position.x=0; position.y=450;
    intro_pos.x=0;
    intro_pos.y=0;
    SDL_Init(SDL_INIT_VIDEO);
    ecran=SDL_SetVideoMode(450,450,32,SDL_HWSURFACE|SDL_RESIZABLE);
    SDL_WM_SetCaption("*** BLOCK PUZZLE ***",NULL);
    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,53,53,65));
    name=IMG_Load("enter.png");
    read_name(ecran, name);
    int c=1, con=1;
while(c){
    menu_principal=IMG_Load("menu.png");
    intro=IMG_Load("intro.png");
    int cont=1, i=1;
    position.y=450;
    SDL_PollEvent(&event);
    if(event.type==SDL_QUIT) c=0;
    while(i)
    {

        SDL_BlitSurface(menu_principal, NULL, ecran, &position);
        position.y--;
        if(position.y==0)
        {

            i=0;
        }
        SDL_Flip(ecran);
    }

    while(cont)
    {
        SDL_BlitSurface(menu_principal, NULL, ecran, &position);
        event.button.x=20;
        event.button.y=20;
        SDL_PollEvent(&event);
        SDL_Flip(ecran);
        switch(event.type)
        {
            case SDL_MOUSEBUTTONUP:
                if((event.button.x>40 && event.button.x<230)&&(event.button.y>200 && event.button.y<300))
                {

                    cont=part1(ecran);
                    //read_name(ecran, menu_principal);
                }
                else if((event.button.x>250 && event.button.x<440)&&(event.button.y>200 && event.button.y<300)) cont=part2(ecran);
                else if((event.button.x>385 && event.button.x<420)&&(event.button.y>20 && event.button.y<65)) i=1;
                {
                    intro_pos.x=450;
                    while(i)
                    {
                        SDL_PollEvent(&event);
                        if(event.type==SDL_MOUSEBUTTONUP && (event.button.x>202 && event.button.x<247)&&(event.button.y>393 && event.button.y<416)) i=0;
                        SDL_BlitSurface(intro, NULL, ecran, &intro_pos);
                        SDL_Flip(ecran);
                        if(intro_pos.x>0 )intro_pos.x--;
                    }
                }

                break;
            case SDL_QUIT:
                cont=0;
                c=0;
                break;
        }
        if(cont==0)
        {
            cont=0;
            c=0;
        }


    }
SDL_FreeSurface(menu_principal);
SDL_FreeSurface(intro);
}
    SDL_FreeSurface(ecran);
    SDL_Quit();
    return EXIT_SUCCESS;
}
