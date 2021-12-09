#include "chessDisplay.h"
#include "display.h"
#include <stdio.h>
#include <stdlib.h>
#include <utils.h>

// y coord, top right of board square
#define ROW_0 240 // 210-240
#define ROW_1 210
#define ROW_2 180
#define ROW_3 150
#define ROW_4 120
#define ROW_5 90
#define ROW_6 60
#define ROW_7 30 // 0-30
// x coord
#define COL_0 30
#define COL_1 60
#define COL_2 90
#define COL_3 120
#define COL_4 150
#define COL_5 180
#define COL_6 210
#define COL_7 240 // 210-240

#define DIFF_IN_SIZE 5
#define HALF_SQUARE_DIM SQUARE_DIM / 2
#define PIECE_DIM SQUARE_DIM - DIFF_IN_SIZE
#define PAWN_DIM HALF_SQUARE_DIM - DIFF_IN_SIZE
#define ROOK_DIM SQUARE_DIM - (DIFF_IN_SIZE * 2)
#define CHAR_SIZE 3
#define CHAR_DIFF_IN_SIZE_X 7.5
#define CHAR_DIFF_IN_SIZE_Y 4.5

int16_t readBGColor(uint8_t row, uint8_t column) {
  // if sum of row and column is odd draw it in "white" else it is
  if ((row + column) % 2) {
    return BG_WHITE;
  } else {
    return BG_BLACK;
  }
}

void drawGrid() {
  int16_t square_color;
  int16_t top_corner, left_corner;

  // proceed through each row
  for (int8_t i = 0; i <= EIGHTH_ROW; i++) {
    // proceed through each column
    for (int8_t j = 0; j <= EIGHTH_COL; j++) {
      square_color = readBGColor((7 - i), j);
      top_corner = i * SQUARE_DIM;
      left_corner = j * SQUARE_DIM;
      display_fillRect(left_corner, top_corner, SQUARE_DIM, SQUARE_DIM,
                       square_color);
    }
  }
}

