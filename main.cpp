#include <iostream>
#include <stdlib.h>
using namespace std; 

struct Coords {
    int row , col; 
    Coords(int r , int c )
    {
        row = r ; col = c; 
    }
    Coords(){}
}; 
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

    Board* copy()
    {
        Board* temp = new Board(); 
        for(int i =0 ; i< rows ; i++)
        {
            for(int j = 0 ; j<cols; j++ )
            {
                temp->grid[i][j]= grid[i][j]; 
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
        char character = max ? 'X' : 'O'; 
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

int depth = 1 ; 
//takes in the current board and whether it is the computers turn or the player's turn 
// going to return the eval of the current board 
int minimax(Board* board, bool max)
{
    
    if(board->gameOver())
    {
        
        if(board->winner =='X')
        {
            return 1; // computer won 
        }else if (board->winner == 'O'){
            return -1; // human won 
        }else{
            return 0; // draw 
        }
        
    }
     // if maximizing player (computer) you want to pick the child with the highest eval
    if(max){
        Coords bestMove; 
        int bestScore = -2; // so any score can be greater initially 
        // first generate children
        for(int i =0; i<board->rows;i++)
        {
            for(int j =0 ; j<board->cols; j++)
            {
                // check if space is empty
                if(board->grid[i][j] != '-')
                    continue; 
                // make a copy board 
                Board* child = board->copy(); 
                // then make move 
                child->makeMove(max, i, j); 
                // now get eval 
                int childScore = minimax(child, !max); // since it would be the humans turn now 
                if(childScore > bestScore)
                {
                    bestScore = childScore; 
                    bestMove.row = i ; 
                    bestMove.col = j; 
                }
            }
        }
        // now the computer can make it's move
        board->makeMove(max, bestMove.row, bestMove.col);  
        return bestScore; 
    }else{
         Coords worstMove; // worst child for computer best child for human
        int worstScore = 2; // so any score can be less initially 
        // first generate children
        for(int i =0; i<board->rows;i++)
        {
            for(int j =0 ; j<board->cols; j++)
            {
                // check if space is empty
                if(board->grid[i][j] != '-')
                    continue; 
                // make a copy board 
                Board* child = board->copy(); 
                // then make move 
                child->makeMove(max, i, j); 
                // now get eval 
                int childScore = minimax(child, !max); // since it would be the humans turn now 
                if(childScore < worstScore)
                {
                    worstScore = childScore; 
                    worstMove.row = i ; 
                    worstMove.col = j ; 
                }
            }
        }
        // this would be the best possible move the human could make 
        board->makeMove(max, worstMove.row, worstMove.col); 
        return worstScore; 
    }
}
int main(){
    Board* board = new Board(); 
    bool max=true ; // is it maximising players turn ? 
     
    while(true){
        cout<<"Computer First? (y/n)"<<endl; 
        char computerFirst;
        cin>>computerFirst; 
        if(computerFirst=='y')
        {
            max = true; 
        }else{
            max= false; 
        }
        while(!board->gameOver()){
            if(!max){
                system("CLS"); 
                board->printBoard(); 
                char character= max? 'X': 'O'; 
                cout<<"Player "<< character << " input your move in row, col form. Ex: 3 1 "<<endl; 
                int row, col; 
                std::cin>>row >> col ; 
                while(row>3||row<1||col>3||col<1 || board->grid[row-1][col-1]!='-'){
                    cout<<"Invalid Input. Try again (has to be in form: row column)"<<endl; 
                    cin>>row>>col; 
                }
                row-=1; col-=1; 
                board->makeMove(max, row, col ); 
                max = !max; 
                
            }else{
                //if start of the game just go top left to save on computation time
                
                // computer's turn 
                minimax(board, true); 
                max =!max; 
            }
             
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