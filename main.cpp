//
//  main.c
//  Sokoban
//
//  Created by Mariusz Laska on 09.01.2018.
//  Copyright © 2018 Mariusz Laska. All rights reserved.
//

//#include <SDL2/SDL.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

extern "C" {
#include"./sdl-2.0.7/include/SDL.h"
#include"./sdl-2.0.7/include/SDL_main.h"
}

//definicje pól
#define empty 0
#define goal 1
#define wall 2

//Klawisze
#define up 0
#define down 1
#define right 2
#define left 3


using namespace std;



struct board{
    int type;
    bool occu_player;
    bool occu_crate;
};

struct size_of_board{
    int x;
    int y;
};

struct player_position{
    int x;
    int y;
};
void DrawString(SDL_Surface *screen, int x, int y, const char *text,
                SDL_Surface *charset) {
    int px, py, c;
    SDL_Rect s, d;
    s.w = 8;
    s.h = 8;
    d.w = 8;
    d.h = 8;
    while(*text) {
        c = *text & 255;
        px = (c % 16) * 8;
        py = (c / 16) * 8;
        s.x = px;
        s.y = py;
        d.x = x;
        d.y = y;
        SDL_BlitSurface(charset, &s, screen, &d);
        x += 8;
        text++;
    }
}



int add_board(SDL_Surface *charset){
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow( "Mgr.Piotrek", 100, 100, 400, 100, NULL );
    SDL_Surface *backgroundSurf;
    //charset = SDL_LoadBMP("cs8x8.bmp");
    backgroundSurf=SDL_GetWindowSurface(window);
    SDL_UpdateWindowSurface(window);
    char text[128];
    
    sprintf(text,"wpisz nazwe pliku do swojej planszy ");
    DrawString(backgroundSurf, 0, 0, text, charset);
    SDL_UpdateWindowSurface(window);
    bool loop=true;
    int a=0;
    char tab[128];
    
    SDL_Event event;
    
    while(loop){
        while ( SDL_PollEvent( &event ) )
        {
            
            if ( event.type == SDL_QUIT ){
                loop = false;
                
            }
            else if ( event.type == SDL_KEYDOWN )
            {
                switch ( event.key.keysym.sym )
                {
                    case SDLK_ESCAPE:
                        return -1;
                        break;
                    case SDLK_RETURN:
                        loop=0;
                        break;
                        
                    case SDLK_a:
                        tab[a]='a';
                        a++;
                        break;
                    case SDLK_b:
                        tab[a]='b';
                        a++;
                        break;
                    case SDLK_c:
                        tab[a]='c';
                        a++;
                        break;
                    case SDLK_d:
                        tab[a]='d';
                        a++;
                        break;
                    case SDLK_e:
                        tab[a]='e';
                        a++;
                        break;
                    case SDLK_f:
                        tab[a]='f';
                        a++;
                        break;
                    case SDLK_g:
                        tab[a]='g';
                        a++;
                        break;
                    case SDLK_h:
                        tab[a]='h';
                        a++;
                        break;
                    case SDLK_i:
                        tab[a]='i';
                        a++;
                        break;
                    case SDLK_j:
                        tab[a]='j';
                        a++;
                        break;
                    case SDLK_k:
                        tab[a]='k';
                        a++;
                        break;
                    case SDLK_l:
                        tab[a]='l';
                        a++;
                        break;
                    case SDLK_m:
                        tab[a]='m';
                        a++;
                        break;
                    case SDLK_n:
                        tab[a]='n';
                        a++;
                        break;
                    case SDLK_o:
                        tab[a]='o';
                        a++;
                        break;
                    case SDLK_p:
                        tab[a]='p';
                        a++;
                        break;
                    case SDLK_q:
                        tab[a]='q';
                        a++;
                        break;
                    case SDLK_r:
                        tab[a]='r';
                        a++;
                        break;
                    case SDLK_s:
                        tab[a]='s';
                        a++;
                        break;
                    case SDLK_t:
                        tab[a]='t';
                        a++;
                        break;
                    case SDLK_u:
                        tab[a]='u';
                        a++;
                        break;
                    case SDLK_v:
                        tab[a]='v';
                        a++;
                        break;
                    case SDLK_w:
                        tab[a]='w';
                        a++;
                        break;
                    case SDLK_x:
                        tab[a]='x';
                        a++;
                        break;
                    case SDLK_y:
                        tab[a]='y';
                        a++;
                        break;
                    case SDLK_z:
                        tab[a]='z';
                        a++;
                        break;
                    case SDLK_PERIOD:
                        tab[a]='.';
                        a++;
                        break;
                    case SDLK_BACKSPACE:
                        a--;
                        tab[a]=' ';
                        break;
                    default :
                        break;
                }
                tab[a]='\0';
                sprintf(text,tab);
                DrawString(backgroundSurf, 0, 20, text, charset);
                SDL_UpdateWindowSurface(window);
            }
            
        }
        
    }
    FILE *file;
    file=fopen("levels.txt", "a");
    fprintf (file, tab);
    fprintf (file, "\n");
    fclose (file);
    SDL_DestroyWindow(window);
    return -1;
    
}