void drawAllPieces() {
  // WHITE
  chessDisplay_displayPiece(PIECE_TYPE_PAWN | PIECE_COLOR_WHITE, SECOND_ROW,
                            FIRST_COL, false);
  chessDisplay_displayPiece(PIECE_TYPE_PAWN | PIECE_COLOR_WHITE, SECOND_ROW,
                            SECOND_COL, false);
  chessDisplay_displayPiece(PIECE_TYPE_PAWN | PIECE_COLOR_WHITE, SECOND_ROW,
                            THIRD_COL, false);
  chessDisplay_displayPiece(PIECE_TYPE_PAWN | PIECE_COLOR_WHITE, SECOND_ROW,
                            FOURTH_COL, false);
  chessDisplay_displayPiece(PIECE_TYPE_PAWN | PIECE_COLOR_WHITE, SECOND_ROW,
                            FIFTH_COL, false);
  chessDisplay_displayPiece(PIECE_TYPE_PAWN | PIECE_COLOR_WHITE, SECOND_ROW,
                            SIXTH_COL, false);
  chessDisplay_displayPiece(PIECE_TYPE_PAWN | PIECE_COLOR_WHITE, SECOND_ROW,
                            SEVENTH_COL, false);
  chessDisplay_displayPiece(PIECE_TYPE_PAWN | PIECE_COLOR_WHITE, SECOND_ROW,
                            EIGHTH_COL, false);
  chessDisplay_displayPiece(PIECE_TYPE_ROOK | PIECE_COLOR_WHITE, FIRST_ROW,
                            FIRST_COL, false);
  chessDisplay_displayPiece(PIECE_TYPE_ROOK | PIECE_COLOR_WHITE, FIRST_ROW,
                            EIGHTH_COL, false);
  chessDisplay_displayPiece(PIECE_TYPE_KNIGHT | PIECE_COLOR_WHITE, FIRST_ROW,
                            SECOND_COL, false);
  chessDisplay_displayPiece(PIECE_TYPE_KNIGHT | PIECE_COLOR_WHITE, FIRST_ROW,
                            SEVENTH_COL, false);
  chessDisplay_displayPiece(PIECE_TYPE_BISHOP | PIECE_COLOR_WHITE, FIRST_ROW,
                            THIRD_COL, false);
  chessDisplay_displayPiece(PIECE_TYPE_BISHOP | PIECE_COLOR_WHITE, FIRST_ROW,
                            SIXTH_COL, false);
  chessDisplay_displayPiece(PIECE_TYPE_QUEEN | PIECE_COLOR_WHITE, FIRST_ROW,
                            FOURTH_COL, false);
  chessDisplay_displayPiece(PIECE_TYPE_KING | PIECE_COLOR_WHITE, FIRST_ROW,
                            FIFTH_COL, false);

  // BLACK
  chessDisplay_displayPiece(PIECE_TYPE_PAWN | PIECE_COLOR_BLACK, SEVENTH_ROW,
                            FIRST_COL, false);
  chessDisplay_displayPiece(PIECE_TYPE_PAWN | PIECE_COLOR_BLACK, SEVENTH_ROW,
                            SECOND_COL, false);
  chessDisplay_displayPiece(PIECE_TYPE_PAWN | PIECE_COLOR_BLACK, SEVENTH_ROW,
                            THIRD_COL, false);
  chessDisplay_displayPiece(PIECE_TYPE_PAWN | PIECE_COLOR_BLACK, SEVENTH_ROW,
                            FOURTH_COL, false);
  chessDisplay_displayPiece(PIECE_TYPE_PAWN | PIECE_COLOR_BLACK, SEVENTH_ROW,
                            FIFTH_COL, false);
  chessDisplay_displayPiece(PIECE_TYPE_PAWN | PIECE_COLOR_BLACK, SEVENTH_ROW,
                            SIXTH_COL, false);
  chessDisplay_displayPiece(PIECE_TYPE_PAWN | PIECE_COLOR_BLACK, SEVENTH_ROW,
                            SEVENTH_COL, false);
  chessDisplay_displayPiece(PIECE_TYPE_PAWN | PIECE_COLOR_BLACK, SEVENTH_ROW,
                            EIGHTH_COL, false);
  chessDisplay_displayPiece(PIECE_TYPE_ROOK | PIECE_COLOR_BLACK, EIGHTH_ROW,
                            FIRST_COL, false);
  chessDisplay_displayPiece(PIECE_TYPE_ROOK | PIECE_COLOR_BLACK, EIGHTH_ROW,
                            EIGHTH_COL, false);
  chessDisplay_displayPiece(PIECE_TYPE_KNIGHT | PIECE_COLOR_BLACK, EIGHTH_ROW,
                            SECOND_COL, false);
  chessDisplay_displayPiece(PIECE_TYPE_KNIGHT | PIECE_COLOR_BLACK, EIGHTH_ROW,
                            SEVENTH_COL, false);
  chessDisplay_displayPiece(PIECE_TYPE_BISHOP | PIECE_COLOR_BLACK, EIGHTH_ROW,
                            THIRD_COL, false);
  chessDisplay_displayPiece(PIECE_TYPE_BISHOP | PIECE_COLOR_BLACK, EIGHTH_ROW,
                            SIXTH_COL, false);
  chessDisplay_displayPiece(PIECE_TYPE_QUEEN | PIECE_COLOR_BLACK, EIGHTH_ROW,
                            FOURTH_COL, false);
  chessDisplay_displayPiece(PIECE_TYPE_KING | PIECE_COLOR_BLACK, EIGHTH_ROW,
                            FIFTH_COL, false);
}

void chessDisplay_drawBoard() {
  display_init();
  display_fillScreen(DISPLAY_BLACK);
  drawGrid();
  drawAllPieces();
}

void chessDisplay_touchScreencomputeBoardRowColumn(uint8_t *row,
                                                   uint8_t *column) {
  int16_t x, y;
  uint8_t z;

  display_getTouchedPoint(&x, &y, &z);
  // determine what square (row, col) is being touched
  // assign col number
  if (x < COL_0) {
    *column = FIRST_COL;
  } else if (x < COL_1) {
    *column = SECOND_COL;
  } else if (x < COL_2) {
    *column = THIRD_COL;
  } else if (x < COL_3) {
    *column = FOURTH_COL;
  } else if (x < COL_4) {
    *column = FIFTH_COL;
  } else if (x < COL_5) {
    *column = SIXTH_COL;
  } else if (x < COL_6) {
    *column = SEVENTH_COL;
  } else if (x < COL_7) {
    *column = EIGHTH_COL;
  } else {
    *column = -1;
  }
  // assign row number

  if (y < ROW_7) {
    *row = EIGHTH_ROW;
  } else if (y < ROW_6) {
    *row = SEVENTH_ROW;
  } else if (y < ROW_5) {
    *row = SIXTH_ROW;
  } else if (y < ROW_4) {
    *row = FIFTH_ROW;
  } else if (y < ROW_3) {
    *row = FOURTH_ROW;
  } else if (y < ROW_2) {
    *row = THIRD_ROW;
  } else if (y < ROW_1) {
    *row = SECOND_ROW;
  } else if (y < ROW_0) {
    *row = FIRST_ROW;
  }
}

