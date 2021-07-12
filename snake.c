
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


#define DELAY 90000
#define RIGHT 1
#define DOWN 2
#define LEFT 3
#define UP 4

//Variables and arrays//

int x[200]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int y[200]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int max_x;
int max_y;
int food_x;
int food_y;
char ch;
char endch;
int direction=RIGHT;	//Default direction is right//
int testch;

int k;
int j;
int length=5;		//starting length is 5//
int score;

int end=0;

//Functions//

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

void game_over(void){
	testch = mvinch(y[0], x[0]);
	if(testch=='o'){
		end=1;}
	else if(x[0]>=max_x){
		end=1;}
	else if(y[0]>=max_y){
		end=1;}
	else if(x[0]<0){
		end=1;}
	else if(y[0]<0){
		end=1;}
}

void food(void){		//generate random numbers for the cords of the food//
	food_x=rand()%max_x;
	food_y=rand()%max_y;}

void eat(void){				//check if field is food if so, score++//
	if(x[0]==food_x&&y[0]==food_y){
		score++;
		length++;
		food();}		//generate new cords for food//
}
	

//*************************************************************************************//
//*										      *//
//*										      *//
//*				     Main       				      *//
//*										      *//
//*************************************************************************************//


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

    while (1) {
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

        }
        else {
        


        k=length-1;		//asign value of the point before-> the snake moves//
        while (k>0){
        x[k]=x[k-1];
        y[k]=y[k-1];
        k--;
        }


        usleep(DELAY);			//in-/decrease x/y depending on direction//
        if (direction==RIGHT){
    	x[0]++;}
        else if (direction==LEFT){
    	x[0]--;}
        else if (direction==UP){
    	y[0]--;}
        else if (direction==DOWN){
    	y[0]++;}

        game_over();
        if(end==1){
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
        refresh();
        }
    }
endwin();
}
