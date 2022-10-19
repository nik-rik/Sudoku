#ifndef SUDOKU_H
#define SUDOKU_H

void load_board(const char* filename, char board[9][9]);
void display_board(const char board[9][9]);
bool is_complete(const char board[9][9]);
bool contains_num(const char board[9][9], int row, int col);
bool make_move(const char *position, const int digit, char board[9][9]);
bool save_board(const char* filename, char board[9][9]);

#endif