void displayPawn(uint8_t row, uint8_t col, int16_t color, bool erase) {
  int16_t display_color, bg_color;
  int16_t x_coord;
  int16_t y_coord;

  bg_color = readBGColor(row, col);
  // if erase is true redraw the piece in black, otherwise use white
  if (erase) {
    display_color = bg_color;
  } else {
    display_color = color;
  }
  // determine coords of circle's center depending on row
  if (row == FIRST_ROW) {
    y_coord = ROW_0 - HALF_SQUARE_DIM;
  } else if (row == SECOND_ROW) {
    y_coord = ROW_1 - HALF_SQUARE_DIM;
  } else if (row == THIRD_ROW) {
    y_coord = ROW_2 - HALF_SQUARE_DIM;
  } else if (row == FOURTH_ROW) {
    y_coord = ROW_3 - HALF_SQUARE_DIM;
  } else if (row == FIFTH_ROW) {
    y_coord = ROW_4 - HALF_SQUARE_DIM;
  } else if (row == SIXTH_ROW) {
    y_coord = ROW_5 - HALF_SQUARE_DIM;
  } else if (row == SEVENTH_ROW) {
    y_coord = ROW_6 - HALF_SQUARE_DIM;
  } else if (row == EIGHTH_ROW) {
    y_coord = ROW_7 - HALF_SQUARE_DIM;
  }
  // determine coords of circle's center depending on col
  if (col == FIRST_COL) {
    x_coord = HALF_SQUARE_DIM;
  } else if (col == SECOND_COL) {
    x_coord = COL_1 - HALF_SQUARE_DIM;
  } else if (col == THIRD_COL) {
    x_coord = COL_2 - HALF_SQUARE_DIM;
  } else if (col == FOURTH_COL) {
    x_coord = COL_3 - HALF_SQUARE_DIM;
  } else if (col == FIFTH_COL) {
    x_coord = COL_4 - HALF_SQUARE_DIM;
  } else if (col == SIXTH_COL) {
    x_coord = COL_5 - HALF_SQUARE_DIM;
  } else if (col == SEVENTH_COL) {
    x_coord = COL_6 - HALF_SQUARE_DIM;
  } else if (col == EIGHTH_COL) {
    x_coord = COL_7 - HALF_SQUARE_DIM;
  }

  display_fillCircle(x_coord, y_coord, PAWN_DIM, display_color);
}

