#include<iostream>
#include<limits>
using namespace std;

char board[3][3];

void initializeBoard(){
    char count = '1';
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            board[i][j] = count++;
}

void displayBoard(){
    cout<<"\n";
    for(int i=0; i<3; i++){
        cout<<" ";
        for(int j=0; j<3; j++){
            cout<<board[i][j];
            if(j<2) cout<<" | ";
        }
        cout<<"\n";
        if(i<2) cout<<"---+---+---\n";
    }
    cout<<"\n";
}

bool checkWin(char player){
    for(int i=0; i<3; i++)
        if(board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return true;
    for(int j=0; j<3; j++)
        if(board[0][j] == player && board[1][j] == player && board[2][j] == player)
            return true;
    if(board[0][0] == player && board[1][1] == player && board[2][2] == player)
        return true;
    if(board[0][2] == player && board[1][1] == player && board[2][0] == player)
        return true;
    return false;
}

bool isBoardFull(){
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            if(board[i][j] != 'X' && board[i][j] != 'O')
                return false;
    return true;
}

// Player move
bool playerMove(){
    int choice;
    cout<<"Your turn (X). Enter your move (1-9): ";
    cin>>choice;

    if(!cin){
        cin.clear();
        cin.ignore(10000, '\n');
        cout<<"Invalid input. Please enter a number between 1 and 9.\n";
        return false;
    }

    if(choice<1 || choice>9){
        cout<<"Invalid move. Try again.\n";
        return false;
    }

    int row = (choice-1)/3;
    int col = (choice-1)%3;

    if(board[row][col] == 'X' || board[row][col] == 'O'){
        cout<<"Cell already occupied. Try again.\n";
        return false;
    }

    board[row][col] = 'X';
    return true;
}

// Minimax algorithm returns score of board
int minimax(bool isMaximizing){
    if(checkWin('O')) return 10;
    if(checkWin('X')) return -10;
    if(isBoardFull()) return 0;

    if(isMaximizing){
        int bestScore = numeric_limits<int>::min();
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                if(board[i][j] != 'X' && board[i][j] != 'O'){
                    char backup = board[i][j];
                    board[i][j] = 'O';
                    int score = minimax(false);
                    board[i][j] = backup;
                    if(score > bestScore) bestScore = score;
                }
            }
        }
        return bestScore;
    }
    else{
        int bestScore = numeric_limits<int>::max();
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                if(board[i][j] != 'X' && board[i][j] != 'O'){
                    char backup = board[i][j];
                    board[i][j] = 'X';
                    int score = minimax(true);
                    board[i][j] = backup;
                    if(score < bestScore) bestScore = score;
                }
            }
        }
        return bestScore;
    }
}

// Computer (O) picks the best move based on minimax
void aiMove(){
    int bestScore = numeric_limits<int>::min();
    int moveRow = -1;
    int moveCol = -1;

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if(board[i][j] != 'X' && board[i][j] != 'O'){
                char backup = board[i][j];
                board[i][j] = 'O';
                int score = minimax(false);
                board[i][j] = backup;

                if(score > bestScore){
                    bestScore = score;
                    moveRow = i;
                    moveCol = j;
                }
            }
        }
    }

    if(moveRow != -1 && moveCol != -1){
        board[moveRow][moveCol] = 'O';
        cout<<"Computer places O in position "<<(moveRow * 3 + moveCol + 1)<<".\n";
    }
}

int main(){
    initializeBoard();
    cout<<"Welcome to Tic Tac Toe!\nYou are X, computer is O.\n";

    while(true){
        displayBoard();
        while(!playerMove()) {}

        if(checkWin('X')){
            displayBoard();
            cout<<"Congratulations! You win!\n";
            break;
        }

        if(isBoardFull()){
            displayBoard();
            cout<<"It's a draw!\n";
            break;
        }
      
        aiMove();
        if(checkWin('O')){
            displayBoard();
            cout<<"Computer wins! Better luck next time.\n";
            break;
        }

        if(isBoardFull()){
            displayBoard();
            cout<<"It's a draw!\n";
            break;
        }
    }
    cout<<"Game over. Thanks for playing!\n";
}
