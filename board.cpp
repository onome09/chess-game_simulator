#include<iostream>
#include<string>
#include<iomanip>
#include"board.h"
#include"move_list.h"
#include"validity_issues.h"
#include"legal_issues.h"

using namespace std;

const char MIN_RANK = '1';
const char MAX_RANK = '8';
const char MIN_FILE = 'A';
const char MAX_FILE = 'H';

Board::Board()
{
  set();
}  

void Board::set()
{
  colour[0] = "White";
  colour[1] = "Black";
  turn = 0;
 
  /*Initialise all pieces on the board and ensure all spaces that should be empty are vacated*/
 for (char i = MIN_RANK; i < MAX_RANK + 1; i++)
    {
      for(char j = MIN_FILE; j < MAX_FILE + 1; j++)
	{
	   board_pieces[add(j,i)] = NULL;
	} 
    }
  for (int i = 0; i < 2; i++)
    {
      char pawn_row = '2' + i * 5;
      char non_pawn_row = '1' + i * 7;     
      for (int j = 0; j < 8; j++)
	{
	  board_pieces[add(char(j + 65),pawn_row)] = new Pawn(pawn_row, char(j+65), i);
	}
      for (int j = 0; j < 2; j++)
	{
	  board_pieces[add(char(1 + 5 * j + 65), non_pawn_row)] = new Knight(non_pawn_row, char(1 + 5 * j + 65), i);
	  board_pieces[add(char(2 + 3 * j + 65), non_pawn_row)] = new Bishop(non_pawn_row, char(2 + 3 * j + 65), i);
	  board_pieces[add(char(7 * j + 65), non_pawn_row)] = new Castle(non_pawn_row, char(7 * j + 65), i);
	}
      board_pieces[add('D', non_pawn_row)] = new Queen(non_pawn_row, 'D', i);
      board_pieces[add('E', non_pawn_row)] = new King(non_pawn_row, 'E', i);      
    }
 
 /*initialise the two teams' kings starting position*/
  king_position[0] = 'E';
  king_position[1] = '1';
  king_position[2] = 'E';
  king_position[3] = '8';
  cout << "A new chess game has started" << endl;
}

int Board::check_move(string old_position, string new_position, int turn_flag)
{
  /*Fisrt check move is valid*/
  char old_coordinates[2], new_coordinates[2];
  switch(validity_checks(old_position, new_position, old_coordinates, new_coordinates, turn_flag))
    {
    case WRONG_TURN: 
      return WRONG_TURN;
    case INVALID_STARTING_POSITION:
      return INVALID_STARTING_POSITION;
    case INVALID_ENDING_POSITION:
      return INVALID_ENDING_POSITION;
    case NO_PIECE_AT_STATING_POSITION:
      return NO_PIECE_AT_STATING_POSITION;
    case NO_MOVEMENT:
      return NO_MOVEMENT;
    case NO_VALIDITY_ISSUES:
      break;
    default:
      break;
    }

  /*Now check if the move is legal*/
  switch(legal_checks(old_position, new_position, old_coordinates, new_coordinates))
    {
    case MOVE_NOT_VALID:
      return MOVE_NOT_VALID;
    case MOVE_SEEMS_FINE:
      return MOVE_SEEMS_FINE;
    case MOVE_SEEMS_FINE_BUT_TAKES_PIECE:
      return MOVE_SEEMS_FINE_BUT_TAKES_PIECE;
    default:
      break;
    }
  return 0;
}

