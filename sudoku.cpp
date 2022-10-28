#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "sudoku.h"
#include <chrono>

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
  /* Coverts inputs into correct ASCII code representation */  
  int input_row_array_number = (*position - 'A');
  int input_column_array_number = (*(position + 1) - '1');
  int input_digit = digit - '0';

  if (!position_input_check(position, input_row_array_number, input_column_array_number)) // Checks for validity of position input
    return false;

  if (!digit_input_check(input_digit)) // Checks for validity of digit input
    return false;

  if (contains_num(board, input_row_array_number, input_column_array_number))  // Checks that the box is empty
    return false;

  if (!move_safe(board, input_row_array_number, input_column_array_number, input_digit))  // Checks if move is logically correct
    return false;

  board[input_row_array_number][input_column_array_number] = digit;  // Updates board if the previous checkes are passed
  return true;
}


/* Function that checks the position input is as required */
bool position_input_check(const char *position, int row, int col){
  if (strlen(position) != 2)  // Checks if string is correct length
    return false;

  if (row < 0 || row > 8)  // Checks if row is within parameters
    return false;

  if ( col < 0 || col > 8)  // Checks if column is within parameters
    return false;

  return true;
}


/* Function that checks the digit input is as required */
bool digit_input_check(const int digit){
  if (digit < 1 || digit > 9) // Checks if digit is withn parameters
    return false;

  return true;
}


/* Function that checks if number already exists in column */
bool already_in_col(const char board[9][9], int col, int digit){ 
  for (int row = 0; row < 9; row++) // Goes through each row in a column
    if (board[row][col] - '0' == digit) // Returns true if there is a number that matches digit
      return true;

  return false;
}


/* Function that checks if number already exists in row */
bool already_in_row(const char board[9][9], int row, int digit){
  for (int col = 0; col < 9; col++) // Goes through each column in a row
    if (board[row][col] - '0' == digit) // Returns true if there is a number that matches digit
      return true;

  return false;

}


/* Function that checks if number already exists in box */
bool already_in_box(const char board[9][9], int row, int col, int digit){
  int start_row = row - row % 3, start_col = col - col % 3; // Used to determine the correct cell to start search at (i.e. first cell in box)

  for (int r = 0; r < 3; r++) // Searches a 3 x 3 box
    for (int c = 0; c < 3; c++)
      if (board[r + start_row][c + start_col] - '0' == digit) // Uses the start variables to check the correct box for matches
	return true;

  return false;
}

/* Function that checks if position with digit is logically valid */
bool move_safe(const char board[9][9], int row, int col, int digit){
  if (already_in_col(board, col, digit))  // Checks if number already exists in column
    return false;

  if (already_in_row(board, row, digit))  // Checks if number already exists in row 
    return false;

  if (already_in_box(board, row, col, digit))  // Checks if number already exists in box
    return false;


  return true;
}

 
/* Function that saves board */
bool save_board(const char *filename, char board[9][9]){
  ofstream out; 

  const int MAX = 80;
  char filename_cpy[MAX];

  /*Creates a file using filename input */
  strcpy(filename_cpy, filename);
  out.open(filename_cpy);

  /* Outputs array to file if no error */ 
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
  
  if(!find_empty_box(board, row, col))   // This is passed by reference to the function so the proceeding check happens at an empty box
    return true;                         // If there are no empty boxes then the board is solved

  /* Checks whether each digit from 1-9 can be placed in cell */
  for (int i = 1; i <= 9; i++)
    if(move_safe(board, row, col, i)){    
      board[row][col] = i + '0'; // If digit can be placed, board is tentatively updated
      if(solve_board(board)) // Repeats process for next empty cell
	return true; // If the board is complete then returns
      board[row][col] = '.'; // If no number works in a cell, deletes tentative input and trys a different number for that cell
    }

  return false; // This causes the function to backtrack if no digit can fit in a a box
}

  
/* Function to find the next empty square */
bool find_empty_box(const char board[9][9], int &row, int &col) {
  for (row = 0; row<9; row++)
    for (col = 0; col<9; col++)
      if (!contains_num(board, row, col)) //Checks each box to see if it contains a number
	return true;
  return false;
}


/* Functon to find the number of valus possible for a board at outset*/
int number_of_possible_values(const char board[9][9]){

  /* This finds the sum of the number of digits that can be placed in each cell at the beginning of the game.
     If the sum is larger, this would indicate that the board is harder to complete as there are less clearly
     solvable boxes */

  int num = 0;

  for (int row = 0; row<9; row++)
    for (int col = 0; col<9; col++)
      if (!contains_num(board, row, col)) // Checks each cell that is not pre-filled
	for (int i = 1; i <= 9; i++)
	  if (move_safe(board, row, col, i)) 
	    num++; // Adds to count if a digit is a viable option

  return num;

}

/* Function that solves board while also measuring the number of board updates made by overloading solve_board*/
bool solve_board(char board[9][9], int &updates){

  /* More board updates would indicate a higher difficulty as the algorithm tried and failed on more node paths
     However, it is not a perfect measure as ths could be influenced by the order of searches etc.*/
  
  int row, col;
  
  if(!find_empty_box(board, row, col))
    return true;
  
  for (int i = 1; i <= 9; i++)
    if(move_safe(board, row, col, i)){
      board[row][col] = i + '0';
      updates++; // This increments when a board update is made (only difference from "solve_board")
      if(solve_board(board, updates))
	return true;
      board[row][col] = '.';
    }
  return false;
}

/* Function to output metrics to test for difficulty of board */
void difficulty_test(const char* filename, char board[9][9]){

  char board_cpy[9][9];
  int updates = 0;
  load_board(filename, board);

  for (int x=0 ; x < 9; x++)
    for (int y=0 ; y < 9; y++)
      board_cpy[x][y] = board[x][y]; // Makes copy of board so it does not have to be loaded twice (

  cout << filename << " test statistics:\n";

  cout << "Possible values from outset: " << number_of_possible_values(board) << "\n";

  solve_board(board_cpy, updates);
  cout << "Number of board updates: " << updates << "\n";

  /* This measures the runtime of the solve_board function for a specific board. Higher runtime 
     indicates higher difficulty. However this is also imperfect as it could be due to the orders
     that the algorithm searches in. */
  auto begin = std::chrono::high_resolution_clock::now(); // Starts timer
  solve_board(board);
  auto end = std::chrono::high_resolution_clock::now(); // Ends timer
  auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin); 
  cout << "Execution time (nanoseconds):" << elapsed.count() << "\n\n"; // Timer output in nanoseconds

}


