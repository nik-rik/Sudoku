#include <iostream>
#include <cstdio>
#include "sudoku.h"


using namespace std;


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
  
  // Test with invalid Position Input 1 - String longer than 2 char
  load_board("easy.dat", board);
  cout << "Putting '1' into I8B4 is ";
  if (!make_move("I8B4", '1', board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:\n";

  // Test with invalid Position Input 2 - Row too high
  load_board("easy.dat", board);
  cout << "Putting '1' into J8 is ";
  if (!make_move("J8", '1', board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:\n";

  // Test with invalid Position Input 3 - Row too low
  load_board("easy.dat", board);
  cout << "Putting '1' into &8 is ";
  if (!make_move("&8", '1', board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:\n";
  
  // Test with invalid Digit Input 1 - Digit too high
  load_board("easy.dat", board);
  cout << "Putting '18' into I8 is ";
  if (!make_move("I8", '10', board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:\n";

  // Test with invalid Digit Input 2 - Digit too low
  load_board("easy.dat", board);
  cout << "Putting '-1' into I8 is ";
  if (!make_move("I8",'-1', board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:\n";

  // Test with number already in column
  load_board("easy.dat", board);
  cout << "Putting '1' into I9 is ";
  if (!make_move("I9",'1', board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:\n";

  // Test with number already in row
  load_board("easy.dat", board);
  cout << "Putting '1' into G8 is ";
  if (!make_move("G8",'1', board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:\n";

  // Test with number already in box
  load_board("easy.dat", board);
  cout << "Putting '1' into G8 is ";
  if (!make_move("H4",'4', board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:\n";
  
  cout << "=================== Question 3 ===================\n\n";

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
  load_board("mystery1.dat", board); // Tests mystery board 1
  if (solve_board(board)) {
    cout << "The 'mystery1' board has a solution:\n";
    display_board(board);
  } else {
    cout << "A solution cannot be found.\n";
  }
  cout << '\n';

  load_board("mystery2.dat", board); // Tests mystery board 2
  if (solve_board(board)) {
    cout << "The 'mystery2' board has a solution:\n";
    display_board(board);
  } else {
    cout << "A solution cannot be found.\n";
  }
  cout << '\n';

  load_board("mystery3.dat", board); // Tests myster board 3
  if (solve_board(board)) {
    cout << "The 'mystery3' board has a solution:\n";
    display_board(board);
  } else {
    cout << "A solution cannot be found.\n";
  }
  cout << '\n';


  cout << "=================== Question 5 ===================\n\n";

  
  // write more tests

  /* Outputs test statistcs for each of the solvable board */
  difficulty_test("easy.dat", board);
  difficulty_test("medium.dat", board);
  difficulty_test("mystery1.dat", board);
  difficulty_test("mystery3.dat", board);

  
  return 0;
}




  
