// snippet of a class to implement the n times n chess board for the n-queens problem
#include<iostream>
#include<vector>
using namespace std;


class Board {
private:
   // insert the code of the representation here
   // representation of the board, MATRIX, booleans
   int n;
   vector<vector<int> > b;

public:

   Board(int n): b(n, vector<int>(n))
   {
       //b = vector<vector<int> > (n, vector<int>(n));
       for (int i =0; i < n; ++i){
           for(int j = 0; j < n; ++j){
               b[i][j] = 0;
           }
       }
       print_c(n);
   }

   //void draw() const {

   //}
   void print_c(int n)
   {
       cout << "ChessBoard representation" << endl;
       for (int x =0; x < n; ++x){
          for(int j = 0; j < n; ++j){
              cout << b[x][j] << " ";
          }
          cout << endl;
       }
   }
   bool free(int row, int column) {
       for(int i=0; i < row; ++i){
           if (b[i][column]) return false;
       }
       for(int j=0; j < column; ++j){
           if(b[row][j]) return false;
       }
       for (int i=row, j=column; i>=0 && j>=0; i--, j--)
          if (b[i][j]) //check whether there is queen in the left upper diagonal or not
             return false;
       for (int i=row, j=column; j>=0 && i<b.size(); i--, j++)
          if (b[i][j]) //check whether there is queen in the left lower diagonal or not
             return false;
       // check the diagonals now
       return true;
   }

   void put_q(int row, int column){
       b[row][column] = 1;
   }

   void remove_q(int row, int column){
       b[row][column] = 0;
   }
};

bool attempt(int row, Board& board, int size){
    int i;
    if (row == size) return true;
    else{
        for (i = 0; i < size; ++i){
            if (board.free(row, i)){
                board.put_q(row, i);
                bool s = attempt(row+1, board, size);
                if(s) return true;
                else board.remove_q(row, i);
            }
        }
        return false;
    }
}

int main(){
    int N;
    cout << "Enter the number of Queens: ";
    cin >> N;
    Board ChessBoard(N);
    attempt(0, ChessBoard, N);
    ChessBoard.print_c(N);
;
}
