#include "chessControl.h"
#include "async_ai.h"
#include "board.h"
#include "buttons.h"
#include "chessDisplay.h"
#include "config.h"
#include "display.h"
#include "minimax.h"
#include "switches.h"
#include <stdio.h>

#define INIT_ST_MSG "init_st\n"
#define START_GAME_ST_MSG "start_game_st\n"
#define SELECT_PIECE_ST_MSG "select_piece_st\n"
#define VERIFY_PIECE_ST_MSG "verify_piece_st\n"
#define SELECT_MOVE_ST_MSG "select_move_st\n"
#define VERIFY_MOVE_ST_MSG "verify_move_st\n"
#define AI_TURN_ST_MSG "ai_turn_st\n"
#define GAME_OVER_ST_MSG "game_over_st\n"
#define ADC_ST_MSG "adc_st\n"
#define UPDATE_BOARD_ST_MSG "update_board_st\n"
#define ERROR_MSG "ERROR: Invalid state encountered\n"

#define ERASE true
#define DRAW false

#define SW_TWO_PLAYER SWITCHES_SW0_MASK
#define BTN_RESET BUTTONS_BTN0_MASK

#define ADC_DELAY (uint8_t)(50E-3 / CONFIG_TIMER_PERIOD)

#define ADC(NEXT)                                                              \
  display_clearOldTouchData();                                                 \
  currentState = adc_st;                                                       \
  nextState = NEXT;

#define UPDATE_BOARD(NEXT)                                                     \
  currentState = update_board_st;                                              \
  nextState = NEXT;

#define MSG_SIZE 4
#define MSG_CURSOR SQUARE_DIM / 2, DISPLAY_HEIGHT / 2 - SQUARE_DIM / 2
#define MSG_COLOR DISPLAY_WHITE
#define MSG_BG_COLOR DISPLAY_BLACK
#define GAME_OVER_MSG "GAME OVER"

#define PRINT_MSG(MSG)                                                         \
  display_setCursor(MSG_CURSOR);                                               \
  display_setTextSize(MSG_SIZE);                                               \
  display_setTextColorBg(MSG_COLOR, MSG_BG_COLOR);                             \
  display_println(MSG);

// The different states of the state machine
static enum chessControl_st_t {
  init_st,         // The state that is initialized to
  start_game_st,   // Start game
  select_piece_st, // Let user choose a piece
  verify_piece_st, // Verify the user touched a piece
  select_move_st,  // Let user select a move
  verify_move_st,  // Verify the user touched a valid move
  ai_turn_st,      // Let the AI take its turn
  game_over_st,    // Game over

  adc_st,         // Wait for ADC to settle
  update_board_st // Update the board
} currentState,
    nextState;

// State machine variables
static uint8_t adc_counter;
static board_t board;
static piece_color_t player_color;
static bool two_player;
static uint8_t piece_row;
static uint8_t piece_col;
static uint8_t move_row;
static uint8_t move_col;
static board_move_list_t moves;
static bool has_moves;
static board_move_t current_move;

/* Helper functions */

// Checks if the touched coordinates contains a piece of the correct color
static inline bool is_valid_piece() {
  if (piece_col < 0 ||
      piece_type(board.pieces[piece_row][piece_col]) == PIECE_TYPE_NULL)
    return false;
  return piece_color(board.pieces[piece_row][piece_col]) == player_color;
}

// Checks if the touched coordinates are a valid move for the selected piece
static inline bool is_valid_move() {
  if (move_col < 0)
    return false;
  for (uint8_t i = 0; i < moves.length; ++i) {
    if (moves.moves[i].start_row == piece_row &&
        moves.moves[i].start_col == piece_col &&
        moves.moves[i].end_row == move_row &&
        moves.moves[i].end_col == move_col)
      return true;
  }
  return false;
}

// Debug function that prints the state as it is entered
static void debugStatePrint() {
  static enum chessControl_st_t previousState;
  static bool firstPass = true;
  // Only print the message if:
  // 1. This is the first pass and the value for previousState is unknown.
  // 2. previousState != currentState - this prevents reprinting the same state
  // name over and over.
  if (previousState != currentState || firstPass) {
    firstPass = false; // previousState will be defined, firstPass is false.
    previousState =
        currentState; // keep track of the last state that you were in.
    // Print the correct message
    switch (currentState) {
    case init_st:
      printf(INIT_ST_MSG);
      break;

    case start_game_st:
      printf(START_GAME_ST_MSG);
      break;

    case select_piece_st:
      printf(SELECT_PIECE_ST_MSG);
      break;

    case verify_piece_st:
      printf(VERIFY_PIECE_ST_MSG);
      break;

    case select_move_st:
      printf(SELECT_MOVE_ST_MSG);
      break;

    case verify_move_st:
      printf(VERIFY_MOVE_ST_MSG);
      break;

    case ai_turn_st:
      printf(AI_TURN_ST_MSG);
      break;

    case game_over_st:
      printf(GAME_OVER_ST_MSG);
      break;

    case adc_st:
      printf(ADC_ST_MSG);
      break;

    case update_board_st:
      printf(UPDATE_BOARD_ST_MSG);
      break;

    default:
      printf(ERROR_MSG);
      break;
    }
  }
}

