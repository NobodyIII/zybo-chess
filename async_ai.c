// #include "board.h"
#include "async_ai.h"
#include "minimax.h"
#include "utils.h"
#include <stdio.h>

static board_t current_board;
static board_move_t ai_move;
static bool move_requested = false;
static bool move_ready = false;

static inline void fence() {
#ifdef BOARD
  __asm("dmb");
#else
  __asm("mfence");
#endif
}

void async_ai_init() {
  // nothing to do here?
}

void async_ai_request_move(const board_t *board) {
  // __disable_interrupts();
  if (move_requested || move_ready)
    printf("error: requested new move before getting the previous move\n");
  current_board = *board;
  fence();
  move_requested = true;
  // __enable_interrupts();
}

bool async_ai_move_ready() { return move_ready; }

board_move_t async_ai_get_move() {
  if (!move_ready)
    printf("error: read move before computing it\n");

  board_move_t ret = ai_move;
  fence();
  move_requested = false;
  move_ready = false;
  return ret;
}

void async_ai_main() {
  for (;;) {
    if (move_requested) {
      ai_move = minimax_get_best_move(&current_board);
      fence();
      move_ready = true;
      fence();
      move_requested = false;
    }
    utils_sleep();
  }
}
