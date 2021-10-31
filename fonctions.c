#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "head.h"
#include <string.h>

void topscores(int score)
{
    FILE *file=fopen("top5.txt", "r");
    int top[5]={0};
    int i, x;
    fscanf(file, " %d %d %d %d %d",&top[0],&top[1],&top[2],&top[3],&top[4]);
    for(i=0; i<5; i++)
    {
    if(top[i] < score)
    {
        x=score;
        score=top[i];
        top[i]=x;
        x=0;
        }
    }
    file=fopen("top5.txt", "w+")  ;
    fprintf(file, " %d %d %d %d %d", top[0],top[1],top[2],top[3],top[4]);
    fclose(file);
}

int choose_piece(int ** mat, PIECE p1, PIECE p2, PIECE p3)
{
    int s1, s2, s3;
    coord_score c;
    c=piece_best_score(mat, p1);
    s1=c.score;
    c=piece_best_score(mat, p2);
    s2=c.score;
    c=piece_best_score(mat, p3);
    s3=c.score;
    if(s1 >= s2 && s1 >=s3) return 1;
    else if(s1 >= s2) return 3;
    else return 2;
}

coord_score piece_best_score(int **map, PIECE p)
{
    int **m;
    int i,j,valid=0;
    coord_score c;
    c.score=0;
    i=1;
    while(i<11 && !valid)
    {
        j=1;
        while(j<11 && !valid)
        {
            m=mat_mat(map);
            if(comparer(m,p.mat_piece,i,j))
            {
                valid=1;
                fusion(m,p.mat_piece,i,j);
                complet_lc(m);
                c.x=i;
                c.y=j;
                c.score=add_score(m, p);
            }
            j++;
        }
        i++;
    }
    for(i=1;i<11;i++)
    {
        for(j=1;j<11;j++)
        {
            m=mat_mat(map);
            if(comparer(m,p.mat_piece,i,j))
            {
                fusion(m,p.mat_piece,i,j);
                complet_lc(m);
                if(c.score<add_score(m,p))
                {
                    c.x=i;
                    c.y=j;
                    c.score=add_score(m,p);
                }
            }
        }
    }
    return c;
}

int **mat_mat(int **map)
{
    int **m=initmap();
    int i,j;
    for(i=0;i<12;i++)
    {
        for(j=0;j<12;j++)
        {
            m[i][j]=map[i][j];
        }
    }
    return m;
}


int **resume_mat(int **mapp)
{
    FILE *matrix=fopen("matrix.txt", "r");
    int i,j,x;
    for(i = 1; i < 11; i++)
    {
        for(j = 1; j < 11; j++)
        {
            x=fgetc(matrix);
            x-=48;
            mapp[i][j]=x;
        }

    }
    fclose(matrix);

return mapp;

}
void savetofile(int **mat)
{
    FILE *matrix=fopen("matrix.txt", "w+");
    int a, b;

    for(a=1;a<11;a++)
    {
        for(b=1;b<11;b++)
        {
            fprintf(matrix, "%d", mat[a][b]);
        }
    }

    fclose(matrix);
}

int piece_blocks(int **mat_piece)
{
    int i,j,s=0;
    for(i=0;i<5;i++)
    {
        for(j=0;j<5;j++)
        {
            if(mat_piece[i][j]!=0) s++;
        }
    }
    return s;
}
int add_score(int **mat, PIECE p)
{
    int i,l=0;
    for(i=0;i<11;i++)
    {
       if(mat[i][0]==-1) l++;
       if(mat[0][i+1]==-1) l++;
    }
    switch(l)
    {
        case 5: return 1500;
        break;
        case 4: return 1000;
        break;
        case 3: return 600;
        break;
        case 2: return 300;
        break;
        case 1: return 100;
        break;
    }
    return p.score * 10;
}

int piece_score(int **mat_piece)
{
    int i,j,s;
    for(i=0;i<5;i++)
    {
        for(j=0;j<5;j++)
        {
            if(mat_piece[i][j]!=0) s++;
        }
    }
    return s;
}
int line_score(int **mat, PIECE p)
{
    int i,s;
    for(i=0;i<11;i++)
    {
       if(mat[i][0]==-1) s++;
       if(mat[0][i+1]==-1) s++;
    }
    switch(s)
    {
        case 5: return 1500;
        case 4: return 1000;
        case 3: return 600;
        case 2: return 300;
        case 1: return 100;
    }
    return p.score*10;
}
void suppr_lc(int **mat)
{
    suppr_l(mat);
    suppr_c(mat);
}