void displayRook(uint8_t row, uint8_t col, int16_t color, bool erase) {
  int16_t display_color, bg_color;
  int16_t x_coord;
  int16_t y_coord;

  bg_color = readBGColor(row, col);
  // if erase is true redraw the piece in black, otherwise use white
  if (erase) {
    display_color = bg_color;
  } else {
    display_color = color;
  }
  // determine top left y coord of rect based on row
  if (row == FIRST_ROW) {
    y_coord = ROW_0 - SQUARE_DIM + DIFF_IN_SIZE;
  } else if (row == SECOND_ROW) {
    y_coord = ROW_1 - SQUARE_DIM + DIFF_IN_SIZE;
  } else if (row == THIRD_ROW) {
    y_coord = ROW_2 - SQUARE_DIM + DIFF_IN_SIZE;
  } else if (row == FOURTH_ROW) {
    y_coord = ROW_3 - SQUARE_DIM + DIFF_IN_SIZE;
  } else if (row == FIFTH_ROW) {
    y_coord = ROW_4 - SQUARE_DIM + DIFF_IN_SIZE;
  } else if (row == SIXTH_ROW) {
    y_coord = ROW_5 - SQUARE_DIM + DIFF_IN_SIZE;
  } else if (row == SEVENTH_ROW) {
    y_coord = ROW_6 - SQUARE_DIM + DIFF_IN_SIZE;
  } else if (row == EIGHTH_ROW) {
    y_coord = ROW_7 - SQUARE_DIM + DIFF_IN_SIZE;
  }
  // determine top left x coord of rect based on col
  if (col == FIRST_COL) {
    x_coord = COL_0 - SQUARE_DIM + DIFF_IN_SIZE;
  } else if (col == SECOND_COL) {
    x_coord = COL_1 - SQUARE_DIM + DIFF_IN_SIZE;
  } else if (col == THIRD_COL) {
    x_coord = COL_2 - SQUARE_DIM + DIFF_IN_SIZE;
  } else if (col == FOURTH_COL) {
    x_coord = COL_3 - SQUARE_DIM + DIFF_IN_SIZE;
  } else if (col == FIFTH_COL) {
    x_coord = COL_4 - SQUARE_DIM + DIFF_IN_SIZE;
  } else if (col == SIXTH_COL) {
    x_coord = COL_5 - SQUARE_DIM + DIFF_IN_SIZE;
  } else if (col == SEVENTH_COL) {
    x_coord = COL_6 - SQUARE_DIM + DIFF_IN_SIZE;
  } else if (col == EIGHTH_COL) {
    x_coord = COL_7 - SQUARE_DIM + DIFF_IN_SIZE;
  }

  display_fillRect(x_coord, y_coord, ROOK_DIM, ROOK_DIM, display_color);
}

void displayBishop(uint8_t row, uint8_t col, int16_t color, bool erase) {
  int16_t display_color, bg_color;
  int16_t x_coord1, x_coord2, x_coord3, center_x;
  int16_t y_coord1, y_coord2, y_coord3, center_y;

  bg_color = readBGColor(row, col);
  // if erase is true redraw the piece in black, otherwise use white
  if (erase) {
    display_color = bg_color;
  } else {
    display_color = color;
  }

  // determine y coords of square's center depending on row
  if (row == FIRST_ROW) {
    center_y = ROW_0 - HALF_SQUARE_DIM;
  } else if (row == SECOND_ROW) {
    center_y = ROW_1 - HALF_SQUARE_DIM;
  } else if (row == THIRD_ROW) {
    center_y = ROW_2 - HALF_SQUARE_DIM;
  } else if (row == FOURTH_ROW) {
    center_y = ROW_3 - HALF_SQUARE_DIM;
  } else if (row == FIFTH_ROW) {
    center_y = ROW_4 - HALF_SQUARE_DIM;
  } else if (row == SIXTH_ROW) {
    center_y = ROW_5 - HALF_SQUARE_DIM;
  } else if (row == SEVENTH_ROW) {
    center_y = ROW_6 - HALF_SQUARE_DIM;
  } else if (row == EIGHTH_ROW) {
    center_y = ROW_7 - HALF_SQUARE_DIM;
  }
  // determine x coords of square's center depending on col
  if (col == FIRST_COL) {
    center_x = HALF_SQUARE_DIM;
  } else if (col == SECOND_COL) {
    center_x = COL_1 - HALF_SQUARE_DIM;
  } else if (col == THIRD_COL) {
    center_x = COL_2 - HALF_SQUARE_DIM;
  } else if (col == FOURTH_COL) {
    center_x = COL_3 - HALF_SQUARE_DIM;
  } else if (col == FIFTH_COL) {
    center_x = COL_4 - HALF_SQUARE_DIM;
  } else if (col == SIXTH_COL) {
    center_x = COL_5 - HALF_SQUARE_DIM;
  } else if (col == SEVENTH_COL) {
    center_x = COL_6 - HALF_SQUARE_DIM;
  } else if (col == EIGHTH_COL) {
    center_x = COL_7 - HALF_SQUARE_DIM;
  }

  x_coord1 = center_x;
  x_coord2 = center_x - HALF_SQUARE_DIM + DIFF_IN_SIZE;
  x_coord3 = center_x + HALF_SQUARE_DIM - DIFF_IN_SIZE;
  y_coord1 = center_y - HALF_SQUARE_DIM + DIFF_IN_SIZE;
  y_coord2 = center_y + HALF_SQUARE_DIM - DIFF_IN_SIZE;
  y_coord3 = center_y + HALF_SQUARE_DIM - DIFF_IN_SIZE;

  display_fillTriangle(x_coord1, y_coord1, x_coord2, y_coord2, x_coord3,
                       y_coord3, display_color);
}

