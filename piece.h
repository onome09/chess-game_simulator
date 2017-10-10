/*This is the class creation of a board piece for the chessboard*/
#include<string>
#include<iostream>

using namespace std;

#ifndef PIECE_H
#define PIECE_H

class Piece
{
protected:
  /* Information about the piece including its coordinate on the board by file and rank and its team*/
  char rank;
  char file;
  int team; 
public:
  /*Piece constructor*/
  Piece(char inital_rank, char initial_file, int team_colour);
/*public functions to set the piece position variables to the values found in new_position and find the value of the team for the piece*/
  void set_position(string new_position);
  int get_colour() {return team;}

  /*Virtual function to check if a piece is able to move in a specific format */
  virtual int make_move(char* new_position)=0;
  /*Virtual function to check the name of a piece*/
  virtual string get_id()=0;
  virtual char get_symbol()=0;
  /*Virtual piece constructor*/
  virtual ~Piece(){}
};

#endif
