#include"piece.h"
#include<string>


using namespace std;

Piece::Piece(char initial_rank, char initial_file, int team_colour)
{
  file = initial_file;
  rank = initial_rank;
  team = team_colour;
}

void Piece::set_position(string new_position)
{
  file = new_position.at(0);
  rank = new_position.at(1);
}
