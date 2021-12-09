#include <stdbool.h>
#include <stdint.h>
#include "board.h"

#define FIRST_ROW 0
#define SECOND_ROW 1
#define THIRD_ROW 2
#define FOURTH_ROW 3
#define FIFTH_ROW 4
#define SIXTH_ROW 5
#define SEVENTH_ROW 6
#define EIGHTH_ROW 7

#define FIRST_COL 0
#define SECOND_COL 1
#define THIRD_COL 2
#define FOURTH_COL 3
#define FIFTH_COL 4
#define SIXTH_COL 5
#define SEVENTH_COL 6
#define EIGHTH_COL 7

#define SQUARE_DIM 30

#define BG_BLACK DISPLAY_GRAY
#define BG_WHITE DISPLAY_LIGHT_GRAY

//reads in touch and computes what square was touched (its row and column)
void chessDisplay_touchScreencomputeBoardRowColumn(uint8_t *row, uint8_t *column);

//draws piece corrseponding w/ offset when erase is false
//erases piece if erase is true
void chessDisplay_displayPiece(piece_t class, uint8_t row, uint8_t column, bool erase);

//draw checkerboard 
void chessDisplay_drawBoard();

//highlight piece that player has chosen to move
void chessDisplay_pieceChosen(piece_t class, uint8_t row, uint8_t column);

//test display
void chessDisplay_runTest();
