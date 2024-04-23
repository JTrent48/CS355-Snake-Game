//First Deliverable


#include <stdbool.h>
#include <unistd.h>
#include <ncurses.h>


#define DELAY 30000


//function protoypes
void makeBdr();
void moveSnake();




void makeBdr(){
    
    int i = 0;
    int j = 0;
    int b = 0;
    int l = 0;
    int width = COLS; //Columns
    int height = LINES; //Rows
    initscr();
    clear();
        
        move(0, 0);
        while(i < COLS){ //Prints the top boarder
            addstr("-");
            i++;   
    
        }

        move(0, 0);
        while(j < LINES){ //Creates boarder on left side
            move(j, 0);
            //addstr("\n");
            addstr("|");

            j++;
            
             }

        move(0, COLS-1); //Move to top right corner
        
        while(l < LINES){ //Creates boarder on right side
            //addstr("\n");
            move(l, COLS-1);
            addstr("|");

            l++;

             
        }

        move(LINES-1, 0); //Move to bottom left corner

        while(b < COLS){ //Prints the bottom boarder
            addstr("-");
            b++; 
        } 
    refresh();
      
}

void moveSnake(){
    //int x = COLS/2;
    //int y = LINES/2;

    int x[100] = {COLS/2, COLS/2-1, COLS/2 -2, COLS/2 -3, COLS/2 - 4}; //x location for snake
    int y[100] = {LINES/2, LINES/2, LINES/2, LINES/2, LINES/2}; //y location for snake
    int length = 5; //Initial length of snake
    int direction = KEY_RIGHT; //Initial direction of snake

    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    while(1){
        int ch = getch();
         if (ch != ERR){
            switch(ch){ //Controls direction of snake when keys are not pressed
                case KEY_UP:
                    if (direction != KEY_DOWN)
                    direction = KEY_UP;
                    break;
                case KEY_DOWN:
                    if (direction != KEY_UP)
                    direction = KEY_DOWN;
                    break;
                case KEY_RIGHT:
                    if (direction != KEY_LEFT)
                    direction = KEY_RIGHT;
                    break;
                case KEY_LEFT:
                    if (direction != KEY_RIGHT)
                    direction = KEY_LEFT;
                    break;
                case 'q':
                    endwin();
                    return;

        }
    }

        for(int i = length -1; i>0; i--){
            x[i] = x[i-1];
            y[i] = y[i-1];
        }

        switch(direction){ //Controls the direction of the snake based on the keys
            case KEY_UP:
                y[0]--;
                break;
            case KEY_DOWN:
                y[0]++;
                break;
            case KEY_LEFT:
                x[0]--;
                break;
            case KEY_RIGHT:
                x[0]++;
                break;
        }

        clear();
        makeBdr();
        //mvaddch(y, x, 'o');
        //refresh();
        for(int i = 0; i < length; i++){
            mvaddch(y[i], x[i], 'o');
        }

        refresh();

         usleep(DELAY);
        
    }

    refresh();

    usleep(DELAY);
}
int main(int argc, char *argv[]){
    initscr();
    makeBdr();
    moveSnake();
    endwin();
    return 0;
}

        