void displayKnight(uint8_t row, uint8_t col, int16_t color, bool erase) {
  int16_t display_color, bg_color;
  int16_t center_x, x_coord_rect, x_coord_t1, x_coord_t2, x_coord_t3;
  int16_t center_y, y_coord_rect, y_coord_t1, y_coord_t2, y_coord_t3;

  bg_color = readBGColor(row, col);
  // if erase is true redraw the piece in black, otherwise use white
  if (erase) {
    display_color = bg_color;
  } else {
    display_color = color;
  }
  // determine y coords of square's center depending on row
  if (row == FIRST_ROW) {
    center_y = ROW_0 - HALF_SQUARE_DIM;
  } else if (row == SECOND_ROW) {
    center_y = ROW_1 - HALF_SQUARE_DIM;
  } else if (row == THIRD_ROW) {
    center_y = ROW_2 - HALF_SQUARE_DIM;
  } else if (row == FOURTH_ROW) {
    center_y = ROW_3 - HALF_SQUARE_DIM;
  } else if (row == FIFTH_ROW) {
    center_y = ROW_4 - HALF_SQUARE_DIM;
  } else if (row == SIXTH_ROW) {
    center_y = ROW_5 - HALF_SQUARE_DIM;
  } else if (row == SEVENTH_ROW) {
    center_y = ROW_6 - HALF_SQUARE_DIM;
  } else if (row == EIGHTH_ROW) {
    center_y = ROW_7 - HALF_SQUARE_DIM;
  }
  // determine x coords of square's center depending on col
  if (col == FIRST_COL) {
    center_x = HALF_SQUARE_DIM;
  } else if (col == SECOND_COL) {
    center_x = COL_1 - HALF_SQUARE_DIM;
  } else if (col == THIRD_COL) {
    center_x = COL_2 - HALF_SQUARE_DIM;
  } else if (col == FOURTH_COL) {
    center_x = COL_3 - HALF_SQUARE_DIM;
  } else if (col == FIFTH_COL) {
    center_x = COL_4 - HALF_SQUARE_DIM;
  } else if (col == SIXTH_COL) {
    center_x = COL_5 - HALF_SQUARE_DIM;
  } else if (col == SEVENTH_COL) {
    center_x = COL_6 - HALF_SQUARE_DIM;
  } else if (col == EIGHTH_COL) {
    center_x = COL_7 - HALF_SQUARE_DIM;
  }

  y_coord_rect = center_y - HALF_SQUARE_DIM + DIFF_IN_SIZE;
  x_coord_rect = center_x - HALF_SQUARE_DIM + 8;
  x_coord_t1 = center_x + HALF_SQUARE_DIM - DIFF_IN_SIZE;
  x_coord_t2 = center_x - HALF_SQUARE_DIM + DIFF_IN_SIZE;
  x_coord_t3 = center_x + HALF_SQUARE_DIM - DIFF_IN_SIZE;
  y_coord_t1 = center_y - DIFF_IN_SIZE;
  y_coord_t2 = center_y + HALF_SQUARE_DIM - DIFF_IN_SIZE;
  y_coord_t3 = center_y + HALF_SQUARE_DIM - DIFF_IN_SIZE;
  display_fillTriangle(x_coord_t1, y_coord_t1, x_coord_t2, y_coord_t2,
                       x_coord_t3, y_coord_t3, display_color);
  display_fillRoundRect(x_coord_rect, y_coord_rect, SQUARE_DIM - 12,
                        HALF_SQUARE_DIM - DIFF_IN_SIZE, DIFF_IN_SIZE,
                        display_color);
}