int Board::validity_checks(string old_position, string new_position, char *old_coordinates, char *new_coordinates, int turn_flag)
{
  for (int i = 0; i < 2; i++)
    {
      if (old_position.at(i) > MAX_FILE - i * 16 || old_position.at(i) < MIN_FILE - i * 16 )
	{
	  return INVALID_STARTING_POSITION;
	}     
      old_coordinates[i] = old_position.at(i);
      if (new_position.at(i) > MAX_FILE - i * 16 || new_position.at(i) < MIN_FILE - i * 16 )
	{
	  return INVALID_ENDING_POSITION;
	}
      new_coordinates[i] = new_position.at(i);
    }

  if (board_pieces[old_position] == NULL)
    {
      return NO_PIECE_AT_STATING_POSITION;
    }
  if (board_pieces[old_position]->get_colour() != turn && turn_flag >0)
    {
      return WRONG_TURN;
    }
  if (strcmp(old_coordinates, new_coordinates) == 0)
    {
      return NO_MOVEMENT;
    }  
  return NO_VALIDITY_ISSUES;
}
int Board::legal_checks(string old_position, string new_position, char* old_coordinates, char* new_coordinates)
{
  char old_rank = old_coordinates[1];
  char old_file = old_coordinates[0];
  char new_rank = new_coordinates[1];
  char new_file = new_coordinates[0];
  /*call make move function and check for pieces in the way of the move or other pieces at the new position*/
  switch (board_pieces[old_position]->make_move(new_coordinates)) 
    {
      char a;
      char b;
      int x;
      int y;
    case INVALID_MOVE:
      return MOVE_NOT_VALID;
      break;
    case UNIDIRECTIONAL_MOVE_ONE_SPACE_FORWARDS:
      if (board_pieces[new_position] != NULL)
	return MOVE_NOT_VALID;
      break;
    case BIDIRECTIONAL_MOVE_ONE_SPACE_DIAGONAL_FORWARDS:
      if (board_pieces[new_position] == NULL)
	return MOVE_NOT_VALID;
      break;
    case MULTIDIRECTIONAL_MOVE_ONE_SPACES:
      break;
    case UNIDIRECTIONAL_MOVE_TWO_SPACES_FORWARDS:
      if (board_pieces[new_position] != NULL)
	return MOVE_NOT_VALID;
      if (board_pieces[add(old_file,(min(old_rank, new_rank) + 1))] != NULL)
	return MOVE_NOT_VALID;
      break;
    case BIDIRECTIONAL_VERTICAL_MOVE_ONE_OR_MORE_SPACES:
      a = min(old_rank, new_rank) + 1;
      b = max(old_rank, new_rank);
      while(a < b)
	{
	  if (board_pieces[add(old_file, a)] != NULL)
	    return MOVE_NOT_VALID;
	  a++;
	}
      break;
    case BIDIRECTIONAL_HORIZONTAL_MOVE_ONE_OR_MORE_SPACES:
      a = min(old_file, new_file) + 1;
      b = max(old_file, new_file);
      while(a < b)  
	{ 
	  if (board_pieces[add(a, old_rank)] != NULL) 
	    return MOVE_NOT_VALID;
	  a++;
	}
      break;
    case BIDIRECTIONAL_45_OR_225_DEGREES_MOVE_ONE_OR_MORE_SPACES:
      y = 1;
      x = 1;
      a = min(old_file, new_file) + 1;
      b = max(old_file, new_file);
      if (new_file < old_file)
	x = 1;
      while(a < b)  
	{   
	  if (board_pieces[add(a, min(old_rank, new_rank) + x * y)] != NULL) 
	    return MOVE_NOT_VALID;
	  a++;
	  y++;
	}
      break;
    case BIDIRECTIONAL_135_OR_315_DEGREE_MOVE_ONE_OR_MORE_SPACES:
      y = 1;
      x = -1;
      a = min(old_file, new_file) + 1;
      b = max(old_file, new_file);
      if (new_file < old_file)
	x = -1;
      while(a < b)  
	{
	  if (board_pieces[add(a, max(old_rank, new_rank) + x * y)] != NULL) 
	    return MOVE_NOT_VALID;
	  a++;  
	  y++;
	}
      break;
    case L_SHAPE_MOVE_CAN_JUMP_PIECES:
      break;
    default:
      ;
    }
  if (board_pieces[new_position] == NULL)
    return MOVE_SEEMS_FINE;
  if (  board_pieces[new_position]->get_colour() != board_pieces[old_position]->get_colour() )
    return MOVE_SEEMS_FINE_BUT_TAKES_PIECE;
  return MOVE_NOT_VALID;
}