void complet_lc(int **mat)
{
    complet_l(mat);
    complet_c(mat);
}
void complet_l(int **mat)
{
    int i=1,j,complet_L;
    while(i<11)
    {
        j=1;
        complet_L=1;
        while(j<11 && complet_L)
        {
            if(!mat[i][j]) complet_L=0;
            j++;
        }
        if(complet_L) mat[i][0]=-1;
        i++;
    }
}
void complet_c(int **mat)
{
    int i=1,j,complet;
    while(i<11)
    {
        j=1;
        complet=1;
        while(j<11 && complet)
        {
            if(!mat[j][i]) complet=0;
            j++;
        }
        if(complet) mat[0][i]=-1;
        i++;
    }
}

void suppr_l(int **mat)
{
    int i,j;
    for(i=0;i<11;i++)
    {
        if(mat[i][0]==-1)
        {
            mat[i][0]=9;
            for(j=1;j<11;j++)
            {
                mat[i][j]=0;
            }
        }
    }
}
void suppr_c(int **mat)
{
    int i,j;
    for(i=1;i<11;i++)
    {
        if(mat[0][i]==-1)
        {
            mat[0][i]=9;
            for(j=1;j<11;j++)
            {
                mat[j][i]=0;
            }
        }
    }
}


int valid_piece(int **map, int **piece)
{
    int i,j;
    for(i=1;i<11;i++)
    {
        for(j=1;j<11;j++)
        {
            if(comparer(map,piece,i,j)) return 1;
        }
    }
    return 0;
}

int trans_pos(int x)
{
    return (x/30)+1;
}
int random(){
    int x=rand();
    return x%27;
}

int comparer(int** m,int **n,int x,int y){
    int i=0,j;
    while(i<5 && i+x<13){
        j=0;
        while(j<5 && j+y<13){
            if((m[i+x][j+y]!=0) && (n[i][j]!=0)) return 0;
            j++;
        }
        i++;
    }
    return 1;
}
void fusion(int** m,int **n,int x,int y){
    int i=0,j;
    while(i<5 && i+x<11){
        j=0;
        while(j<5 && j+y<11){
            if(n[i][j]!=0) m[i+x][j+y]=1;
            j++;
        }
        i++;
    }
}

int **initmap(){
    int i,j;
    int **map=(int**)malloc(13*sizeof(int*));
    for(i=0;i<13;i++){
        map[i]=(int*)malloc(13*sizeof(int));
    }
    for(i=0;i<13;i++){
        map[i][11]=9;
        map[11][i]=9;
        map[12][i]=9;
        map[i][12]=9;
    }
    for(i=1;i<11;i++){
        for(j=1;j<11;j++){
            map[i][j]=0;
        }
    }
    return map;
}

