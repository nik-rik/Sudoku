#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "sudoku.h"

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* pre-supplied function to load a Sudoku board from a file */
void load_board(const char* filename, char board[9][9]) {

  cout << "Loading Sudoku board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in) {
    cout << "Failed!\n";
  }
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << '\n';
  assert(row == 9);
}

/* internal helper function */
void print_frame(int row) {
  if (!(row % 3)) {
    cout << "  +===========+===========+===========+\n";
  } else {
    cout << "  +---+---+---+---+---+---+---+---+---+\n";
  }
}

/* internal helper function */
void print_row(const char* data, int row) {
  cout << (char) ('A' + row) << " ";
  for (int i=0; i<9; i++) {
    cout << ( (i % 3) ? ':' : '|' ) << " ";
    cout << ( (data[i]=='.') ? ' ' : data[i]) << " ";
  }
  cout << "|\n";
}

/* pre-supplied function to display a Sudoku board */
void display_board(const char board[9][9]) {
  cout << "    ";
  for (int r=0; r<9; r++) {
    cout << (char) ('1'+r) << "   ";
  }
  cout << '\n';
  for (int r=0; r<9; r++) {
    print_frame(r);
    print_row(board[r],r);
  }
  print_frame(9);
}

/* add your functions here */


/* Function to check if board is complete */
bool is_complete(const char board[9][9]) {
  for (int row=0; row<9; row++)
    for (int col=0; col<9; col++)
      if (!contains_num(board, row, col))
	return false;
  return true;
}


/* Function to check if a space already contains a number from 1-9 */
bool contains_num(const char board[9][9], int row, int col){
  if (board[row][col] < '1' || board[row][col] > '9')
    return false;
  return true;
}
  


/* Function that places digit on board */
bool make_move(const char *position, const int digit, char board[9][9]){
 
  int input_row_array_number = (*position - 'A');
  int input_column_array_number = (*(position + 1) - '1');
  int input_digit = digit - '0';

  // Checks for validity of position input
  if (!position_input_check(position, input_row_array_number, input_column_array_number))
    return false;

  // Checks for validity of digit input
  if (!digit_input_check(input_digit))
    return false;

  // Checks that the box is empty
  if (contains_num(board, input_row_array_number, input_column_array_number))
    return false;

  // Checks if move is logically correct
  if (!move_safe(board, input_row_array_number, input_column_array_number, input_digit))
    return false;

  // Updates board
  board[input_row_array_number][input_column_array_number] = digit;
  return true;
}

/* Function that checks the position input is as required */
bool position_input_check(const char *position, int row, int col){
  // Checks if string is correct length
  if (strlen(position) != 2)
    return false;

  // Checks if row is within parameters
  if (row < 0 || row > 8)
    return false;

  // Checks if column is within parameters
  if ( col < 0 || col > 8)
    return false;

  return true;
}


/* Function that checks the digit input is as required */
bool digit_input_check(const int digit){
  // Checks if digit is within parameters
  if (digit < 1 || digit > 9)
    return false;

  return true;
}

/* Function that checks if number already exists in column */
bool already_in_col(const char board[9][9], int col, int digit){ 
  for (int row = 0; row < 9; row++)
    if (board[row][col] - '0' == digit)
      return true;

  return false;
}


/* Function that checks if number already exists in row */
bool already_in_row(const char board[9][9], int row, int digit){
  for (int col = 0; col < 9; col++)
    if (board[row][col] - '0' == digit)
      return true;

  return false;

}

/* Function that checks if number already exists in box */
bool already_in_box(const char board[9][9], int row, int col, int digit){
 int start_row = row - row % 3, start_col = col - col % 3;

  for (int r = 0; r < 3; r++)
    for (int c = 0; c < 3; c++)
      if (board[r + start_row][c + start_col] - '0' == digit)
	return true;

  return false;
}

/* Function that checks if position with digit is logically valid */
bool move_safe(const char board[9][9], int row, int col, int digit){
  // Checks if number already exists in column
  if (already_in_col(board, col, digit))
    return false;

  // Checks if number already exists in row
  if (already_in_row(board, row, digit))
    return false;

  // Checks if number already exists in box
  if (already_in_box(board, row, col, digit))
    return false;


  return true;
}

 
/* Function that saves board */
bool save_board(const char *filename, char board[9][9]){
  ofstream out;

  const int MAX = 80;
  char filename_cpy[MAX];

  strcpy(filename_cpy, filename);

  out.open(filename_cpy);

  if (out.fail())
    return false;
  
  for(int row = 0; row < 9; row++){
    for (int col = 0; col < 9; col++)
      out.put(board[row][col]);
    out << "\n";
  }

  out.close();

  return true;

}
  

/* Function that solves board */
bool solve_board(char board[9][9]){

  int row, col;
  
  // base case
  if(!find_empty_box(board, row, col))
    return true;

  for (int i = 1; i <= 9; i++)
    if(move_safe(board, row, col, i)){
      // Updates board
      board[row][col] = i + '0';
      if(solve_board(board))
	return true;
      board[row][col] = '.';
    }
  return false;
}

  
/* Function to find the next empty square */
bool find_empty_box(const char board[9][9], int &row, int &col) {
  for (row = 0; row<9; row++)
    for (col = 0; col<9; col++)
      if (!contains_num(board, row, col))
	return true;
  return false;
}




