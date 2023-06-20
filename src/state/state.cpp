#include <iostream>
#include <sstream>
#include <cstdint>

#include "./state.hpp"
#include "../config.hpp"

#include <fstream>
//std::ofstream qout("Eval.txt", std::ios::app);

//second commit
//yey


/**
 * @brief evaluate the state
 * 
 * @return int 
 */
int State::evaluate(){
  int score = 0;
  //int pieceValues[7] = { 0, 100,500,  320, 330,900, 0};  // Piece values 
  //int pieceValues[7] = { 0, 2,6,  7, 8,20, 1000};  // Piece values 
  int pieceValues[7] = { 0, 4,70,  50, 30,350, 1000};
  /*piece id :
  0=empty, 1=pawn, 2=rook, 3=knight, 4=bishop, 5=queen, 6=king
  Queen=20, Bishop=8, Knight=7, Rook=6, Pawn=2.
  */
  int pawnSquareTable[6][5] = { //white
    { 0,  0,  0,  0,  0},
    {70, 70, 70, 70, 70},
    {10, 40, 40, 40, 10},
    {20, 25, 25, 25, 0},
    {-10, -20, 15, -20,5},
    { 0,  0,  0,  0,  0}
  };

  int rookSquareTable[6][5] = { //white
    {0, 0, 0, 0, 0},
    {10, 10, 10, 10, 5},
    {-5, 0, 0, 0, -5},
    {-5, 0, 0, 0, -5},
    {-5, 0, 0, 0,-5},
    {0, 0, 5, 0, 0}
  };

  int knightSquareTable[6][5] = { //white
    {-50, -40, -30, -40, -50},
    {-40, 0, 15, 0, -40},
    {-30, 15, 20, 10, -30},
    {-30, 10,20, 10, -30},
    {-40, -10, 5, -10,-40},
    {-50, -40, -30, -40, -50}
  };

  int bishopSquareTable[6][5] = { //white
    {-20, -10, -10, -10, -20},
    {-10, 0, 0, 0, -10},
    {-10, 10, 0, 10, -10},
    {-10, 0,10, 0, -10},
    {-10, 5, 0, 5,-10},
    {-20, -10, -10, -10, -20}
  };

  int queenSquareTable[6][5] = { //white
    {-20, -10, -5, -10, -20},
    {-10, 0, 0, -30, -10},
    {-5, 0, 5, 5, -5},
    {-5, 0,5, 10, -5},
    {-10, 0, 0, 5,-10},
    {-20, -10, -5, -10, -20}
  };

  int kingSquareTableMid[6][5] = { //white
    {-30, -40, -50, -40, -30},
    {-30, -40, -50, -40, -30},
    {-20, -30, -40, -30, -20},
    {-10, -20,-20, -20, -10},
    {20, 0, 0, 0,20},
    {20, 30,10, 30, 20}
  };

  int kingSquareTableEnd[6][5] = { //white
    {-50, -30, -30, -30, -50},
    {-30, -10, 0, -10, -30},
    {-30, 10, 30, 10, -30},
    {-30, 20,40, 20, -30},
    {-30, 0, 0, 0,-30},
    {-50, -30,-30, -30, -50}
  };


//////////////////////////////////////////BLACK
  int BpawnSquareTable[6][5] = { //black
    { 0,  0,  0,  0,  0},
    {5, -20, 5, -20, -10},
    {0, 25, 25, 25, 20},
    {10, 40, 40,40, 10},
    {70, 70, 70, 70,70},
    { 0,  0,  0,  0,  0}
  };

  int BrookSquareTable[6][5] = { //black
    {0, 0, 5, 0, 0},
    {-5, 0, 0, 0, -5},
    {-5, 0, 0, 0, -5},
    {-5, 0, 0, 0, -5},
    {5, 10, 10, 10, 10},
    {0, 0, 0, 0, 0}
  };

  int BknightSquareTable[6][5] = { //black
    {-50, -40, -30, -40, -50},//
    {-40, -10, 5, -10, -40}, //
    {-30, 10, 20, 10, -30}, //
    {-30, 10,20, 15, -30},
    {-40, 0, 15, 0,-40},//
    {-50, -40, -30, -40, -50}//
  };

  int BbishopSquareTable[6][5] = { //black
    {-20, -10, -10, -10, -20},//
    {-10, 5, 0, 5, -10},//
    {-10, 0, 10, 0, -10},//
    {-10, 10,0, 10, -10},//
    {-10, 0, 0, 0,-10},//
    {-20, -10, -10, -10, -20}//
  };

  int BqueenSquareTable[6][5] = { //white
    {-20, -10, -5, -10, -20},//
    {-10, 5, 0, 0, -10},
    {-5, 10, 5, 0, -5},
    {-5, 5,5, 0, -5},
    {-10, 0, 0, 0,-10},
    {-20, -10, -5, -10, -20}//
  };

  int BkingSquareTableMid[6][5] = { //black
    {20, 30, 10, 30, 20},//
    {20, 0, 0, 0, 20},//
    {-10, -20, -20, -20, -10},
    {-20, -30,-40, -30, -20},
    {-30, -40, -50, -40,-30},
    {-30, -40,-50, -40, -30}
  };

  int BkingSquareTableEnd[6][5] = { //black
    {-50, -30, -30, -30, -50},
    {-30, 0, 0, 0, -30},
    {-30, 20, 40, 20, -30},
    {-30, 10,30, 10, -30},
    {-30, -10, 0, -10,-30},
    {-50, -30,-30, -30, -50}
  };
  


int total_pieces=0;
  // Calculate the score based on the pieces on the board
  for (int i = 0; i < BOARD_H; i++) {
    for (int j = 0; j < BOARD_W; j++) {
      int piece = this->board.board[this->player][i][j];  // White pieces
      //based on the material
      if (piece > 0) {
        score += pieceValues[piece];
        //total_pieces++;
      }

      // if (piece ==6){
      //   if (i-1>=0 && this->board.board[1-this->player][i-1][j]==1) score-=50;
      //   if (i+1<=5 && this->board.board[1-this->player][i+1][j]==1) score-=50;
      //   if (j-1>=0 && this->board.board[1-this->player][i][j-1]==1) score-=50;
      //   if (j+1<=5 &&this->board.board[1-this->player][i][j+1]==1) score-=50;
      //   if (i-1>=0 && j-1>=0 &&this->board.board[1-this->player][i-1][j-1]==1) score-=50;
      //   if (i-1>=0 && j+1<=5 &&this->board.board[1-this->player][i-1][j+1]==1) score-=50;
      //   if (i+1<=5 && j-1>=0 && this->board.board[1-this->player][i+1][j-1]==1) score-=50;
      //   if (i+1<=5 &&j+1<=5 &&this->board.board[1-this->player][i+1][j+1]==1) score-=50;
      //   //if (i==5 && j==4) score+=2;
      // }
      // if (piece ==5){
      //   if (i-1>=0 && this->board.board[1-this->player][i-1][j]==1) score-=50;
      //   if (i+1<=5 && this->board.board[1-this->player][i+1][j]==1) score-=50;
      //   if (j-1>=0 && this->board.board[1-this->player][i][j-1]==1) score-=50;
      //   if (j+1<=5 &&this->board.board[1-this->player][i][j+1]==1) score-=50;
      //   if (i-1>=0 && j-1>=0 &&this->board.board[1-this->player][i-1][j-1]==1) score-=50;
      //   if (i-1>=0 && j+1<=5 &&this->board.board[1-this->player][i-1][j+1]==1) score-=50;
      //   if (i+1<=5 && j-1>=0 && this->board.board[1-this->player][i+1][j-1]==1) score-=50;
      //   if (i+1<=5 &&j+1<=5 &&this->board.board[1-this->player][i+1][j+1]==1) score-=50;
      // }

      // if (piece ==4||piece ==3||piece==2){
      //   if (i-1>=0 && this->board.board[1-this->player][i-1][j]==1) score-=20;
      //   if (i+1<=5 && this->board.board[1-this->player][i+1][j]==1) score-=20;
      //   if (j-1>=0 && this->board.board[1-this->player][i][j-1]==1) score-=20;
      //   if (j+1<=5 &&this->board.board[1-this->player][i][j+1]==1) score-=20;
      //   if (i-1>=0 && j-1>=0 &&this->board.board[1-this->player][i-1][j-1]==1) score-=20;
      //   if (i-1>=0 && j+1<=5 &&this->board.board[1-this->player][i-1][j+1]==1) score-=20;
      //   if (i+1<=5 && j-1>=0 && this->board.board[1-this->player][i+1][j-1]==1) score-=20;
      //   if (i+1<=5 &&j+1<=5 &&this->board.board[1-this->player][i+1][j+1]==1) score-=20;
      // }

      // if (piece ==1){
      //   if (i-1>=0 && this->board.board[1-this->player][i-1][j]==1) score-=5;
      //   if (i+1<=5 && this->board.board[1-this->player][i+1][j]==1) score-=5;
      //   if (j-1>=0 && this->board.board[1-this->player][i][j-1]==1) score-=5;
      //   if (j+1<=5 &&this->board.board[1-this->player][i][j+1]==1) score-=5;
      //   if (i-1>=0 && j-1>=0 &&this->board.board[1-this->player][i-1][j-1]==1) score-=5;
      //   if (i-1>=0 && j+1<=5 &&this->board.board[1-this->player][i-1][j+1]==1) score-=5;
      //   if (i+1<=5 && j-1>=0 && this->board.board[1-this->player][i+1][j-1]==1) score-=5;
      //   if (i+1<=5 &&j+1<=5 &&this->board.board[1-this->player][i+1][j+1]==1) score-=5;
      // }

       

      // if (piece == 1) { // Pawn
      //     score += pawnSquareTable[i][j];
      // }

      // if (piece == 2) { // rook
      //     score += rookSquareTable[i][j];
      // }

      // if (piece == 3) { // knight
      //     score += knightSquareTable[i][j];
      // }

      // if (piece == 4) { // bishop
      //     score += bishopSquareTable[i][j];
      // }

      // if (piece == 5) { // queen
      //     score += queenSquareTable[i][j];
      // }

      // if (piece == 6) { // king
      //     score += kingSquareTableMid[i][j];
      // }



      piece = this->board.board[1-this->player][i][j];  // Black pieces
      //based on the material
      if (piece > 0) {
        score -= pieceValues[piece];
        //total_pieces++;
      }

      // if (piece == 1) { // Pawn
      //     score -= BpawnSquareTable[i][j];
      // }

      // if (piece == 2) { // rook
      //     score -= BrookSquareTable[i][j];
      // }

      // if (piece == 3) { // knight
      //     score -= BknightSquareTable[i][j];
      // }

      // if (piece == 4) { // bishop
      //     score -= BbishopSquareTable[i][j];
      // }

      // if (piece == 5) { // queen
      //     score -= BqueenSquareTable[i][j];
      // }

      // if (piece == 6) { // king
      //     score -= BkingSquareTableMid[i][j];
      // }

      // if (piece == 2) { // rook
      // int x=j;
      // int y=i;
      // while(x<=5){
      //   x+=1;
      //   if(this->board.board[1-this->player][y][x]>0){
      //     break;
      //   }
      //   if(this->board.board[this->player][y][x]>0){
      //     int barang=this->board.board[this->player][y][x];
      //     score-=pieceValues[barang];
      //     break;
      //   }
      // }

      // x=j;
      // y=i;
      // while(x>=0){
      //   x-=1;
      //   if(this->board.board[1-this->player][y][x]>0){
      //     break;
      //   }
      //   if(this->board.board[this->player][y][x]>0){
      //     int barang=this->board.board[this->player][y][x];
      //     score-=pieceValues[barang];
      //     break;
      //   }
      // }

      // x=j;
      // y=i;
      // while(y>=0){
      //   y-=1;
      //   if(this->board.board[1-this->player][y][x]>0){
      //     break;
      //   }
      //   if(this->board.board[this->player][y][x]>0){
      //     int barang=this->board.board[this->player][y][x];
      //     score-=pieceValues[barang];
      //     break;
      //   }
      // }

      // x=j;
      // y=i;
      // while(y<=6){
      //   y+=1;
      //   if(this->board.board[1-this->player][y][x]>0){
      //     break;
      //   }
      //   if(this->board.board[this->player][y][x]>0){
      //     int barang=this->board.board[this->player][y][x];
      //     score-=pieceValues[barang];
      //     break;
      //   }
      // }

      // }


      // if (piece == 5) { // queen
      // int x=j;
      // int y=i;
      // while(x<=5 && y<=6){ //down right diagonal
      //   x+=1;
      //   y+=1;
      //   if(this->board.board[1-this->player][y][x]>0){
      //     break;
      //   }
      //   if(this->board.board[this->player][y][x]>0){
      //     int barang=this->board.board[this->player][y][x];
      //     score-=pieceValues[barang];
      //     break;
      //   }
      // }
      // x=j;
      // y=i;

      // while(x>=0 && y>=0){ //up-left diagonal
      //   x-=1;
      //   y-=1;
      //   if(this->board.board[1-this->player][y][x]>0){
      //     break;
      //   }
      //   if(this->board.board[this->player][y][x]>0){
      //     int barang=this->board.board[this->player][y][x];
      //     score-=pieceValues[barang];
      //     break;
      //   }
      // }

      // x=j;
      // y=i;
      // while(x<=5 && y>=0){ //up-right diagonal
      //   x+=1;
      //   y-=1;
      //   if(this->board.board[1-this->player][y][x]>0){
      //     break;
      //   }
      //   if(this->board.board[this->player][y][x]>0){
      //     int barang=this->board.board[this->player][y][x];
      //     score-=pieceValues[barang];
      //     break;
      //   }
      // }

      // x=j;
      // y=i;
      // while(x>=0 && y<=6){ //down-left diagonal
      //   x-=1;
      //   y+=1;
      //   if(this->board.board[1-this->player][y][x]>0){
      //     break;
      //   }
      //   if(this->board.board[this->player][y][x]>0){
      //     int barang=this->board.board[this->player][y][x];
      //     score-=pieceValues[barang];
      //     break;
      //   }
      // }


      // x=j;
      // y=i;
      // while(x<=5){
      //   x+=1;
      //   if(this->board.board[1-this->player][y][x]>0){
      //     break;
      //   }
      //   if(this->board.board[this->player][y][x]>0){
      //     int barang=this->board.board[this->player][y][x];
      //     score-=pieceValues[barang];
      //     break;
      //   }
      // }

      // x=j;
      // y=i;
      // while(x>=0){
      //   x-=1;
      //   if(this->board.board[1-this->player][y][x]>0){
      //     break;
      //   }
      //   if(this->board.board[this->player][y][x]>0){
      //     int barang=this->board.board[this->player][y][x];
      //     score-=pieceValues[barang];
      //     break;
      //   }
      // }

      // x=j;
      // y=i;
      // while(y>=0){
      //   y-=1;
      //   if(this->board.board[1-this->player][y][x]>0){
      //     break;
      //   }
      //   if(this->board.board[this->player][y][x]>0){
      //     int barang=this->board.board[this->player][y][x];
      //     score-=pieceValues[barang];
      //     break;
      //   }
      // }

      // x=j;
      // y=i;
      // while(y<=6){
      //   y+=1;
      //   if(this->board.board[1-this->player][y][x]>0){
      //     break;
      //   }
      //   if(this->board.board[this->player][y][x]>0){
      //     int barang=this->board.board[this->player][y][x];
      //     score-=pieceValues[barang];
      //     break;
      //   }
      // }
      // }





      // if (piece==4){ //bishop
      // int x=j;
      // int y=i;
      // while(x<=5 && y<=6){ //down right diagonal
      //   x+=1;
      //   y+=1;
      //   if(this->board.board[1-this->player][y][x]>0){
      //     break;
      //   }
      //   if(this->board.board[this->player][y][x]>0){
      //     int barang=this->board.board[this->player][y][x];
      //     score-=pieceValues[barang];
      //     break;
      //   }
      // }
      // x=j;
      // y=i;

      // while(x>=0 && y>=0){ //up-left diagonal
      //   x-=1;
      //   y-=1;
      //   if(this->board.board[1-this->player][y][x]>0){
      //     break;
      //   }
      //   if(this->board.board[this->player][y][x]>0){
      //     int barang=this->board.board[this->player][y][x];
      //     score-=pieceValues[barang];
      //     break;
      //   }
      // }

      // x=j;
      // y=i;
      // while(x<=5 && y>=0){ //up-right diagonal
      //   x+=1;
      //   y-=1;
      //   if(this->board.board[1-this->player][y][x]>0){
      //     break;
      //   }
      //   if(this->board.board[this->player][y][x]>0){
      //     int barang=this->board.board[this->player][y][x];
      //     score-=pieceValues[barang];
      //     break;
      //   }
      // }

      // x=j;
      // y=i;
      // while(x>=0 && y<=6){ //down-left diagonal
      //   x-=1;
      //   y+=1;
      //   if(this->board.board[1-this->player][y][x]>0){
      //     break;
      //   }
      //   if(this->board.board[this->player][y][x]>0){
      //     int barang=this->board.board[this->player][y][x];
      //     score-=pieceValues[barang];
      //     break;
      //   }
      // }




      // }

     }
   }
  //`qout<<"score= "<<score<<" lala"<<std::endl;

  // if (total_pieces<=9){
  // for (int i = 0; i < BOARD_H; i++) {
  //   for (int j = 0; j < BOARD_W; j++) {
  //     int piece = this->board.board[0][i][j];  // White pieces
  //     //based on the material
  //     if (piece == 6) { // king
  //         score -= kingSquareTableMid[i][j];
  //         score +=kingSquareTableEnd[i][j];
  //     }

  //     piece = this->board.board[1][i][j];  // Black pieces
  //     if (piece == 6) { // king
  //         score += BkingSquareTableMid[i][j];
  //         score-=BkingSquareTableEnd[i][j];
        
  //     }
  // }
  // }
  // }

  return score;
}


