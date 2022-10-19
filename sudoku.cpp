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
  


/*Function that places digit on board */
bool make_move(const char *position, const int digit, char board[9][9]){
  // Checks for validity of position input
  // Checks if string is correct length
  if (strlen(position) != 2)
    return false;

  int input_row_array_number = (*position - '@') - 1;
  int input_column_array_number = ((*(position + 1) - '0') - 1);
  int input_digit = digit - '0';

  
  // Checks if row is within parameters
  if (input_row_array_number < 0 || input_row_array_number > 8)
    return false;

  // Checks if column is within parameters
  if (input_column_array_number < 0 || input_column_array_number > 8)
    return false;

  // Checks if position is already filled in
  if (contains_num(board, input_row_array_number, input_column_array_number))
      return false;



  // Checks for validity of digit input
  // Checks if digit is within parameters
  if (input_digit < 1)
    return false;



  // Checks if move is logically correct
  // Checks if number already exists in column
  for (int row = 0; row < 9; row++)
    if (board[row][input_column_array_number] - '0' == input_digit)
      return false;
 
  // Checks if number already exists in row
  for (int col = 0; col < 9; col++)
    if (board[input_row_array_number][col] - '0' == input_digit)
      return false;

  // Checks if number already exists in box
  int start_row = input_row_array_number - input_row_array_number % 3, start_col = input_column_array_number - input_column_array_number % 3;

  for (int row = 0; row < 3; row++)
    for (int col = 0; col < 3; col++)
      if (board[row + start_row][col + start_col] - '0' == input_digit)
	return false;
  

  // Updates board
  board[input_row_array_number][input_column_array_number] = digit;

  
  return true;
}
  

/* Function that saves board */
bool save_board(const char *filename, char board[9][9]){
  ofstream out;

  const int MAX = 80;
  char filename2[MAX];

  strcpy (filename2, filename);

  out.open(filename2);

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
  

  
