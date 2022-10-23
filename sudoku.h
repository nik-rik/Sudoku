#ifndef SUDOKU_H
#define SUDOKU_H

void load_board(const char* filename, char board[9][9]);
void display_board(const char board[9][9]);
bool is_complete(const char board[9][9]);
bool contains_num(const char board[9][9], int row, int col);
bool make_move(const char *position, const int digit, char board[9][9]);
bool save_board(const char* filename, char board[9][9]);
bool position_input_check(const char *position, int row, int col);
bool digit_input_check(const int digit);
bool already_in_col(const char board[9][9], int col, int digit);
bool already_in_row(const char board[9][9], int row, int digit);
bool already_in_box(const char board[9][9], int row, int col, int digit);
bool move_safe(const char board[9][9], int row, int col, int digit);
bool solve_board(char board[9][9]);
bool find_empty_box(const char board[9][9], int &row, int &col);
int number_of_possible_values(const char board[9][9]);
bool solve_board2(char board[9][9], int &updates);
void difficulty_test(const char* filename, char board[9][9]);

#endif
