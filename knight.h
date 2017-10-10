/*This is the class creation of a Knight which is derived from the Piece class*/
#include"piece.h"

#ifndef KNIGHT_H
#define KNIGHT_H

class Knight :public Piece
{
  /* Further information about the knight including its name*/
 private:
  string name;
 public:
  /*Knight constructor*/
 Knight(char inital_rank, char initial_file, int team_colour):Piece(inital_rank, initial_file, team_colour){name = "Knight";}
  /*Function declaration to check if the knight is able to move in a specific format */
  int make_move(char* new_position);
  /*Function declaration return the name of the piece which is Knight*/
  string get_id(){return name;}
  char get_symbol(){return 'H';}
  /*Virtual Knight destructor*/
  virtual ~Knight(){}
};

#endif
