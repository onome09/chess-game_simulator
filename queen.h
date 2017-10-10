/*This is the class creation of a Queen which is derived from the Piece class*/
#include"piece.h"
#include<string>

using namespace std;

#ifndef QUEEN_H
#define QUEEN_H

class Queen :public Piece
{
  /* Further information about the queen including its name*/
 private:
  string name;
 public:
  /*Queen constructor*/
 Queen(char inital_rank, char initial_file, int team_colour):Piece(inital_rank, initial_file, team_colour){name = "Queen";}
  /*Function declaration to check if the queen is able to move in a specific format */
  int make_move(char* new_position);
  /*Function declaration return the name of the piece which is queen*/
  string get_id(){return name;}
  char get_symbol(){return 'Q';}
  /*Virtual queen destructor */
  virtual ~Queen(){}
};

#endif