static void make_move(board_move_t move) {
  board_move_t move_simplified = board_simplify_move(move);

  // remove piece where move begins
  chessDisplay_displayPiece(
      board.pieces[move_simplified.start_row][move_simplified.start_col],
      move_simplified.start_row, move_simplified.start_col, ERASE);

  // remove piece where move ends
  chessDisplay_displayPiece(
      board.pieces[move_simplified.end_row][move_simplified.end_col],
      move_simplified.end_row, move_simplified.end_col, ERASE);

  // apply move
  board_apply_move(&board, move);

  // draw piece where move ends
  chessDisplay_displayPiece(
      board.pieces[move_simplified.end_row][move_simplified.end_col],
      move_simplified.end_row, move_simplified.end_col, DRAW);
  // TODO - DRAW Castling
}

// Inits the SM
void chessControl_init() {
  currentState = init_st;
  // Create board
  board = board_create_init();
  // Draw board
  chessDisplay_drawBoard();
  // Init 2-player switch & reset button
  switches_init();
  buttons_init();
}

// Ticks the SM
void chessControl_tick() {
  // Debug printing
  debugStatePrint();

  // Reset
  if (buttons_read() & BTN_RESET)
    chessControl_init();

  // State transitions
  switch (currentState) {
  case init_st:
    currentState = start_game_st;
    adc_counter = 0;
    has_moves = false;
    player_color = PIECE_COLOR_WHITE;
    break;

  case start_game_st:
    // TODO - Let AI go first
    currentState = select_piece_st;
    break;

  case select_piece_st:
    // Wait for user to touch a piece
    if (display_isTouched()) {
      ADC(verify_piece_st)
    }
    break;

  case verify_piece_st:
    if (is_valid_piece()) {
      // TODO - Draw possible moves
      currentState = select_move_st;
    } else
      currentState = select_piece_st;
    break;

  case select_move_st:
    // Wait for user to touch a square
    if (display_isTouched()) {
      ADC(verify_move_st)
    }
    break;

  case verify_move_st:
    if (is_valid_move()) {
      current_move = (board_move_t){piece_row, piece_col, move_row, move_col};
      if (two_player) {
        UPDATE_BOARD(select_piece_st)
        player_color = player_color == PIECE_COLOR_BLACK ? PIECE_COLOR_WHITE
                                                         : PIECE_COLOR_BLACK;
      } else {
        UPDATE_BOARD(ai_turn_st)
        async_ai_request_move(&board);
      }
    } else
      currentState = select_move_st;
    break;

  case ai_turn_st:
    if (async_ai_move_ready()) {
      current_move = async_ai_get_move();
      UPDATE_BOARD(select_piece_st)
    }
    break;

  case game_over_st:
    break;

  case adc_st:
    if (adc_counter > ADC_DELAY) {
      adc_counter = 0;
      currentState = nextState;
    }
    break;

  case update_board_st:
    if (minimax_is_game_over(&board)) {
      currentState = game_over_st;
      PRINT_MSG(GAME_OVER_MSG)
    } else
      currentState = nextState;
    break;

  default:
    printf(ERROR_MSG);
    break;
  }

  // State actions
  switch (currentState) {
  case init_st:
    break;

  case start_game_st:
    two_player = switches_read() & SW_TWO_PLAYER;
    break;

  case select_piece_st:
    if (!has_moves) {
      moves = minimax_get_legal_moves(&board);
      has_moves = true;
    }
    break;

  case verify_piece_st:
    chessDisplay_touchScreencomputeBoardRowColumn(&piece_row, &piece_col);
    printf("Piece location: %d %d\n", piece_row, piece_col);
    break;

  case select_move_st:
    break;

  case verify_move_st:
    chessDisplay_touchScreencomputeBoardRowColumn(&move_row, &move_col);
    printf("Move location: %d %d\n", move_row, move_col);
    break;

  case ai_turn_st:
    break;

  case game_over_st:
    break;

  case adc_st:
    ++adc_counter;
    break;

  case update_board_st:
    make_move(current_move);
    // Moves have updated
    has_moves = false;
    break;

  default:
    printf(ERROR_MSG);
    break;
  }
}
