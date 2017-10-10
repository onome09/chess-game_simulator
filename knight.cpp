#include<iostream>
#include<iomanip>
#include"knight.h"
#include"move_list.h"

using namespace std;
/*Function examines at the potential move and returns the type of move from the defined move list if the piece can do it */
int Knight::make_move(char* new_position)
{

  char new_file = new_position[0];
  char new_rank = new_position[1];
  if ((abs(new_file - file) == 2 && abs(new_rank - rank) == 1) || (abs(new_file - file) == 1 && abs(new_rank - rank) == 2))
    {
      return L_SHAPE_MOVE_CAN_JUMP_PIECES;
    }

  return INVALID_MOVE;
}
