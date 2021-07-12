#include <ncurses.h>
#include <unistd.h>

#define DELAY 30000
#define RIGHT 1
#define DOWN 2
#define LEFT 3
#define UP 4
int i;
int len=5;

int main(int argc, char *argv[]) {
    int x[200]={5};
    int y[200]={5};
    int max_y = 0, max_x = 0;
    int next_x = 0;
    int direction = RIGHT;

    initscr();
    noecho();
    curs_set(FALSE);
    getmaxyx(stdscr, max_y, max_x);

    while(1) {
	clear();
	for (i=0; i<len; i++) {
	    mvprintw(y[i], x[i], "o");
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
endwin();
}