size_of_board get_size_of_board(char file[]){
    int x=0,y=1;
    char sign;
    
    FILE *plik;
    plik=fopen(file, "r");
    while(!feof(plik))
    {
        sign = fgetc(plik);
        if(sign == '\n')
        {
            y++;
        }
        else{
            if(sign == '0' || sign == '1' || sign=='2'|| sign == '3' || sign=='4' || sign=='5' || sign=='6' || sign=='7')
                x++;
        }
    }
    x=x/y;
    size_of_board size;
    size.x=x;
    size.y=y;
    
    return size;
    
}

board **get_board(int x, int y, char file[]){
    char sign;
    FILE* plik;
    
    board **tab=(board **)malloc(y * sizeof(board*));
    
    for(int i=0; i<y; i++){
        tab[i]=(board *)malloc(x * sizeof(board));
    }
    
    plik=fopen(file, "r");
    for(int i=0; i<y; i++){
        for(int j=0; j<x; j++){
            while(!feof(plik)){
                sign=fgetc(plik);
                
                if(sign=='0'){
                    tab[i][j].type=empty;
                    tab[i][j].occu_player=false;
                    tab[i][j].occu_crate=false;
                    break;
                }
                
                if(sign=='1'){
                    tab[i][j].type=empty;
                    tab[i][j].occu_player=false;
                    tab[i][j].occu_crate=true;
                    break;
                }
                
                if(sign=='2'){
                    tab[i][j].type=empty;
                    tab[i][j].occu_player=true;
                    tab[i][j].occu_crate=false;
                    break;
                }
                
                if(sign=='3'){
                    tab[i][j].type=goal;
                    tab[i][j].occu_player=false;
                    tab[i][j].occu_crate=false;
                    break;
                }
                
                if(sign=='4'){
                    tab[i][j].type=goal;
                    tab[i][j].occu_player=false;
                    tab[i][j].occu_crate=true;
                    break;
                }
                
                if(sign=='6'){
                    tab[i][j].type=goal;
                    tab[i][j].occu_player=true;
                    tab[i][j].occu_crate=false;
                    break;
                }
                
                if(sign=='7'){
                    tab[i][j].type=wall;
                    tab[i][j].occu_player=false;
                    tab[i][j].occu_crate=false;
                    break;
                }
                
            }
        }
    }
    
    return tab ;
}


SDL_Window *make_window(int x, int y){
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow( "Mgr.Piotrek", 100, 100, x*50, (y*50)+25, NULL );
    return window;
}


void get_surfaces(SDL_Surface **backgroundSurf, SDL_Surface **wallSurf, SDL_Surface **playerSurf, SDL_Surface **player_moveSurf, SDL_Surface **goalSurf,SDL_Surface **emptySurf, SDL_Surface **goal_crateSurf, SDL_Surface **crateSurf, SDL_Surface **charset){
    
    *playerSurf = SDL_LoadBMP("player.bmp");
    *player_moveSurf = SDL_LoadBMP("moving_player.bmp");
    *emptySurf = SDL_LoadBMP("plain.bmp");
    *wallSurf = SDL_LoadBMP("wall.bmp");
    *goalSurf = SDL_LoadBMP("goal.bmp");
    *crateSurf = SDL_LoadBMP("crate.bmp");
    *goal_crateSurf = SDL_LoadBMP("crate_goal.bmp");
    *charset = SDL_LoadBMP("cs8x8.bmp");
}

