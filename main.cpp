#include <iostream>
#include <iomanip> // setw()
#include <time.h>
using namespace std;
using std::cout;
using std::endl;
using std::cin;

const int BOARD_SIZE = 4;
int board[BOARD_SIZE][BOARD_SIZE];

void initBoard(){//Init the board with 2 random tiles
    srand(time(nullptr));
    for(int i=0; i<BOARD_SIZE; i++){
        for(int j=0; j<BOARD_SIZE; j++){
            board[i][j] =0 ;
        }
    }
    for(int i=0; i<2; i++){
        int x,y;
        do{
            x= rand()%BOARD_SIZE;
            y=rand()%BOARD_SIZE;
        }while(board[x][y]!=0);
        int value = (rand() < RAND_MAX * 0.9) ? 2 : 4;// 2 or 4
        board[x][y] = value;
    }
}

void printBoard(){//print the board
    if(system("cls")==-1){
        return;
    }
    for(int i=0; i<BOARD_SIZE; i++){
        for(int j=0; j<BOARD_SIZE; j++){
            if(board[i][j]==0){
                cout << setw(5) << "_"; // set the width of the output field to 5
            }
            else{
                cout << setw(5) << board[i][j]; // set the width of the output field to 5
            }

        }
        cout << endl;
    }
}

bool isValidMoveLeft(){//check if still valid move
    for(int i=0; i<BOARD_SIZE; i++){//check full
        for(int j=0; j<BOARD_SIZE; j++){
            if(board[i][j]==0){
                return true;
            }
        }
    }
    //check adjacents
    for(int i=0; i<BOARD_SIZE; i++){
        for(int j=0; j<BOARD_SIZE; j++){
            if(j<BOARD_SIZE-1 && board[i][j] == board[i][j+1]){
                return true;
            }

            if(i<BOARD_SIZE-1 && board[i][j] == board[i+1][j]){
                return true;
            }
        }
    }

    return false;//invalid
}

void addNewTile(){//add random tile
    srand(time(nullptr));
    if(!isValidMoveLeft()){
        return;
    }

    int x,y;
    do{
        x= rand()%BOARD_SIZE;
        y=rand()%BOARD_SIZE;
    } while(board[x][y]!=0);

    int value = (rand() < RAND_MAX * 0.9) ? 2 : 4;// 2 or 4
    board[x][y] = value;
}

bool changed(int b1[BOARD_SIZE][BOARD_SIZE],int b2[BOARD_SIZE][BOARD_SIZE]){//check if 2 boards different
    for(int i=0; i<BOARD_SIZE; i++){
        for(int j=0; j<BOARD_SIZE; j++){
            if(b1[i][j]!=b2[i][j])
                return true;
        }
    }
    return false;
}


