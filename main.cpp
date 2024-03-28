#include <iostream>
using namespace std; 

struct Board{
    const int rows =3, cols = 3; 
    char** grid ; // 3x3 tictactoe grid 

    Board(){
        grid = new char*[rows]; 
        for(int i = 0; i< rows ; i++)
        {
            grid[i] = new char[cols];
            for(int j = 0 ; j<cols; j++)
            {
                grid[i][j] = '-'; 
            } 
        }

    }

    Board* copy(Board* board)
    {
        Board* temp = new Board(); 
        for(int i =0 ; i< rows ; i++)
        {
            for(int j = 0 ; j<cols; j++ )
            {
                temp->grid[i][j]= board->grid[i][j]; 
            }
        }
        return temp; 
    }
    // takes in whether its the computer's turn or the players turn 
    void makeMove(bool max , int row , int col ) 
    {
        char character = max ? 'X' : '0'; 
        grid[row][col] = character; 
    }
    void printBoard(){
        for(int i =0; i< rows ; i++)
        {
            for(int j = 0 ; j<cols; j++)
            {
                cout<<grid[i][j]<<" "; 
            }cout<<endl; 
        }
    }
}; 

int main(){
    return 0; 
}