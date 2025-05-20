#include<iostream>
#include<conio.h>      // For _kbhit() and _getch() to capture keyboard input
#include<windows.h>    // For Sleep(), cursor manipulation with SetConsoleCursorPosition
#include<ctime>        // For random seed using time()
using namespace std;

bool gameOver;
const int width=20, height=20;
int x, y;              // Coordinates of the snake's head
int fruitX, fruitY;    // Coordinates of the fruit
int score;
int tailX[100], tailY[100];
int nTail;             // Length of the snake's tail

// Enum to represent direction
enum eDirection{STOP=0, LEFT, RIGHT, UP, DOWN};
eDirection dir; // Current direction of snake

// Initializes the game state
void Setup(){
    gameOver=false;         // Set game as active
    dir=STOP;               // Snake initially doesn't move
    x=width/2;            // Start snake in middle of screen
    y=height/2;
    fruitX=rand()%width;
    fruitY=rand()%height;
    score=0;
}
// Moves the cursor to a given position in console (used to redraw efficiently)
void gotoXY(int x, int y){
    COORD pos={(SHORT)x, (SHORT)y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
// Draws the game board each frame
void Draw(){
    gotoXY(0, 0); // Set cursor to top-left to overwrite previous frame
    // Draw top wall
    for(int i=0; i<width+2; i++) cout<<"#";
    cout<<endl;
    // Draw each line of the play area
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            if(j==0) cout<<"#"; // Left wall
            if(i==y && j==x) cout<<"O"; // Snake's head
            else if(i==fruitY && j==fruitX) cout<<"F"; // Fruit
            else{
                bool print=false;
                // Check if current coordinate matches any tail segment
                for(int k=0; k<nTail; k++){
                    if(tailX[k]==j && tailY[k]==i){
                        cout<<"o"; // Snake's tail
                        print=true;
                    }
                }
                if(!print) cout<<" "; // Empty space if no snake part is here
            }
            if(j==width-1) cout<<"#"; // Right wall
        }
        cout<<endl;
    }
    // Draw bottom wall
    for(int i=0; i<width+2; i++) cout<<"#";
    cout<<"\nScore: "<<score<<"\n";
    cout<<"Use W A S D to move. Press X to quit.\n";
}
// Handles user input
void Input(){
    if(_kbhit()){ // Check if key was pressed
        switch(_getch()){ // Read pressed key
            case 'a': if(dir!=RIGHT) dir=LEFT; break;  // Move left if not moving right
            case 'd': if(dir!=LEFT) dir=RIGHT; break;  // Move right if not moving left
            case 'w': if(dir!=DOWN) dir=UP; break;     // Move up if not moving down
            case 's': if(dir!=UP) dir=DOWN; break;     // Move down if not moving up
            case 'x': gameOver=true; break;               // Exit the game
        }
    }
}
// Updates game logic every frame
void Logic(){
    // Move tail: shift positions of each tail segment
    int prevX=tailX[0];
    int prevY=tailY[0];
    int prev2X, prev2Y;
    tailX[0]=x; // Tail starts where head was
    tailY[0]=y;
    // Move the tail segments
    for(int i=1; i<nTail; i++){
        prev2X=tailX[i];
        prev2Y=tailY[i];
        tailX[i]=prevX;
        tailY[i]=prevY;
        prevX=prev2X;
        prevY=prev2Y;
    }
    // Update head position based on direction
    switch(dir){
        case LEFT: x--; break;
        case RIGHT: x++; break;
        case UP: y--; break;
        case DOWN: y++; break;
        default: break; // If STOP, do nothing
    }
    // Collision with wall
    if(x>=width || x<0 || y>=height || y<0) gameOver=true;
    // Collision with tail (self)
    for(int i=0; i<nTail; i++)
        if(tailX[i]==x && tailY[i]==y) gameOver = true;
    // If snake eats the fruit
    if(x==fruitX && y==fruitY){
        score+=10;                   // Increase score
        fruitX=rand()%width;       // Spawn new fruit
        fruitY=rand()%height;
        nTail++;                       // Increase tail length
    }
}
int main(){
    srand(time(0)); // Seed for random number generator
    Setup();        // Initialize game variables
    // Hide the blinking cursor in console for better visuals
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hOut, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hOut, &cursorInfo);
    // Game loop runs until gameOver becomes true
    while(!gameOver){
        Draw();      // Render the game board
        Input();     // Handle input
        Logic();     // Update game state
        Sleep(100);  // Delay to control speed (in milliseconds)
    }
    // After game ends, print the final score
    gotoXY(0, height+5);
    cout<<"Game Over! Final Score: "<<score<<endl;
}
