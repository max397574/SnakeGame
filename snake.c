#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define RIGHT 1
#define DOWN 2
#define LEFT 3
#define UP 4
#define LENGHT 1
#define SPEED 2

int x[200]={5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int y[200]={5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int delay=90000;
int max_x;
int max_y;
int food_x;
int food_y;
char ch;
char endch;
int nokey=1;
int direction=RIGHT;
int testch;
int rounds=0;
int increment=1;
int mode=3;

int k;
int j;
int length=5;
int score;

int end=0;

int kbhit(void)
{
    int ch = getch();

    if (ch != ERR) {
        ungetch(ch);
        return 1;
    } else {
        return 0;
    }
}

int game_over(void){
    bool game_over=false;
    testch = mvinch(y[0], x[0]);
    if (rounds>=10) {
        for (int i=1; i<=length; i++) {
            if (x[i]==x[0]&&y[i]==y[0]) {
                game_over=true;
            }
        }
    }
    if (testch=='-'||testch=='|') {
        game_over=true;}
    if(x[0]==max_x-1){
        game_over=true;}
    else if(y[0]==max_y-5){
        game_over=true;}
    else if(x[0]==3){
        game_over=true;}
    else if(y[0]==-1){
        game_over=true;}
    return game_over;
}

void food(void){
    food_x=rand()%max_x-1;
    food_y=rand()%max_y-6;}

void eat(void){	
    if(x[0]==food_x&&y[0]==food_y){
        score++;
        if (mode==LENGHT) {
            length+=increment;
        }
        else {
            delay-=5000;
        }
        food();}
}

void draw_borders(void) {
    for (int i=0; i<=max_x; i++) {
        mvprintw(max_y-5,i,"-");
    }
    for (int i=0; i<=max_y; i++) {
        mvprintw(i,0,"|");
        mvprintw(i,(max_x-1),"|");
    }
}


int main(void)
{
    start:
    srand(time(NULL));
    initscr();
    getmaxyx(stdscr, max_y, max_x);
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    curs_set(FALSE);
    scrollok(stdscr, TRUE);
    food();
    clear();
    while(mode==3) {
        if (kbhit()) {
            ch=getch();
            if (ch=='l') {
                mode=LENGHT;
            }
            else {
                mode=SPEED;
            }
            nokey=0;
            continue;
        }
        mvprintw(20,0,"\t\tChoose your mode:\n\t\t'l' to increment length after eating\n\t\t's'to incremt speed\n\n\t\tPress the character until the game starts. \n\t\tStandart will be lenght");
        refresh();
        usleep(delay*50);
        clear();
    }

    while (1) {
        rounds++;
        if (kbhit()) {		//check if WASD hit//
            ch=getch();
            if (ch=='w'){				//change direction but not to the opposite//
                if (direction!=DOWN)direction= UP;}	//to avoid GAME OVER//
            else if (ch=='d'){
                if (direction!=LEFT)direction = RIGHT;}
            else if (ch=='s'){
                if (direction!=UP)direction = DOWN;}
            else if (ch=='a'){
                if (direction!=RIGHT)direction = LEFT;}
            else if (ch=='f') {
                food();
            }
        }
        else {

            k=length-1;		//asign value of the point before-> the snake moves//
            while (k>0){
                x[k]=x[k-1];
                y[k]=y[k-1];
                k--;
            }

            usleep(delay);			//in-/decrease x/y depending on direction//
            if (direction==RIGHT){
                x[0]++;}
            else if (direction==LEFT){
                x[0]--;}
            else if (direction==UP){
                y[0]--;}
            else if (direction==DOWN){
                y[0]++;}

            if(game_over()){
                system("clear");
                printf("\n\nGAME OVER\n\n");
                printf("\n\nYour score was %d.\n\n\n",score);
                exit(0);
            }

            clear();			//print all points//
            for (j=length-1; j>=0; j--){
                mvprintw(y[j], x[j], "o");}
            eat();
            mvprintw(food_y, food_x, "O");
            mvprintw(max_y-3, 3, "Score: %d",score);
            mvprintw(max_y-1, 3, "Score: %d,%d",x[0],y[0]);
            mvprintw(max_y-2, 3, "Press 'f' if there is no food visible");
            draw_borders();
            refresh();
        }
    }
    endwin();
}