void draw_board(SDL_Surface *backgroundSurf, SDL_Surface *wallSurf, SDL_Surface *playerSurf, SDL_Surface *goalSurf,SDL_Surface *emptySurf, SDL_Surface *goal_crateSurf, SDL_Surface *crateSurf, SDL_Window *window, board **board, int x, int y){
    
    SDL_Rect box;
    box.w=50;
    box.h=50;
    
    
    for(int i=0; i<y; i++){
        for(int j=0; j<x; j++){
            box.y=(i*50)+25;
            box.x=j*50;
            
            if(board[i][j].type==empty){
                if(board[i][j].occu_player==true){SDL_BlitSurface( playerSurf, NULL, backgroundSurf, &box );}
                if(board[i][j].occu_crate==true){SDL_BlitSurface( crateSurf, NULL, backgroundSurf, &box );}
                if(board[i][j].occu_player==false && board[i][j].occu_crate==false){
                    SDL_BlitSurface( emptySurf, NULL, backgroundSurf, &box );
                }
            }
            
            if(board[i][j].type==goal){
                if(board[i][j].occu_crate==true){SDL_BlitSurface( goal_crateSurf, NULL, backgroundSurf, &box );}
                if(board[i][j].occu_player==true){SDL_BlitSurface( playerSurf, NULL, backgroundSurf, &box );}
                if(board[i][j].occu_player==false && board[i][j].occu_crate==false){
                    SDL_BlitSurface( goalSurf, NULL, backgroundSurf, &box );
                }
            }
            
            if(board[i][j].type==wall){SDL_BlitSurface( wallSurf, NULL, backgroundSurf, &box );}
            
        }
    }
    SDL_UpdateWindowSurface(window);
    
}

bool done(board **board, size_of_board size){
    for(int i=0; i<size.y; i++){
        for(int j=0; j<size.x; j++){
            if(board[i][j].type==goal&&board[i][j].occu_crate==false)
                return false;
        }
    }
    return true;
}
player_position get_player_position(board **board, int x, int y){
    player_position player;
    for(int i=0; i<y; i++){
        for(int j=0; j<x; j++){
            if(board[i][j].occu_player==true){
                player.x=j;
                player.y=i;
                return player;
            }
        }
    }
    return player;
}

void move(board **board, int x, int y, int d){
    if(d==up){
        if(board[y-1][x].type==empty || board[y-1][x].type==goal){
            if(board[y-1][x].occu_crate==false){
                board[y-1][x].occu_player=true;
                board[y][x].occu_player=false;
                return;
            }
            else{
                if(board[y-2][x].occu_crate==false&&board[y-2][x].type!=wall){
                    board[y-2][x].occu_crate=true;
                    board[y-1][x].occu_crate=false;
                    board[y-1][x].occu_player=true;
                    board[y][x].occu_player=false;
                    return;
                }
                else{return;}
            }
        }
        else{return;}
    }
    
    if(d==down){
        if(board[y+1][x].type==empty || board[y+1][x].type==goal){
            if(board[y+1][x].occu_crate==false){
                board[y+1][x].occu_player=true;
                board[y][x].occu_player=false;
                return;
            }
            else{
                if(board[y+2][x].occu_crate==false&&board[y+2][x].type!=wall){
                    board[y+2][x].occu_crate=true;
                    board[y+1][x].occu_crate=false;
                    board[y+1][x].occu_player=true;
                    board[y][x].occu_player=false;
                    return;
                }
                else{return;}
            }
        }
        else{return;}
    }
    
    if(d==right){
        if(board[y][x+1].type==empty || board[y][x+1].type==goal){
            if(board[y][x+1].occu_crate==false){
                board[y][x+1].occu_player=true;
                board[y][x].occu_player=false;
                return;
            }
            else{
                if(board[y][x+2].occu_crate==false&&board[y][x+2].type!=wall){
                    board[y][x+2].occu_crate=true;
                    board[y][x+1].occu_crate=false;
                    board[y][x+1].occu_player=true;
                    board[y][x].occu_player=false;
                    return;
                }
                else{return;}
            }
        }
        else{return;}
    }
    
    if(d==left){
        if(board[y][x-1].type==empty || board[y][x-1].type==goal){
            if(board[y][x-1].occu_crate==false){
                board[y][x-1].occu_player=true;
                board[y][x].occu_player=false;
                return;
            }
            else{
                if(board[y][x-2].occu_crate==false&&board[y][x-2].type!=wall){
                    board[y][x-2].occu_crate=true;
                    board[y][x-1].occu_crate=false;
                    board[y][x-1].occu_player=true;
                    board[y][x].occu_player=false;
                    return;
                }
                else{return;}
            }
        }
        else{return;}
    }
}

