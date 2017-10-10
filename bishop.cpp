#include"bishop.h"
#include"move_list.h"
#include<iostream>
/*Function examines at the potential move and returns the type of move from the defined move list if the piece can do it */
int Bishop::make_move(char* new_position)
{
  char new_file = new_position[0];
  char new_rank = new_position[1];
//cout << new_file - file << " " << new_rank - rank<< endl;
  if ((new_file - file) == (new_rank - rank))
    {//std::cout << "cool";
    return BIDIRECTIONAL_45_OR_225_DEGREES_MOVE_ONE_OR_MORE_SPACES;
    }
  if ((file - new_file) == (new_rank - rank))
    {
      return BIDIRECTIONAL_135_OR_315_DEGREE_MOVE_ONE_OR_MORE_SPACES;
    }
  return INVALID_MOVE;
}
