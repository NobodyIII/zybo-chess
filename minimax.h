#ifndef MINIMAX_H
#define MINIMAX_H

#include "board.h"

typedef enum {
    MINIMAX_NORMAL,
    MINIMAX_CHECK,
    MINIMAX_CHECKMATE,
    MINIMAX_DRAW
} minimax_state_t;

board_move_t minimax_get_best_move(const board_t *board);
minimax_state_t minimax_get_board_state(const board_t *board);
// void minimax_remove_illegal_moves(const board_t *board, board_move_list_t *move_list);
board_move_list_t minimax_get_legal_moves(const board_t *board);

tinybool minimax_is_game_over(const board_t *board);

#endif