int **mat_piece(int n){
    int shapes[27][5][5]={
      {
      {1,0,0,0,0},
      {0,0,0,0,0},
      {0,0,0,0,0},
      {0,0,0,0,0},
      {0,0,0,0,0}
      },
      {
      {2,2,0,0,0},
      {0,0,0,0,0},
      {0,0,0,0,0},
      {0,0,0,0,0},
      {0,0,0,0,0}
      },
      {
      {2,0,0,0,0},
      {2,0,0,0,0},
      {0,0,0,0,0},
      {0,0,0,0,0},
      {0,0,0,0,0}
      },
      {
      {3,3,3,0,0},
      {3,3,3,0,0},
      {3,3,3,0,0},
      {0,0,0,0,0},
      {0,0,0,0,0}
      },
      {
      {4,4,4,4,0},
      {0,0,0,0,0},
      {0,0,0,0,0},
      {0,0,0,0,0},
      {0,0,0,0,0}
      },
      {
      {4,0,0,0,0},
      {4,0,0,0,0},
      {4,0,0,0,0},
      {4,0,0,0,0},
      {0,0,0,0,0}
      },
      {
      {4,4,0,0,0},
      {4,4,0,0,0},
      {0,0,0,0,0},
      {0,0,0,0,0},
      {0,0,0,0,0}
      },
      {
      {0,4,0,0,0},
      {4,4,0,0,0},
      {0,4,0,0,0},
      {0,0,0,0,0},
      {0,0,0,0,0}
      },

       {
      {0,4,0,0,0},
      {4,4,4,0,0},
      {0,0,0,0,0},
      {0,0,0,0,0},
      {0,0,0,0,0}
      },
      {
      {4,0,0,0,0},
      {4,4,0,0,0},
      {4,0,0,0,0},
      {0,0,0,0,0},
      {0,0,0,0,0}
      },

       {
      {4,4,4,0,0},
      {0,4,0,0,0},
      {0,0,0,0,0},
      {0,0,0,0,0},
      {0,0,0,0,0}
      },
      {
      {5,5,5,0,0},
      {0,0,0,0,0},
      {0,0,0,0,0},
      {0,0,0,0,0},
      {0,0,0,0,0}
      },

       {
      {5,0,0,0,0},
      {5,0,0,0,0},
      {5,0,0,0,0},
      {0,0,0,0,0},
      {0,0,0,0,0}
      },
      {
      {5,5,0,0,0},
      {5,0,0,0,0},
      {0,0,0,0,0},
      {0,0,0,0,0},
      {0,0,0,0,0}
      },
      {
      {5,5,0,0,0},
      {0,5,0,0,0},
      {0,0,0,0,0},
      {0,0,0,0,0},
      {0,0,0,0,0}
      },
      {
      {5,0,0,0,0},
      {5,5,0,0,0},
      {0,0,0,0,0},
      {0,0,0,0,0},
      {0,0,0,0,0}
      },
      {
      {0,5,0,0,0},
      {5,5,0,0,0},
      {0,0,0,0,0},
      {0,0,0,0,0},
      {0,0,0,0,0}
      },
      {
      {6,6,6,6,6},
      {0,0,0,0,0},
      {0,0,0,0,0},
      {0,0,0,0,0},
      {0,0,0,0,0}
      },
      {
      {6,0,0,0,0},
      {6,0,0,0,0},
      {6,0,0,0,0},
      {6,0,0,0,0},
      {6,0,0,0,0}
      },
      {
      {6,6,6,0,0},
      {0,0,6,0,0},
      {0,0,6,0,0},
      {0,0,0,0,0},
      {0,0,0,0,0}
      },
      {
      {6,0,0,0,0},
      {6,0,0,0,0},
      {6,6,6,0,0},
      {0,0,0,0,0},
      {0,0,0,0,0}
      },
      {
      {6,6,6,0,0},
      {6,0,0,0,0},
      {6,0,0,0,0},
      {0,0,0,0,0},
      {0,0,0,0,0}
      },
      {
      {0,0,6,0,0},
      {0,0,6,0,0},
      {6,6,6,0,0},
      {0,0,0,0,0},
      {0,0,0,0,0}
      },
      {
      {6,6,0,0,0},
      {0,6,0,0,0},
      {6,6,0,0,0},
      {0,0,0,0,0},
      {0,0,0,0,0}
      },
      {
      {6,6,0,0,0},
      {6,0,0,0,0},
      {6,6,0,0,0},
      {0,0,0,0,0},
      {0,0,0,0,0}
      },
      {
      {6,6,6,0,0},
      {6,0,6,0,0},
      {0,0,0,0,0},
      {0,0,0,0,0},
      {0,0,0,0,0}
      },
      {
      {6,0,6,0,0},
      {6,6,6,0,0},
      {0,0,0,0,0},
      {0,0,0,0,0},
      {0,0,0,0,0}
      },
};
    int i,j;
    int **piece=(int**)malloc(5*sizeof(int*));
    for(i=0;i<5;i++){
        piece[i]=(int*)malloc(5*sizeof(int));
    }
    for(i=0;i<5;i++){
        for(j=0;j<5;j++){
            piece[i][j]=shapes[n][i][j];
        }
    }
    return piece;
}
