#include <iostream>
#include <cstdio>
#include "sudoku.h"
#include <cstring>
#include <cassert>

using namespace std;

bool make_move(const char *position, const int digit, char board[9][9]);

int main() {

  char board[9][9];

  /* This section illustrates the use of the pre-supplied helper functions. */
  cout << "============= Pre-supplied functions =============\n\n";

  cout << "Calling load_board():\n";
  load_board("easy.dat", board);

  cout << '\n';
	cout << "Displaying Sudoku board with display_board():\n";
  display_board(board);
  cout << "Done!\n\n";

  cout << "=================== Question 1 ===================\n\n";

  load_board("easy.dat", board);
  cout << "Board is ";
  if (!is_complete(board)) {
    cout << "NOT ";
  }
  cout << "complete.\n\n";

  load_board("easy-solution.dat", board);
  cout << "Board is ";
  if (!is_complete(board)) {
    cout << "NOT ";
  }
  cout << "complete.\n\n";

  cout << "=================== Question 2 ===================\n\n";

  load_board("easy.dat", board);

  // Should be OK
  cout << "Putting '1' into I8 is ";
  if (!make_move("I8", '1', board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:\n";
  display_board(board);

  // write more tests

  /*cout << "=================== Question 3 ===================\n\n";

  load_board("easy.dat", board);
  if (save_board("easy-copy.dat", board)) {
    cout << "Save board to 'easy-copy.dat' successful.\n";
  } else {
    cout << "Save board failed.\n";
  }
  cout << '\n';

  cout << "=================== Question 4 ===================\n\n";

  load_board("easy.dat", board);
  if (solve_board(board)) {
    cout << "The 'easy' board has a solution:\n";
    display_board(board);
  } else {
    cout << "A solution cannot be found.\n";
  }
  cout << '\n';

  load_board("medium.dat", board);
  if (solve_board(board)) {
    cout << "The 'medium' board has a solution:\n";
    display_board(board);
  } else {
    cout << "A solution cannot be found.\n";
  }
  cout << '\n';

  // write more tests

  cout << "=================== Question 5 ===================\n\n";

  // write more tests */

  return 0;
}


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
  
