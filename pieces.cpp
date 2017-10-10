#include<string>
#include<iostream>
#include <map>
#include <iomanip>

using namespace std;
string add(char one, char two);


piece::piece(char initial_rank, char initial_file, int team_colour)
{
  file = initial_file;
  rank = initial_rank;
  team = (colour)team_colour;
}
/***********************************************************************************************************/
class king :public piece
{
public:
  king(char inital_rank, char initial_file, int team_colour):piece(inital_rank, initial_file, team_colour){}
  int make_move(char* new_position);
  char get_id(){return 'K';}
  virtual ~king(){}
};

int king::make_move(char* new_position)
{
  char new_file = new_position[1];
  char new_rank = new_position[0];

  if (abs(new_file - file) < 2 || abs(new_rank - rank) < 2)
    return 0;
  return 1;
}



/***********************************************************************************************************/
class queen :public piece
{

public:
  queen(char inital_rank, char initial_file, int team_colour):piece(inital_rank, initial_file, team_colour){}
  int make_move(char* new_position);
  char get_id(){return 'Q';}
  virtual ~queen(){}
};

int queen::make_move(char* new_position)
{
  char new_file = new_position[1];
  char new_rank = new_position[0];

  if (new_file == file)  
    return 2;
  if (new_rank == rank)
    return 3;
  if ((new_file - file) == (new_rank - rank)) 
    return 4;   
  if ((file - new_file) == (new_rank - rank))
    return 5;
return false;
}
/***********************************************************************************************************/
class castle :public piece
{
  
public:
  castle(char inital_rank, char initial_file, int team_colour):piece(inital_rank, initial_file, team_colour){}
  int make_move(char* new_position);
  char get_id(){return 'C';}
  virtual ~castle(){}
};

int castle::make_move(char* new_position)
{
  char new_file = new_position[1];
  char new_rank = new_position[0];

  if (new_file == file)
    return 2;

  if (new_rank == rank)
    return 3;
  return false;
}
/***********************************************************************************************************/
class bishop :public piece
{
 
public:
  bishop(char inital_rank, char initial_file, int team_colour):piece(inital_rank, initial_file, team_colour){}
  int make_move(char* new_position);
  char get_id(){return 'B';}
  virtual ~bishop(){}
};

int bishop::make_move(char* new_position)
{
  char new_file = new_position[1];
  char new_rank = new_position[0];

  if ((new_file - file) == (new_rank - rank))
    return 4;
  
  if ((file - new_file) == (new_rank - rank))
    return 5;
  return false;
}
/***********************************************************************************************************/
class knight :public piece
{

public:
  knight(char inital_rank, char initial_file, int team_colour):piece(inital_rank, initial_file, team_colour){}
  int make_move(char* new_position);
  char get_id(){return 'k';}
  virtual ~knight(){}
};

int knight::make_move(char* new_position)
{
  char new_file = new_position[1];
  char new_rank = new_position[0];
  
  if ((abs(new_file - file) == 2 && abs(new_rank - rank) == 1) || (abs(new_file - file) == 1 && abs(new_rank - rank) == 2))
    {
      return 1;
    }
  return 0;
}
/***********************************************************************************************************/
class pawn :public piece
{
public:
  pawn(char inital_rank, char initial_file, int team_colour):piece(inital_rank, initial_file, team_colour){}
  int make_move(char* new_position);
  char get_id(){return 'P';}
  virtual ~pawn(){}
};

int pawn::make_move(char* new_position)
{
  char new_file = new_position[1];
  char new_rank = new_position[0];
  int y;
  
  if (team == 0)
    y = 1;
  else
    y = -1;

   if ((new_rank - rank) == 1*y && new_file == file)
    {
       return 7;
    }
  if ((new_rank - rank) == 1*y && abs(new_file - file) == 1)
    {
      return 6;
    }
   return 0;
}
/***********************************************************************************************************/
class board
{
  map <string, piece*> board_pieces;
public:
  board();
  bool check_move(char* old_position, char* new_position);
  void display_board();
  void submit_move(string old_pos, string new_pos);
  //  ~board();
};


int main()
{
  board test_board;
  test_board.display_board();
  test_board.submit_move("a2","a3");
  test_board.display_board();
  test_board.submit_move("b7","a6");
  test_board.display_board();
  test_board.submit_move("a3","a4");
  test_board.display_board();
  test_board.submit_move("a4","a5");
  test_board.display_board(); 
  test_board.submit_move("a5","a6");
  test_board.display_board();
  //test_board.submit_move("b7","a6");
  test_board.display_board();
  test_board.submit_move("b8","a6");
  test_board.display_board();
  
}

board::board()
{
  string str = "";
  string position;

  for (char i = '3'; i < '6'; i++)
    {

      for(char j = 'a'; j < 'i'; j++)
      {
	board_pieces[add(j,i)] = NULL;
      } 
      
    }
  
  for (int i = 0; i < 2; i++)
    {
      char pawn_initial_rank = '2' + i*5;
      for (int j = 0; j < 8; j++)
	{
	  board_pieces[add(char(j + 97),char(pawn_initial_rank))] = new pawn(pawn_initial_rank, char(j+97), i);
	}
      int non_pawn_initial_rank = '1' + i*7;
      for (int j = 0; j < 2; j++)
	{
	  board_pieces[add(char(1 + 5 * j + 97),char(non_pawn_initial_rank))] = new knight(char(non_pawn_initial_rank), char(1 + 5 * j + 97), i);
	  board_pieces[add(char(2 + 3 * j + 97),char(non_pawn_initial_rank))] = new bishop(char(non_pawn_initial_rank), char(2 + 3 * j + 97), i);
	  board_pieces[add(char(7 * j + 97),char(non_pawn_initial_rank))] = new castle(char(non_pawn_initial_rank), char(7 * j + 97), i);
	}
      board_pieces[add('e',char(non_pawn_initial_rank))] = new queen(char(non_pawn_initial_rank), 'e', i);
      board_pieces[add('d',char(non_pawn_initial_rank))] = new king(char(non_pawn_initial_rank), 'd', i);
      
    }
  
     
}  