void Board::display_board()
{
  string position;
  const char separator    = '|';
  char sock; 
  int gay;
  for (char i = '8'; i > '0'; i--)
    {
      for(char j = 'A'; j < 'I'; j++) 
	{
	  if (board_pieces[add(j,i)] != NULL) 
	    {  
	      sock = board_pieces[add(j,i)]->get_symbol();
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

void Board::submitMove(string old_position, string new_position)
{
  int po;
  char fake[2];
  
  switch(check_move(old_position, new_position,1))
    {
    case WRONG_TURN:
      cout << "It is not " << colour[board_pieces[old_position]->get_colour()] << "'s turn to move" << endl;
      break;
    case INVALID_STARTING_POSITION:
      cout << "Invalid starting position" << endl;
      break;
    case INVALID_ENDING_POSITION:
      cout << "Invalid ending position" << endl;
      break;
    case NO_PIECE_AT_STATING_POSITION:
      cout << "There is no piece at position " << old_position << endl;
      break;
    case NO_MOVEMENT:
      cout << "Attempt to move a piece to it'd same position" << endl;
      break;
    case MOVE_NOT_VALID:
      cout << colour[turn]<< "'s " << board_pieces[old_position]->get_id() << " cannot move to " << new_position << endl;
      break;
    case MOVE_SEEMS_FINE:
      
      
      board_pieces[old_position]->set_position(new_position);      
      board_pieces[new_position] = board_pieces[old_position];
      board_pieces[old_position] = NULL;

      if (board_pieces[new_position]->get_id()== "King")
	{
	  king_position[0+2*turn] = new_position.at(0);
	  king_position[1+2*turn] = new_position.at(1);
	}
      turn = (turn+1) % 2;
      fake[0] = king_position[2 - 2*turn];
      fake[1] = king_position[3 - 2*turn];
      
      if (check(fake,((turn+1) % 2))==true)
	{
	  cout << "Illegal move for "<< colour[(turn+1) % 2] << endl;
	  if (board_pieces[new_position] != NULL && board_pieces[new_position]->get_id()== "King")
	    {
	      king_position[0+2*turn] = old_position.at(0);
	      king_position[1+2*turn] = old_position.at(1);
	    } 
	  board_pieces[new_position]->set_position(old_position);
	  board_pieces[old_position] = board_pieces[new_position];
	  board_pieces[new_position] = NULL;

	  turn = (turn+1) % 2;
	  return;
	}
      turn = (turn+1) % 2;
      po = result(king_position, (turn+1)%2);
      cout << colour[(turn+1)%2]<< "'s " << board_pieces[new_position]->get_id() << " moves from " << old_position << " to " << new_position << endl;    
      switch(po)
	{
	case 0:
	    turn = (turn+1) % 2;
	  break;
	case 1:
	  turn = (turn+1) % 2;    
	  cout << colour[turn] << " is in check" << endl;

	  break;
	case 2:
	  cout << colour[turn] << " is in checkmate" << endl;
	  return;
	  break;
	case 3:
          cout << "The game is in stalemate" << endl;
          return;
          break;
	default:
	  ;
	}
      
      break;
    case MOVE_SEEMS_FINE_BUT_TAKES_PIECE:
      Piece* recycle;
      
      recycle = board_pieces[new_position];
      board_pieces[old_position]->set_position(new_position);
      board_pieces[new_position] = board_pieces[old_position];
      board_pieces[old_position] = NULL;

      if (board_pieces[new_position]->get_id()== "King")
	{
	  king_position[0+2*turn] = new_position.at(0);
	  king_position[1+2*turn] = new_position.at(1);
	}
      turn = (turn+1) % 2;
      fake[0] = king_position[2-2*turn];
      fake[1] = king_position[3-2*turn];
      
      if (check(fake,((turn+1) % 2))==true)
	{
	  cout << "Illegal move for "<< colour[(turn+1) % 2] << endl;
	  if (board_pieces[new_position] != NULL && board_pieces[new_position]->get_id()== "King")
	    {
	      king_position[0+2*turn] = old_position.at(0);
	      king_position[1+2*turn] = old_position.at(1);
	    } 
	  board_pieces[new_position]->set_position(old_position);
	  board_pieces[old_position] = board_pieces[new_position];
	  board_pieces[new_position] = recycle;
	  
	  turn = (turn+1) % 2;

	  return;
	}
      cout << colour[(turn+1) % 2]<< "'s " << board_pieces[new_position]->get_id() << " moves from " << old_position << " to " << new_position;
      cout << " taking " << colour[turn]<< "'s " << recycle->get_id() << endl;      
      delete recycle;
      turn = (turn+1) % 2;
      recycle = NULL;
      po = result(king_position, (turn+1)%2);
     
      switch(po)
	{
	case 0:
				      turn = (turn + 1)%2;
	  break;
	case 1:
			      turn = (turn + 1)%2;	
	  cout << colour[turn] << " is in check" << endl;
	 
	  break;
	case 2:
	  cout << colour[turn] << " is in checkmate" << endl;
	  return;
	  break;
	case 3:
          cout << "The game is in stalemate" << endl;
          return;
          break;
	default: 
	  ;
	}
           
      break;
    default:
      ;
    }

  return;
}

Board::~Board()
{
  for (char i = MIN_RANK; i < MAX_RANK + 1; i++)
    {
      for(char j = MIN_FILE; j < MAX_FILE + 1; j++)
	{
	  if (board_pieces[add(j,i)] != NULL)
	    {
	      delete board_pieces[add(j,i)];
	      board_pieces[add(j,i)] = NULL;
	    }
	} 
    }
}

bool Board::check(char* king_position, int team)
{
  char team_king_pos[2];
  team_king_pos[0] = king_position[0];
  team_king_pos[1] = king_position[1];


  for (char i = MIN_RANK; i < MAX_RANK + 1; i++)
    {
      for(char j = MIN_FILE; j < MAX_FILE + 1; j++)
	{
	  if (board_pieces[add(j,i)] != NULL && board_pieces[add(j,i)]->get_colour() != team && check_move(add(j,i) ,add(team_king_pos[0],team_king_pos[1]),0) > 5)
	    {
	      return true;}
	    
	}
    }
  return false;
}

int Board::result(char* king_position, int team)
{
  bool a=false;
  bool b = false;
  char team_king_pos[2];
  team_king_pos[0] = king_position[0 + 2*team];
  team_king_pos[1] = king_position[1 + 2*team];
  if (check(team_king_pos, team) == false)
    a =  true;
  
  for (char i = MIN_RANK; i < MAX_RANK + 1; i++)
    {
      for(char j = MIN_FILE; j < MAX_FILE + 1; j++)
	{
	  for (char k = MIN_RANK; k < MAX_RANK + 1; k++)
	    {
	      for(char l = MIN_FILE; l < MAX_FILE + 1; l++)
		{ 
		  if (board_pieces[add(j,i)] != NULL && board_pieces[add(j,i)]->get_colour() == team)
		    {		
		      if  (check_move(add(j,i), add(l,k),0)>5)
			{			      
			  int m = 0;
			  Piece* recycle;
			  if (board_pieces[add(l,k)] != NULL)
			    {
			      m = 1;
			      recycle = board_pieces[add(l,k)];
			    }
			  if (j == team_king_pos[0] && i ==team_king_pos[1])
			    {
			      team_king_pos[0] = l;
                              team_king_pos[1] = k;
			  
			    }
			  board_pieces[add(l,k)] = board_pieces[add(j,i)];
			  board_pieces[add(j,i)] = NULL;
			  if (check(team_king_pos,team ) == false)
			    {
			      board_pieces[add(j,i)] = board_pieces[add(l,k)];
			      board_pieces[add(l,k)] = NULL;
			      if (m > 0)
				{
				  board_pieces[add(l,k)] = recycle;
				    
				}
			      team_king_pos[0] = king_position[0 + 2*team];
			      team_king_pos[1] = king_position[1 + 2*team];
			      b =true;
			      goto next;
			    }
			  team_king_pos[0] = king_position[0 + 2*team];
			  team_king_pos[1] = king_position[1 + 2*team];
			  board_pieces[add(j,i)] = board_pieces[add(l,k)];
			  board_pieces[add(l,k)] = NULL;
			  if (m > 0)
			    { 
			      board_pieces[add(l,k)] = recycle;
			            
			    }
			  
			}
		      
		    }
		  
		}
	    }
	}
    }
 next:


  if (a==true && b == true)
    {
    return 0;
    }
  if (a==false && b==true)
    { 
      return 1;}
      if (a==false && b==false)
	{turn = (turn + 1)%2;
	  return 2;}
      if (a==true && b==false)
	return 3;
      return 0;

}

string Board::add(char one, char two)
{ 
  string aString;
  aString = one;
  aString += two;
  return aString;
}

void Board::resetBoard()
{
  for (char i = MIN_RANK; i < MAX_RANK + 1; i++)
    {
      for(char j = MIN_FILE; j < MAX_FILE + 1; j++)
	{
	  if (board_pieces[add(j,i)] != NULL)
	    delete board_pieces[add(j,i)];
	} 
    }
  set(); 
}
