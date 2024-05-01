//First Deliverable


#include <stdbool.h>
#include <unistd.h>
#include <ncurses.h>



#define DELAY 30000

int random_direction;
int directions[] = {KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT};
//function protoypes
void makeBdr();
void moveSnake();
bool checkCollision(int x[], int y[], int length);
void Trophy();
bool trophyCollision(int x[], int y[], int length);

//Global variables
int trophyX ;
int trophyY ;
int trophyValue;
int trophyExpiryTime;
int trophyCreationTime;
bool trophyExists = false;
int length;
int speed;


//Makes border
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



//Checks for collisions
bool checkCollision(int x[], int y[], int length){
    int width = COLS;
    int height = LINES;

    if(x[0] == 0 || x[0] >= COLS || y[0] == 0 || y[0] >= LINES){ //Checks for collision with walls
        return true;
    } 

    for(int i = 1; i<length; i++){
        if(x[0] == x[i] && y[0] == y[i]){ //Checks for collision with body
            return true;
        }
    }

    return false;
}


//Check for trophy collisions
bool trophyCollision(int x[], int y[], int length){
    if(x[0] == trophyX && y[0] == trophyY){
        trophyExists = false;
        return true;
    }

    return false;
}


//Spawns in trophy
void Trophy(){
    if(!trophyExists){
        trophyX = rand() % (COLS - 2) + 1; //avoid spawning on x border
        trophyY = rand() % (LINES - 2) + 1; //avoid spawning on y border
        trophyValue = rand() %9 + 1;
        trophyExists = true;
        trophyCreationTime = time(NULL);
        //mvaddch(trophyY, trophyX, '*');
        mvprintw(trophyY, trophyX, "%d", trophyValue);

        //length +=trophyValue;
    }
}

//Move snake method
void moveSnake(){
    //int x = COLS/2;
    //int y = LINES/2;

    int x[100] = {COLS/2, COLS/2-1, COLS/2 -2, COLS/2 -3, COLS/2 - 4}; //x location for snake
    int y[100] = {LINES/2, LINES/2, LINES/2, LINES/2, LINES/2}; //y location for snake
    length = 6;
    int direction = random_direction; //Initial direction of snake
    int num_positions = 10; //Number of positions trophy can spawn in
    //speed = 1000000 / length;

    //Initialize first trophy
    Trophy();

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

        

        if(length > 1){
        for(int i = length -1; i>0; i--){
            x[i] = x[i-1];
            y[i] = y[i-1];
        }
        
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

        

        if(checkCollision(x, y, length)){
            endwin();
            return;
        }

        if(trophyCollision(x, y, length)){
        Trophy();
        length+= trophyValue;
       }
        
        speed = (1000000 / length) / 2;
        mvaddch(' ', y[length - 1], x[length - 1]);
   

        refresh();
        mvaddch(y[0], x[0], 'o');
        for(int i = 1; i<length; i++){
            if(x[i] >=0 && x[i] < COLS && y[i] >=0 && y[i] < LINES){
            mvaddch(y[i], x[i], 'o');
        }
        mvaddch(y[length-1], x[length-1], ' ');

        
    }
    //2 * (COLS + LINES) - 4
    if(length >= 20){
        endwin();
        clear();
        mvprintw(LINES/2, (COLS-8)/2, "You win!");
        refresh();
        sleep(2);
        return;
    }
 
        
        
        refresh();
        usleep(speed);
        
    }

    
}

int main(int argc, char *argv[]){

    initscr();
    
    srand(time(NULL));
    
    int numDirections = sizeof(directions) / sizeof(directions[0]);
    random_direction = directions[rand() % numDirections];
    int num_positions = 10; //Number of positions trophy can spawn in

    makeBdr();
    Trophy();
    moveSnake();
    endwin();
    return 0;
}

        