int RunGame(SDL_Surface *charset, SDL_Surface *backgroundSurf, SDL_Surface *wallSurf, SDL_Surface *playerSurf, SDL_Surface *player_moveSurf, SDL_Surface *goalSurf,SDL_Surface *emptySurf, SDL_Surface *goal_crateSurf, SDL_Surface *crateSurf, SDL_Window *window, board **board, size_of_board size_of_board,  char *text){
    bool loop = true;
    SDL_Event event;
    int moves_quantity=0;
    int t3=SDL_GetTicks();
    int t2=0;
    int t1=0;
    while(loop){
        while ( SDL_PollEvent( &event ) )
        {
             player_position player=get_player_position(board, size_of_board.x, size_of_board.y);
            if ( event.type == SDL_QUIT ){
                loop = false;
                
            }
            else if ( event.type == SDL_KEYDOWN )
            {
                switch ( event.key.keysym.sym )
                {
                    case SDLK_RIGHT:
                        move(board, player.x, player.y, right);
                        moves_quantity++;
                        t1=SDL_GetTicks()-t3;
                        break;
                    case SDLK_LEFT:
                        move(board, player.x, player.y, left);
                        moves_quantity++;
                        t1=SDL_GetTicks()-t3;
                        break;
                    case SDLK_DOWN:
                        move(board, player.x, player.y, down);
                        moves_quantity++;
                        t1=SDL_GetTicks()-t3;
                        break;
                    case SDLK_UP:
                       move(board, player.x, player.y, up);
                        moves_quantity++;
                        t1=SDL_GetTicks()-t3;
                        break;
                    case SDLK_n:
                        return 0;
                        break;
                    case SDLK_ESCAPE:
                        return 1;
                        break;
                    default :
                        break;
                }
            }
        }
      
        t2=SDL_GetTicks()-t3;
        
        
        if(t2-t1<200){
            draw_board(backgroundSurf, wallSurf, player_moveSurf, goalSurf, emptySurf, goal_crateSurf,  crateSurf, window, board, size_of_board.x, size_of_board.y);
        }
        else{
            draw_board(backgroundSurf, wallSurf, playerSurf, goalSurf, emptySurf, goal_crateSurf,  crateSurf, window, board, size_of_board.x, size_of_board.y);
        }
        char test[500]; test[0]='a'; test[1]='b'; test[2]='c';  test[3]='\0';
        sprintf(text,"czas: %ds   liczba ruchow:%d", t2/1000, moves_quantity);
        DrawString(backgroundSurf, 0, 10, text, charset);
        if(done(board, size_of_board)){
            sprintf(text,"WYGRALES!!!!                  ");
            DrawString(backgroundSurf, 0, 10, text, charset);
            SDL_UpdateWindowSurface(window);
            SDL_Delay(2000);
            return 5;}
    }
    
    return 5;
}

