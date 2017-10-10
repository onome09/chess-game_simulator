#include<iomanip>
#include"pawn.h"
#include"move_list.h"
#include<iostream>

using namespace std;
/*Function examines at the potential move and returns the type of move from the defined move list if the piece can do it */
int Pawn::make_move(char* new_position)
{
  char new_file = new_position[0];
  char new_rank = new_position[1];
  int y;
  if (team == 0)
    y = 1;
  else
    y = -1;
  
   if ((new_rank - rank) == y && new_file == file)
    {
       return UNIDIRECTIONAL_MOVE_ONE_SPACE_FORWARDS;
    }
  if ((new_rank - rank) == y && abs(new_file - file) == 1)
    {
      return BIDIRECTIONAL_MOVE_ONE_SPACE_DIAGONAL_FORWARDS;
    }
  if ((new_rank - rank) == 2 * y && new_file == file && starting_rank == rank && starting_file == file)
    {      
      return UNIDIRECTIONAL_MOVE_TWO_SPACES_FORWARDS;
    } 
  return INVALID_MOVE;
}
