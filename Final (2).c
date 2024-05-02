/*
CS355 Snake Game             
Jordyn T, Joey C, Abbie M
*/

//Imports
#include <stdbool.h>
#include <unistd.h>
#include <ncurses.h>



//Function Protoypes

//Function for the creation of the border around the screen
void makeBdr();
//Function for the movement of the snake based on user input
void moveSnake();
//Function the checks for collision (the snake dying)
bool checkCollision(int x[], int y[], int length);
//Function for spawning trophies in the snake pit
void Trophy();
//Function the checks for trophy collision
bool trophyCollision(int x[], int y[], int length);

//Global variables

//X Coordinate for Trophy
int trophyX ;
//Y coordinate for Trophy
int trophyY ;
//Value of Trophy
int trophyValue;
//Expiration Time of Trophy
int trophyExpiryTime;
//Creation Time of Trophy
int trophyCreationTime;
//Boolean for existance of trophy
bool trophyExists = false;
//length of snake
int length;
//speed of snake
int speed;
//random direction number
int random_direction;
//directions of the snake
int directions[] = {KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT};


//Function to Create the border around the screen
void makeBdr(){
    int top = 0;
    int left = 0;
    int bottom = 0;
    int right = 0;
    int width = COLS; //Columns
    int height = LINES; //Rows
    //clear the screen
    initscr();
    clear();
        
        move(0, 0);
        while(top < COLS){ //Prints the top boarder
            addstr("-");
            top++;   
    
        }

        move(0, 0);
        while(left < LINES){ //Creates boarder on left side
            move(left, 0);
            //addstr("\n");
            addstr("|");

            left++;
            
             }

        move(0, COLS-1); //Move to top right corner
        
        while(right < LINES){ //Creates boarder on right side
            //addstr("\n");
            move(right, COLS-1);
            addstr("|");
            right++;
        }

        move(LINES-1, 0); //Move to bottom left corner

        while(bottom < COLS){ //Prints the bottom boarder
            addstr("-");
            bottom++; 
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
        trophyExists = false; //Trophy is consumer, so set it to not exist
        return true;
    }
    //collision with trophy detected
    return false;
}


//Spawns in trophy
void Trophy(){
    if(!trophyExists){
        trophyX = rand() % (COLS - 2) + 1; //avoid spawning on x border
        trophyY = rand() % (LINES - 2) + 1; //avoid spawning on y border
        trophyValue = rand() %9 + 1; //randomly assigns a value to the trophy
        trophyExists = true; //set the flag to indiacte the existence of a trophy
        trophyCreationTime = time(NULL); //records creation time of the trophy
        //mvaddch(trophyY, trophyX, '*');
        mvprintw(trophyY, trophyX, "%d", trophyValue);

        length +=trophyValue;
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

    //configures ncurses settings
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    
    //Main loop for the snake game
    while(1){
        //get user input for snake movement
        int ch = getch();
         if (ch != ERR){
            //control the direction of the snake based on user input
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
                case 'q': //Quit the game if 'q' is pressed
                    endwin();
                    return;

        }
    }

        
        //update the snake's body posirions based on uts direction
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

        
        //checks for collisions
        if(checkCollision(x, y, length)){
            endwin();
            return;
        }
        //checks for trophy collisions
        if(trophyCollision(x, y, length)){
            length+= trophyValue; //increases the length of the snake
            Trophy(); //Spawns a new trophy
        
        //Shift the body of the snake to acommodate new length
        for(int i = length - trophyValue; i < length; i++){
            x[i] = x[i-1];
            y[i] = y[i-1];                            
        }        
       }
        //adjust  speed based on a snake length
        speed = (1000000 / length);
        mvaddch(' ', y[length - 1], x[length - 1]);
   

        refresh();
        mvaddch(y[0], x[0], 'o');
        for(int i = 1; i<length; i++){
            if(x[i] >=0 && x[i] < COLS && y[i] >=0 && y[i] < LINES){
            mvaddch(y[i], x[i], 'o');
        }
        mvaddch(y[length-1], x[length-1], ' ');

        
    }
    //If the snake length reaches have the length of the perimeter, display a win message
    if(length == 2 * (COLS + LINES) - 4){
        endwin();
        clear();
        mvprintw(LINES/2, (COLS-8)/2, "You win!");
        refresh();
        sleep(2);
        return;
    }
        //refresh the screen and add delay for the next move
        refresh();
        usleep(speed);
    }
    
}

int main(int argc, char *argv[]){

    initscr();
    
    srand(time(NULL));
    
    //randomly selects the initial direction of the snake
    int numDirections = sizeof(directions) / sizeof(directions[0]);
    random_direction = directions[rand() % numDirections];
    int num_positions = 10; //Number of positions trophy can spawn in

    //initialize the game
    makeBdr();
    Trophy();
    moveSnake();

    //ends ncurses mode and exit the program
    endwin();
    return 0;
} 