int menu(SDL_Surface *charset){
    SDL_Window *window = SDL_CreateWindow( "Mgr.Piotrek", 100, 100, 800, 800, NULL );
    SDL_Surface *backgroundSurf, *arrow, *black;
    arrow=SDL_LoadBMP("arrow.bmp");
    black=SDL_LoadBMP("black.bmp");
    backgroundSurf=SDL_GetWindowSurface(window);
    SDL_UpdateWindowSurface(window);
    char text[128];
    char tab[10000];
    FILE *file;
    file=fopen("levels.txt", "r");
    int a=100;
    int records=0;
    while(!feof(file)){
        fgets(tab, 10000 ,file);
        if(tab[0]!=' '){
            records++;
            sprintf(text,tab);
            DrawString(backgroundSurf, 35, a, text, charset);
            SDL_UpdateWindowSurface(window);
            a+=20;
            tab[0]=' ';
        }
    }

    sprintf(text,"MAGAZYNIER PIOTREK ");
    DrawString(backgroundSurf, 375, 0, text, charset);
    sprintf(text,"DODAJ NOWY POZIOM - wcisnij n ");
    DrawString(backgroundSurf, 10, 30, text, charset);
    sprintf(text,"DOSTEPNE POZIOMY ");
    DrawString(backgroundSurf, 20, 75, text, charset);
    SDL_UpdateWindowSurface(window);
    
    
    SDL_Rect box;
    box.x=10; box.y=90; box.w=20; box.h=20;
    SDL_BlitSurface( arrow, NULL, backgroundSurf, &box );
    SDL_UpdateWindowSurface(window);
    
    SDL_Event event;
    bool loop = true;
    while(loop){
        while ( SDL_PollEvent( &event ) )
        {
            if ( event.type == SDL_QUIT ){
                return -5;
                
            }
            else if ( event.type == SDL_KEYDOWN )
            {
                switch ( event.key.keysym.sym )
                {
                    case SDLK_ESCAPE:
                        return -5;
                        break;
                    case SDLK_RETURN:
                        loop=0;
                        break;
                    case SDLK_DOWN:
                        if(box.y<70+(records*20)){
                        box.y+=20;
                        }
                        break;
                    case SDLK_UP:
                        if(box.y>90){
                            box.y-=20;
                        }
                        break;
                    case SDLK_n:
                        return -2;
                        break;
                    default :
                        break;
                }
            }
        }
        box.y+=20;
        SDL_BlitSurface( black, NULL, backgroundSurf, &box );
        box.y-=40;
        SDL_BlitSurface( black, NULL, backgroundSurf, &box );
        box.y+=20;
        
        SDL_BlitSurface( arrow, NULL, backgroundSurf, &box );
        SDL_UpdateWindowSurface(window);
    }
    SDL_DestroyWindow(window);
    return (box.y-80)/20;

}

    
int main(int argc, const char * argv[]) {
    
//    SDL_Window *window = make_window(size_of_board.x, size_of_board.y);
    SDL_Surface *backgroundSurf;
    SDL_Surface *wallSurf;
    SDL_Surface *playerSurf;
    SDL_Surface *player_moveSurf;
    SDL_Surface *goalSurf;
    SDL_Surface *crateSurf;
    SDL_Surface *goal_crateSurf;
    SDL_Surface *emptySurf;
    SDL_Surface *charset;
    
    get_surfaces(&backgroundSurf, &wallSurf, &playerSurf , &player_moveSurf, &goalSurf, &emptySurf, &goal_crateSurf, &crateSurf, &charset);
    char text[128];
    
    int controller=-1;
    
    while(1){
    
        if(controller==-1){
            controller=menu(charset);
        }
        if(controller==-2){
            controller=add_board(charset);
        }
        if(controller>=0){
    
            FILE *file;
            file=fopen("levels.txt", "r");
            char tab[10000];
            for(int i=0; i<=controller; i++){
                fgets(tab, 10000 ,file);
            }
            int i=0;
            while(1){
                if(tab[i]=='\n'){tab[i]='\0';break;}
                i++;
            }
            size_of_board size_of_board = get_size_of_board(tab);
            board **board=get_board(size_of_board.x, size_of_board.y, tab);
            cout<<board[0][0].type;
            SDL_Window *window = make_window(size_of_board.x, size_of_board.y);
           backgroundSurf=SDL_GetWindowSurface(window);
            bool gameController=RunGame(charset, backgroundSurf, wallSurf, playerSurf, player_moveSurf, goalSurf, emptySurf, goal_crateSurf,  crateSurf, window, board, size_of_board, text);
            if(gameController==true){
                controller=-1;
              //  free(board);
            }
            free(board);
            SDL_DestroyWindow(window);
        }
        if(controller == -5){
            return 0;
        }
    }
    
}
