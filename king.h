/*This is the class creation of a King which is derived from the Piece class*/
#include"piece.h"
#include<string>
#include<iostream>

using namespace std;

#ifndef KING_H
#define KING_H

class King :public Piece
{
  /* Further information about the king including its name*/
 private:
  string name;

 public:
  /*King constructor*/
 King(char inital_rank, char initial_file, int team_colour):Piece(inital_rank, initial_file, team_colour){name = "King";}
  /*Function declaration to check if the king is able to move in a specific format */
  int make_move(char* new_position);
  /*Function declaration return the name of the piece which is king*/
  string get_id(){return name;}
  char get_symbol(){return 'K';}
  /*Virtual king destructor */
  virtual ~King(){}
};

#endif