bool board::check_move(char* old_position, char* new_position)
{
  char old_file = old_position[1];
  char old_rank = old_position[0];
  char new_file = new_position[1];
  char new_rank = new_position[0];
  char test_file;
  char test_rank;
  char test_position[2];
  string test_pos;
  string old_pos = add(old_file,old_rank);
  string new_pos = add(new_file,new_rank);
  cout << old_file << old_rank << new_file << new_rank << endl;
  /*******************************check bounds*/
  if ((old_file > 'h') || (old_file < 'a') || (old_rank > '8') || (old_rank < '0') || (new_file > 'h') || (new_file < 'a') || (new_rank > '8') || (new_rank < '0'))
   {
     cout << "Invalid move out of bounds" << endl;
     return false;   
   }

  /********************************/
  if (board_pieces[old_pos] == NULL)
    {
      cout << " no piece here" << endl;
      return false;
    }
  int x;
  int valid = (board_pieces[old_pos]->make_move(new_position));
  switch (valid) 
    {
    case 0:
      cout << "invalid move cos the piece cant move like dat" << endl;
      return false;
      break;
    case 1:
      break;
    case 2:
      if (new_rank > old_rank)
	{
	  test_rank = old_rank + 1;
	  x = 1;
	}
      else
	{
	  test_rank = old_rank - 1;
	  x = -1;
	}
      while (test_rank != new_rank)
	{
	  test_position[0] = old_file;
	  test_position[1] = test_rank;
	  test_pos = add(test_position[0],test_position[1]);
	  if (board_pieces[test_pos] != NULL)
	    return false;
	  test_rank = test_rank + x;
	}
      break;
    case 3:
      if (new_file > old_file)
        {
          test_file = old_file + 1;
          x = 1;
        }
      else
	{
          test_file = old_file - 1;
          x = -1;
        }
      while (test_file != new_file)
        {
          test_position[0] = test_file;
          test_position[1] = old_rank;
	  test_pos = add(test_position[0],test_position[1]);
          if (board_pieces[test_pos] != NULL)
            return false;
          test_file = test_file + x;
        }
      break;
    case 4:
      if (new_file > old_file)
        {
          test_file = old_file + 1;
	  test_rank = old_rank + 1;
	  x = 1;
        }
      else
        {
          test_file = old_file + 1;
	  test_rank = old_rank + 1;
          x = -1;
        }      
      while (test_file != new_file)
        {
          test_position[0] = test_rank;
          test_position[1] = test_file;
	  test_pos = add(test_position[0],test_position[1]);
          if (board_pieces[test_pos] != NULL)
            return false;
          test_file = test_file + x;
	  test_rank = test_rank + x;
        }
      break;
    case 5:
      if (new_file > old_file)
        {
          test_file = old_file + 1;
          test_rank = old_rank - 1;
          x = 1;
        }
      else
        {
          test_file = old_file - 1;
          test_rank = old_rank + 1;
          x = -1;
        }
      while (test_file != new_file)
        {
          test_position[0] = test_rank;
          test_position[1] = test_file;
          test_pos = add(test_position[0],test_position[1]);
          if (board_pieces[test_pos] != NULL)
            return false;
          test_file = test_file + x;
          test_rank = test_rank - x;
        }
      break;
    case 6:
      if (board_pieces[new_pos] == NULL)
	return false;
      break;
    case 7:
      if (board_pieces[new_pos] != NULL)
        return false;
      break;
    default:
      ;
    }

  if (board_pieces[new_pos] == NULL && valid > 0)
    {
      board_pieces[old_pos]->set_position(new_rank,new_file);
      return true;
    }
  if (board_pieces[new_pos]->get_colour() != board_pieces[old_pos]->get_colour() && valid > 0)
    {
      board_pieces[old_pos]->set_position(new_rank,new_file)    ;
      return true;
    }
  cout << "invalid_move for piece" << endl;  
  return false;
}

void board::display_board()
{
  string position;
  const char separator    = '|';
  char sock; 
  int gay;
  for (char i = '1'; i < '9'; i++)
    {
      for(char j = 'a'; j < 'i'; j++) 
	{
	  if (board_pieces[add(j,i)] != NULL) 
	    {  
	      sock = board_pieces[add(j,i)]->get_id();
	      gay = board_pieces[add(j,i)]->get_colour();

	      cout << separator << sock <<  '-' << gay;
	    }
	  else
	    {
	      cout << separator << "   ";
	    }	  
	}
      cout << separator << endl;
    }
}

void board::submit_move(string old_pos, string new_pos)
{
  char old_position[2], new_position[2];
  old_position[0] = old_pos.at(1);
  old_position[1] = old_pos.at(0);
  new_position[0] = new_pos.at(1);
  new_position[1] = new_pos.at(0);
    
  if (check_move(old_position,new_position))
    {
      board_pieces[new_pos] = board_pieces[old_pos];
      board_pieces[old_pos] = NULL;
      cout << board_pieces[new_pos]->get_id() << " moves from " << old_pos << " to " << new_pos << endl;
    }
}



string add(char one, char two)
{ 
  string aString;
  aString = one;
  aString += two;
  return aString;
}
