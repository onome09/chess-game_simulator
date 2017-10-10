/*This is the class creation of a Bishop which is derived from the Piece class*/
#include"piece.h"
#include<string>

using namespace std;

#ifndef BISHOP_H
#define BISHOP_H

class Bishop :public Piece
{
  /* Further information about the bishop including its name*/
 private:
  string name;
 public:
  /*Bishop class constructor*/
 Bishop(char inital_rank, char initial_file, int team_colour):Piece(inital_rank, initial_file, team_colour){ name = "Bishop";}
  /*Function declaration to check if the Bishop is able to move in a specific format */
  int make_move(char* new_position);
  /*Function declaration return the name of the piece which Bishop */
  string get_id(){return name;}
  char get_symbol(){return 'B';}
  /*virtual Bishop class destructor*/
  virtual ~Bishop(){}
};

#endif
