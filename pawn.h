/*This is the class creation of a Pawn which is derived from the Piece class*/
#include"piece.h"
#include<string>

using namespace std;

#ifndef PAWN_H
#define PAWN_H

class Pawn :public Piece
{
  /* Further information about the pawn including its name and its starting position by rank and file*/
 private:
  string name;
  char starting_rank;
  char starting_file;
 public:
  /*Pawn class constructor*/
 Pawn(char initial_rank, char initial_file, int team_colour):Piece(initial_rank, initial_file, team_colour){name = "Pawn";
    starting_rank = initial_rank; starting_file = initial_file; }
  /*Function declaration to check if the Pawn is able to move in a specific format */
  int make_move(char* new_position);
  /*Function declaration return the name of the piece which Pawn */
  string get_id(){return name;}
  char get_symbol(){return 'P';}
  /*virtual Pawn class destructor*/
  virtual ~Pawn(){}
};


#endif
