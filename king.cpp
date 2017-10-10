#include<iomanip>
#include"king.h"
#include"move_list.h"

using namespace std;
/*Function examines at the potential move position and outputs the type of move from the defined move list if the piece can do it */
int King::make_move(char* new_position)
{
  if (abs(new_position[0] - file) < 2 && abs(new_position[1] - rank) < 2)
    {
    return MULTIDIRECTIONAL_MOVE_ONE_SPACES;
    }

 return INVALID_MOVE;
}
