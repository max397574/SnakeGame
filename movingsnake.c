#include <ncurses.h>
#include <unistd.h>

#define DELAY 50000
#define RIGHT 1
#define DOWN 2
#define LEFT 3
#define UP 4
int i;
int len=5;
char ch;

int kbhit(void){
    int cha = getch();
    if (cha != ERR) {
        ungetch(cha);
        return 1;
    }
    else {
        return 0;
    }
}



int main(int argc, char *argv[]) {
    int x[200]={5,5,5,5,5};
    int y[200]={5};
    int max_y = 0, max_x = 0;
    int next_x = 0;
    int direction = DOWN;

    initscr();
    noecho();
    curs_set(FALSE);
    getmaxyx(stdscr, max_y, max_x);

    while(1) {
	ch=getch();
	if (ch=='w'){
	    if (direction!=DOWN)direction= UP;}
	else if (ch=='d'){
	    if (direction!=LEFT)direction = RIGHT;}
	else if (ch=='s'){
	    if (direction!=UP)direction = DOWN;}
	else if (ch=='a'){
	    if (direction!=RIGHT)direction = LEFT;}
	else {

	    clear();
	    for (i=0; i<len; i++) {
		mvprintw(y[i], x[i], "o");
	    }
	    for (i=len; i>0; i--) {
		y[i]=y[i-1];
		x[i]=x[i-1];
	    }
	    refresh();

	    usleep(DELAY);

	    if (direction==RIGHT){
		x[0]++;}
	    else if (direction==LEFT){
		x[0]--;}
	    else if (direction==UP){
		y[0]--;}
	    else if (direction==DOWN){
		y[0]++;}
	}
    }
endwin();
}