void displayKing(uint8_t row, uint8_t col, int16_t color, bool erase) {
  int16_t display_color, bg_color;
  int16_t x_coord;
  int16_t y_coord;

  bg_color = readBGColor(row, col);
  // if erase is true redraw the piece in black, otherwise use white
  if (erase) {
    display_color = bg_color;
  } else {
    display_color = color;
  }
  // determine top left y coord based on row
  if (row == FIRST_ROW) {
    y_coord = ROW_0 - SQUARE_DIM + CHAR_DIFF_IN_SIZE_Y;
  } else if (row == SECOND_ROW) {
    y_coord = ROW_1 - SQUARE_DIM + CHAR_DIFF_IN_SIZE_Y;
  } else if (row == THIRD_ROW) {
    y_coord = ROW_2 - SQUARE_DIM + CHAR_DIFF_IN_SIZE_Y;
  } else if (row == FOURTH_ROW) {
    y_coord = ROW_3 - SQUARE_DIM + CHAR_DIFF_IN_SIZE_Y;
  } else if (row == FIFTH_ROW) {
    y_coord = ROW_4 - SQUARE_DIM + CHAR_DIFF_IN_SIZE_Y;
  } else if (row == SIXTH_ROW) {
    y_coord = ROW_5 - SQUARE_DIM + CHAR_DIFF_IN_SIZE_Y;
  } else if (row == SEVENTH_ROW) {
    y_coord = ROW_6 - SQUARE_DIM + CHAR_DIFF_IN_SIZE_Y;
  } else if (row == EIGHTH_ROW) {
    y_coord = ROW_7 - SQUARE_DIM + CHAR_DIFF_IN_SIZE_Y;
  }
  // determine top left x coord based on col
  if (col == FIRST_COL) {
    x_coord = COL_0 - SQUARE_DIM + CHAR_DIFF_IN_SIZE_X;
  } else if (col == SECOND_COL) {
    x_coord = COL_1 - SQUARE_DIM + CHAR_DIFF_IN_SIZE_X;
  } else if (col == THIRD_COL) {
    x_coord = COL_2 - SQUARE_DIM + CHAR_DIFF_IN_SIZE_X;
  } else if (col == FOURTH_COL) {
    x_coord = COL_3 - SQUARE_DIM + CHAR_DIFF_IN_SIZE_X;
  } else if (col == FIFTH_COL) {
    x_coord = COL_4 - SQUARE_DIM + CHAR_DIFF_IN_SIZE_X;
  } else if (col == SIXTH_COL) {
    x_coord = COL_5 - SQUARE_DIM + CHAR_DIFF_IN_SIZE_X;
  } else if (col == SEVENTH_COL) {
    x_coord = COL_6 - SQUARE_DIM + CHAR_DIFF_IN_SIZE_X;
  } else if (col == EIGHTH_COL) {
    x_coord = COL_7 - SQUARE_DIM + CHAR_DIFF_IN_SIZE_X;
  }
  display_setCursor(x_coord, y_coord);
  display_setTextSize(CHAR_SIZE);
  display_setTextColor(display_color);
  display_println("K");
}