/**
 * @brief return next state after the move
 * 
 * @param move 
 * @return State* 
 */
State* State::next_state(Move move){
  Board next = this->board;
  Point from = move.first, to = move.second;
  
  int8_t moved = next.board[this->player][from.first][from.second];
  //promotion for pawn
  if(moved == 1 && (to.first==BOARD_H-1 || to.first==0)){
    moved = 5;
  }
  if(next.board[1-this->player][to.first][to.second]){
    next.board[1-this->player][to.first][to.second] = 0;
  }
  
  next.board[this->player][from.first][from.second] = 0;
  next.board[this->player][to.first][to.second] = moved;
  
  State* next_state = new State(next, 1-this->player);
  
  if(this->game_state != WIN)
    next_state->get_legal_actions();
  return next_state;
}


static const int move_table_rook_bishop[8][7][2] = {
  {{0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {0, 7}},
  {{0, -1}, {0, -2}, {0, -3}, {0, -4}, {0, -5}, {0, -6}, {0, -7}},
  {{1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}},
  {{-1, 0}, {-2, 0}, {-3, 0}, {-4, 0}, {-5, 0}, {-6, 0}, {-7, 0}},
  {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}},
  {{1, -1}, {2, -2}, {3, -3}, {4, -4}, {5, -5}, {6, -6}, {7, -7}},
  {{-1, 1}, {-2, 2}, {-3, 3}, {-4, 4}, {-5, 5}, {-6, 6}, {-7, 7}},
  {{-1, -1}, {-2, -2}, {-3, -3}, {-4, -4}, {-5, -5}, {-6, -6}, {-7, -7}},
};
static const int move_table_knight[8][2] = {
  {1, 2}, {1, -2},
  {-1, 2}, {-1, -2},
  {2, 1}, {2, -1},
  {-2, 1}, {-2, -1},
};
static const int move_table_king[8][2] = {
  {1, 0}, {0, 1}, {-1, 0}, {0, -1}, 
  {1, 1}, {1, -1}, {-1, 1}, {-1, -1},
};


