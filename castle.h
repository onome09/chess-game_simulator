/*This is the class creation of a Castle which is derived from the Piece class*/
#include"piece.h"
#include<string>

using namespace std;

#ifndef CASTLE_H
#define CASTLE_H

class Castle :public Piece
{
  /* Further information about the castle including its name*/
 private:
  string name;

 public:
  /*Castle constructor*/
 Castle(char inital_rank, char initial_file, int team_colour):Piece(inital_rank, initial_file, team_colour){ name = "Rook";}
  /*Function declaration to check if the Rook is able to move in a specific format */
  int make_move(char* new_position);
  /*Function declaration return the name of the piece which is Rook*/
  string get_id(){return name;}
  char get_symbol(){return 'C';}
  /*Virtual Castle destructor */
  virtual ~Castle(){}
};

#endif
