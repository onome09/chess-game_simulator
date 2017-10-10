/*This class declaration is for the creation of a Chessboard for the game of chess to be played on*/
#include<map>
#include<iomanip>
#include<string>
#include"piece.h"
#include"king.h"
#include"queen.h"
#include"castle.h"
#include"bishop.h"
#include"knight.h"
#include"pawn.h"

using namespace std;

#ifndef BOARD_H
#define BOARD_H

class Board
{
  /*Declaration of a function which initialises pieces on the board, whose turn it is, and the starting king positions*/
  void set();
  /*Information about the class including whose turn it is to make a move*/
  int turn;
  /*An array to monitor the position of both kings forst two members of array are the whites position by file and rank and the next 2 members are for the black*/
  char king_position[4];
  /*A map to associate a team with a colour*/
  map <int, string> colour; 
  /*A map to associate a position which is of string type with a pointer to a piece on the board in that position*/
  map <string, Piece*> board_pieces;
  /*Declaration for a function which returns the effects of a move once it is made*/
  int result(char *king_position, int team);
  /*Declaration of a function which checks whether a king of the team is in check*/
  bool check(char *king_position, int team);
  /*Declaration of a function which checks if a submitted move is valid*/
  int check_move(string old_position, string new_position, int turn_flag);
  /*Declaration of a function which checks the validity of a move in terms of the board size, whose turn it is etc*/
  int validity_checks(string old_position, string new_position, char *old_coordinates, char *new_coordinates, int turn_flag);
  /*Declaration of a function which checks the legality of whether a piece is in the way or it will try to replace a piece of its own team etc*/
  int legal_checks(string old_position, string new_position, char *old_coordinates, char *new_coordinates);
  /*Declaration of a function which adds two characters together to form a string*/
  string add(char one, char two);
public:
  /*Board class constructor*/
  Board();
  /*Declaration of a function which moves a piece from old position to new position if it is valid and legal*/
  void submitMove(string old_position, string new_position);
  /*Function to display the board*/
  void display_board();
  /*Function to reset the Chessboard*/
  void resetBoard();
  /*Board class destructor*/
  ~Board();
};

#endif