/**
 * @brief get all legal actions of now state
 * 
 */
void State::get_legal_actions(){
  // [Optional]
  // This method is not very efficient
  // You can redesign it
  this->game_state = NONE;
  std::vector<Move> all_actions;
  auto self_board = this->board.board[this->player];
  auto oppn_board = this->board.board[1 - this->player];
  
  int now_piece, oppn_piece;
  for(int i=0; i<BOARD_H; i+=1){
    for(int j=0; j<BOARD_W; j+=1){
      if((now_piece=self_board[i][j])){
        // std::cout << this->player << "," << now_piece << ' ';
        switch (now_piece){
          case 1: //pawn
            if(this->player && i<BOARD_H-1){
              //black
              if(!oppn_board[i+1][j] && !self_board[i+1][j])
                all_actions.push_back(Move(Point(i, j), Point(i+1, j)));
              if(j<BOARD_W-1 && (oppn_piece=oppn_board[i+1][j+1])>0){
                all_actions.push_back(Move(Point(i, j), Point(i+1, j+1)));
                if(oppn_piece==6){
                  this->game_state = WIN;
                  this->legal_actions = all_actions;
                  return;
                }
              }
              if(j>0 && (oppn_piece=oppn_board[i+1][j-1])>0){
                all_actions.push_back(Move(Point(i, j), Point(i+1, j-1)));
                if(oppn_piece==6){
                  this->game_state = WIN;
                  this->legal_actions = all_actions;
                  return;
                }
              }
            }else if(!this->player && i>0){
              //white
              if(!oppn_board[i-1][j] && !self_board[i-1][j])
                all_actions.push_back(Move(Point(i, j), Point(i-1, j)));
              if(j<BOARD_W-1 && (oppn_piece=oppn_board[i-1][j+1])>0){
                all_actions.push_back(Move(Point(i, j), Point(i-1, j+1)));
                if(oppn_piece==6){
                  this->game_state = WIN;
                  this->legal_actions = all_actions;
                  return;
                }
              }
              if(j>0 && (oppn_piece=oppn_board[i-1][j-1])>0){
                all_actions.push_back(Move(Point(i, j), Point(i-1, j-1)));
                if(oppn_piece==6){
                  this->game_state = WIN;
                  this->legal_actions = all_actions;
                  return;
                }
              }
            }
            break;
          
          case 2: //rook
          case 4: //bishop
          case 5: //queen
            int st, end;
            switch (now_piece){
              case 2: st=0; end=4; break; //rook
              case 4: st=4; end=8; break; //bishop
              case 5: st=0; end=8; break; //queen
              default: st=0; end=-1;
            }
            for(int part=st; part<end; part+=1){
              auto move_list = move_table_rook_bishop[part];
              for(int k=0; k<std::max(BOARD_H, BOARD_W); k+=1){
                int p[2] = {move_list[k][0] + i, move_list[k][1] + j};
                
                if(p[0]>=BOARD_H || p[0]<0 || p[1]>=BOARD_W || p[1]<0) break;
                now_piece = self_board[p[0]][p[1]];
                if(now_piece) break;
                
                all_actions.push_back(Move(Point(i, j), Point(p[0], p[1])));
                
                oppn_piece = oppn_board[p[0]][p[1]];
                if(oppn_piece){
                  if(oppn_piece==6){
                    this->game_state = WIN;
                    this->legal_actions = all_actions;
                    return;
                  }else
                    break;
                };
              }
            }
            break;
          
          case 3: //knight
            for(auto move: move_table_knight){
              int x = move[0] + i;
              int y = move[1] + j;
              
              if(x>=BOARD_H || x<0 || y>=BOARD_W || y<0) continue;
              now_piece = self_board[x][y];
              if(now_piece) continue;
              all_actions.push_back(Move(Point(i, j), Point(x, y)));
              
              oppn_piece = oppn_board[x][y];
              if(oppn_piece==6){
                this->game_state = WIN;
                this->legal_actions = all_actions;
                return;
              }
            }
            break;
          
          case 6: //king
            for(auto move: move_table_king){
              int p[2] = {move[0] + i, move[1] + j};
              
              if(p[0]>=BOARD_H || p[0]<0 || p[1]>=BOARD_W || p[1]<0) continue;
              now_piece = self_board[p[0]][p[1]];
              if(now_piece) continue;
              
              all_actions.push_back(Move(Point(i, j), Point(p[0], p[1])));
              
              oppn_piece = oppn_board[p[0]][p[1]];
              if(oppn_piece==6){
                this->game_state = WIN;
                this->legal_actions = all_actions;
                return;
              }
            }
            break;
        }
      }
    }
  }
  //std::cout << "\n";
  this->legal_actions = all_actions;
}


