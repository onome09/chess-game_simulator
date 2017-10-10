#include<iostream>
#include"castle.h"
#include"move_list.h"

/*Function examines at the potential move and returns the type of move from the defined move list if the piece can do it */
int Castle::make_move(char* new_position)
{
  char new_file = new_position[0];
  char new_rank = new_position[1];

  if (new_file == file)
    return BIDIRECTIONAL_VERTICAL_MOVE_ONE_OR_MORE_SPACES;

  if (new_rank == rank)
    return BIDIRECTIONAL_HORIZONTAL_MOVE_ONE_OR_MORE_SPACES;
  return INVALID_MOVE;
}