void displayQueen(uint8_t row, uint8_t col, int16_t color, bool erase) {
  int16_t display_color, bg_color;
  int16_t x_coord;
  int16_t y_coord;

  bg_color = readBGColor(row, col);
  // if erase is true redraw the piece in black, otherwise use white
  if (erase) {
    display_color = bg_color;
  } else {
    display_color = color;
  }
  // determine top left y coord based on row
  if (row == FIRST_ROW) {
    y_coord = ROW_0 - SQUARE_DIM + CHAR_DIFF_IN_SIZE_Y;
  } else if (row == SECOND_ROW) {
    y_coord = ROW_1 - SQUARE_DIM + CHAR_DIFF_IN_SIZE_Y;
  } else if (row == THIRD_ROW) {
    y_coord = ROW_2 - SQUARE_DIM + CHAR_DIFF_IN_SIZE_Y;
  } else if (row == FOURTH_ROW) {
    y_coord = ROW_3 - SQUARE_DIM + CHAR_DIFF_IN_SIZE_Y;
  } else if (row == FIFTH_ROW) {
    y_coord = ROW_4 - SQUARE_DIM + CHAR_DIFF_IN_SIZE_Y;
  } else if (row == SIXTH_ROW) {
    y_coord = ROW_5 - SQUARE_DIM + CHAR_DIFF_IN_SIZE_Y;
  } else if (row == SEVENTH_ROW) {
    y_coord = ROW_6 - SQUARE_DIM + CHAR_DIFF_IN_SIZE_Y;
  } else if (row == EIGHTH_ROW) {
    y_coord = ROW_7 - SQUARE_DIM + CHAR_DIFF_IN_SIZE_Y;
  }
  // determine top left x coord based on col
  if (col == FIRST_COL) {
    x_coord = COL_0 - SQUARE_DIM + CHAR_DIFF_IN_SIZE_X;
  } else if (col == SECOND_COL) {
    x_coord = COL_1 - SQUARE_DIM + CHAR_DIFF_IN_SIZE_X;
  } else if (col == THIRD_COL) {
    x_coord = COL_2 - SQUARE_DIM + CHAR_DIFF_IN_SIZE_X;
  } else if (col == FOURTH_COL) {
    x_coord = COL_3 - SQUARE_DIM + CHAR_DIFF_IN_SIZE_X;
  } else if (col == FIFTH_COL) {
    x_coord = COL_4 - SQUARE_DIM + CHAR_DIFF_IN_SIZE_X;
  } else if (col == SIXTH_COL) {
    x_coord = COL_5 - SQUARE_DIM + CHAR_DIFF_IN_SIZE_X;
  } else if (col == SEVENTH_COL) {
    x_coord = COL_6 - SQUARE_DIM + CHAR_DIFF_IN_SIZE_X;
  } else if (col == EIGHTH_COL) {
    x_coord = COL_7 - SQUARE_DIM + CHAR_DIFF_IN_SIZE_X;
  }
  display_setCursor(x_coord, y_coord);
  display_setTextSize(CHAR_SIZE);
  display_setTextColor(display_color);
  display_println("Q");
}

void chessDisplay_displayPiece(piece_t class, uint8_t row, uint8_t column,
                               bool erase) {
  piece_type_t type = piece_type(class);
  int16_t color =
      (piece_color(class) == PIECE_COLOR_BLACK) ? DISPLAY_BLACK : DISPLAY_WHITE;

  if (type == PIECE_TYPE_PAWN) {
    displayPawn(row, column, color, erase);
  } else if (type == PIECE_TYPE_ROOK) {
    displayRook(row, column, color, erase);
  } else if (type == PIECE_TYPE_KNIGHT) {
    displayKnight(row, column, color, erase);
  } else if (type == PIECE_TYPE_BISHOP) {
    displayBishop(row, column, color, erase);
  } else if (type == PIECE_TYPE_QUEEN) {
    displayQueen(row, column, color, erase);
  } else if (type == PIECE_TYPE_KING) {
    displayKing(row, column, color, erase);
  }
}

void chessDisplay_pieceChosen(piece_t class, uint8_t row, uint8_t column) {
  piece_type_t type = piece_type(class);

  if (type == PIECE_TYPE_PAWN) {
    displayPawn(row, column, DISPLAY_GREEN, false);
  } else if (type == PIECE_TYPE_ROOK) {
    displayRook(row, column, DISPLAY_GREEN, false);
  } else if (type == PIECE_TYPE_KNIGHT) {
    displayKnight(row, column, DISPLAY_GREEN, false);
  } else if (type == PIECE_TYPE_BISHOP) {
    displayBishop(row, column, DISPLAY_GREEN, false);
  } else if (type == PIECE_TYPE_QUEEN) {
    displayQueen(row, column, DISPLAY_GREEN, false);
  } else if (type == PIECE_TYPE_KING) {
    displayKing(row, column, DISPLAY_GREEN, false);
  }
}

void chessDisplay_runTest() {
  int8_t row, column;
  // display_init();
  // display_fillScreen(DISPLAY_BLACK);
  chessDisplay_drawBoard();
  chessDisplay_displayPiece(PIECE_TYPE_QUEEN | PIECE_COLOR_WHITE, FIRST_ROW,
                            FOURTH_COL, true);
  chessDisplay_displayPiece(PIECE_TYPE_PAWN | PIECE_COLOR_WHITE, SECOND_ROW,
                            SEVENTH_COL, true);
  display_clearOldTouchData();
  utils_msDelay(50);
  chessDisplay_touchScreencomputeBoardRowColumn(&row, &column);
  chessDisplay_pieceChosen(PIECE_TYPE_PAWN, row, column);
  printf("row: %d col: %d\n", row, column);
}