void moveTiles(int direction){//the move function
    int dx=0, dy=0;
    bool add=false;

    int tmpBoard[BOARD_SIZE][BOARD_SIZE];
    for(int i=0; i<BOARD_SIZE; i++){
        for(int j=0; j<BOARD_SIZE; j++){
            tmpBoard[i][j] = board[i][j];
        }
    }//for comparing board changes purposes

    bool paired[BOARD_SIZE][BOARD_SIZE];
    for(int i=0; i<BOARD_SIZE; i++){
        for(int j=0; j<BOARD_SIZE; j++){
            paired[i][j] = false;
        }
    }//flags to avoid double merging

    int shift;
    switch(direction){
        case 0:// MOVE UP
            for(int i=1; i<BOARD_SIZE; i++){
                for(int j=0; j<BOARD_SIZE; j++){
                    shift=0;
                    //STARTING ROW 1,FOR EVERY TILE, CHECK IF IT CAN BE SHIFTED UP,DO IT, CHECK IF CAN BE MERGED, DO IT.
                    for(int k=0; k < i; k++){
                        if(board[k][j]==0) shift++;
                    }
                    if(shift>0){
                        board[i-shift][j]=board[i][j];
                        board[i][j]=0;
                    }
                    if(board[i-shift-1][j]==board[i-shift][j] && !paired[i-shift-1][j] && !paired[i-shift][j]){
                        board[i-shift-1][j]*=2;
                        board[i-shift][j]=0;
                        paired[i-shift-1][j]=true;
                    }
                }
            }
            break;
        case 1://RIGHT
            for(int i=0; i<BOARD_SIZE; i++){
                for(int j=1; j<BOARD_SIZE; j++){
                    //STARTING COL 2,FOR EVERY TILE, CHECK IF IT CAN BE SHIFTED RIGHT,DO IT, CHECK IF CAN BE MERGED, DO IT.
                    shift=0;
                    for(int k=0; k < j; k++){
                        if(board[i][3-k]==0) shift++;
                    }
                    if(shift>0){
                        board[i][3-j+shift]=board[i][3-j];
                        board[i][3-j]=0;
                    }
                    if(4-j+shift <=3){
                        if(board[i][4-j+shift]==board[i][3-j+shift] && !paired[i][4-j+shift] && !paired[i][3-j+shift]){
                            board[i][4-j+shift]*=2;
                            board[i][3-j+shift]=0;
                            paired[i][4-j+shift]=true;
                        }
                    }
                }
            }
            break;
        case 2://DOWN
            //STARTING ROW 2,FOR EVERY TILE, CHECK IF IT CAN BE SHIFTED DOWN,DO IT, CHECK IF CAN BE MERGED, DO IT.
            for(int i=0; i<3; i++){
                for(int j=0; j<BOARD_SIZE; j++){
                    shift=0;
                    for(int k=0; k < i+1; k++){
                        if(board[3-k][j]==0) shift++;
                    }
                    if(shift>0){
                        board[2-i+shift][j]=board[2-i][j];
                        board[2-i][j]=0;
                    }
                    if(3-i+shift<=3){
                        if(board[2-i+shift][j]==board[3-i+shift][j]&&!paired[3-i+shift][j] &&!paired[2-i+shift][j]){
                            board[3-i+shift][j]*=2;
                            board[2-i+shift][j]=0;
                            paired[3-i+shift][j]=true;
                        }
                    }
                }
            }
            break;
        case 3://LEFT
            for(int i=0; i<BOARD_SIZE; i++){
                for(int j=1; j<BOARD_SIZE; j++){
                    //STARTING FROM COL 1,FOR EVERY TILE, CHECK IF IT CAN BE SHIFTED LEFT,DO IT, CHECK IF CAN BE MERGED, DO IT.
                    shift=0;
                    for(int k=0; k < j; k++){
                        if(board[i][k]==0) shift++;
                    }
                    if(shift>0){
                        board[i][j-shift]=board[i][j];
                        board[i][j]=0;
                    }
                    if(board[i][j-shift]==board[i][j-shift-1] && !paired[i][j-shift-1] && !paired[i][j-shift]){
                        board[i][j-shift-1]*=2;
                        board[i][j-shift]=0;
                        paired[i][j-shift-1]=true;
                    }
                }
            }
            break;
    }

    if(changed(board,tmpBoard)){//add new tile
        addNewTile();
    }
}

bool checkWin(){//Check if there is win
    for(int i=0; i<BOARD_SIZE; i++){
        for(int j=0; j<BOARD_SIZE; j++){
            if(board[i][j]==2048){
                return true;
            }
        }
    }
    return false;
}



int main() {
    initBoard();
    printBoard();

    while(!checkWin() && isValidMoveLeft()){
        char move;
        cout << "Enter your move W/A/S/D";
        cin >> move;
        switch(move){
            case 'w':
                moveTiles(0);
                break;
            case 'd':
                moveTiles(1);
                break;
            case 's':
                moveTiles(2);
                break;
            case 'a':
                moveTiles(3);
                break;
            default:
                cout << "Invalid move. Please enter from WASD." <<endl;
        }
        printBoard();
    }

    if(checkWin()){
        cout << "Congratulations! you won!" << endl;
    }else{
        cout << "Game over. You lost" << endl;
    }

    return 0;
}