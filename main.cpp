#include <iostream>
#include <stdlib.h>
using namespace std; 

struct Board{
    const int rows =3, cols = 3; 
    char** grid ; // 3x3 tictactoe grid 
    char winner; // will indicate if player won or comp won 
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
    bool moveAvail(){
        for(int i =0 ; i< rows ; i++)
        {
            for(int j = 0 ; j<cols; j++ )
            {
               if(grid[i][j] == '-')
                return true; 
            }
        }
        return false; 
    }
    // this function check the status of the game;  returns false if the game is still going and true if its finished 
    bool gameOver()
    {
        if(grid[0][0] == grid[0][1] && grid[0][1]== grid[0][2] && grid[0][0] != '-') { // first row 
            winner =grid[0][0] ; 
           return true; 
        }
        if(grid[1][0] == grid[1][1] && grid[1][1]== grid[1][2] && grid[1][0] != '-') { // second row 
            winner = grid[1][0]; 
           return true; 
        }
        if(grid[2][0] == grid[2][1] && grid[2][1]== grid[2][2] && grid[2][0] != '-') { // third row 
            winner = grid[2][0]; 
           return true; 
        }

        if(grid[0][0] == grid[1][0] && grid[1][0]== grid[2][0] && grid[0][0] != '-') { // first col 
            winner = grid[0][0]; 
           return true; 
        }
        if(grid[0][1] == grid[1][1] && grid[1][1]== grid[2][1] && grid[0][1] != '-') { // second col 
            winner = grid[0][1]; 
           return true; 
        }
        if(grid[0][2] == grid[1][2] && grid[1][2]== grid[2][2] && grid[0][2] != '-') { // third col 
            winner = grid[0][2]; 
           return true; 
        }
        
        if(grid[0][0] == grid[1][1] && grid[1][1]== grid[2][2] && grid[0][0] != '-') { // first diag 
            winner = grid[0][0]; 
           return true; 
        }
        if(grid[2][0] == grid[1][1] && grid[1][1]== grid[0][2] && grid[2][0] != '-') { // second diag 
            winner = grid[2][0]; 
           return true; 
        }

        // if all that still is false then check if there any moves still available
        // if so return false cus game is not over
        if(moveAvail()) return false; 

        // else it has ended in a draw 
        return true; 
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
    Board* board = new Board(); 
    bool max=true; // is it maximising players turn ? 
    while(true){
        while(!board->gameOver()){
            system("CLS"); 
            board->printBoard(); 
            char character= max? 'X': 'O'; 
            cout<<"Player "<< character << " input your move in the form:  row column"<<endl; 
            int row, col; 
            cin>>row >> col ; 
            while(row>3||row<1||col>3||col<1){
                cout<<"Invalid Input. Try again (has to be in form: row column)"<<endl; 
                cin>>row>>col; 
            }
            row-=1; col-=1; 
            board->makeMove(max, row, col ); 
            max = !max; 
        }   

        system("CLS"); 
        board->printBoard(); 
        if(board->winner){
            cout<<"The winner is player "<<board->winner<<"!"<<endl; 
        }else{
            cout<<"The game ended in a draw"<<endl; 
        }
        cout<<"Play again? (y/n)"<<endl; 
        char response ; 
        cin>> response; 
        if(response != 'y') 
            break; 

        // reset game 
        board = new Board(); 
        max = true; 
    }
    return 0; 
}