const char piece_table[2][7][5] = {
  {" ", "♙", "♖", "♘", "♗", "♕", "♔"},
  {" ", "♟", "♜", "♞", "♝", "♛", "♚"}
};
/**
 * @brief encode the output for command line output
 * 
 * @return std::string 
 */
std::string State::encode_output(){
  std::stringstream ss;
  int now_piece;
  for(int i=0; i<BOARD_H; i+=1){
    for(int j=0; j<BOARD_W; j+=1){
      if((now_piece = this->board.board[0][i][j])){
        ss << std::string(piece_table[0][now_piece]);
      }else if((now_piece = this->board.board[1][i][j])){
        ss << std::string(piece_table[1][now_piece]);
      }else{
        ss << " ";
      }
      ss << " ";
    }
    ss << "\n";
  }
  return ss.str();
}


/**
 * @brief encode the state to the format for player
 * 
 * @return std::string 
 */
std::string State::encode_state(){
  std::stringstream ss;
  ss << this->player;
  ss << "\n";
  for(int pl=0; pl<2; pl+=1){
    for(int i=0; i<BOARD_H; i+=1){
      for(int j=0; j<BOARD_W; j+=1){
        ss << int(this->board.board[pl][i][j]);
        ss << " ";
      }
      ss << "\n";
    }
    ss << "\n";
  }
  return ss.str();
}
