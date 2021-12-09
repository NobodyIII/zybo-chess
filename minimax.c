#include "minimax.h"
#include "board.h"
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

#define SCORE_OVERFLOW_MAX INT_MAX
#define SCORE_OVERFLOW_MIN INT_MIN

#define MAT_VALUE_MULTIPLIER 10

#define SCORE_DEAD_THRESHOLD (1000 * MAT_VALUE_MULTIPLIER)
#define MINIMAX_DEPTH 6

typedef int32_t minimax_score_t;

/* create a copy of a board */
// TODO: potential optimization: use memcpy()
static inline board_t copy_board(const board_t *board) { return *board; }

static inline minimax_score_t score_board(const board_t *board) {
  return board->rel_mat_value_w_b * MAT_VALUE_MULTIPLIER;
}

static inline bool king_is_dead(minimax_score_t minimax_score) {
  return (minimax_score > SCORE_DEAD_THRESHOLD) ||
         (minimax_score * (-1) > SCORE_DEAD_THRESHOLD);
}

static minimax_score_t alphabeta(const board_t *board, int depth,
                                 minimax_score_t alpha, minimax_score_t beta) {
  --depth;

  board_move_list_t move_list;
  board_get_possible_moves(board, &move_list);

  const bool maximizing = !board->last_player_is_white;
  minimax_score_t value = maximizing ? SCORE_OVERFLOW_MIN : SCORE_OVERFLOW_MAX;

  for (int i = 0; i < move_list.length; i++) {
    // TODO: convert to pointer function?
    board_t new_board = copy_board(board);
    board_apply_move(&new_board, move_list.moves[i]);

    /* score board here to avoid excess recursion */
    minimax_score_t new_value = score_board(&new_board);

    /* determine whether we have reached the death of the king (illegal, but
     * useful) */
    if (king_is_dead(new_value)) {
      /* prefer earlier checkmate to later checkmate */
      new_value = maximizing ? new_value + depth * 20 : new_value - depth * 20;
    } else if (depth > 0) {
      /* recurse */
      new_value = alphabeta(&new_board, depth - 1, alpha, beta);
    }

    /* accept/reject new_value */
    if (maximizing) {
      value = MAX(value, new_value);
      alpha = MAX(alpha, value);
    } else {
      value = MIN(value, new_value);
      beta = MIN(beta, value);
    }

    /* are we done yet? */
    if (beta <= alpha)
      break;
  }
  return value;
}

// check for check/checkmate/stalemate
minimax_state_t minimax_get_board_state(const board_t *board) {
  // checkmate/stalemate (ambiguous)
  minimax_score_t score_forward_2 =
      (alphabeta(board, 2, SCORE_OVERFLOW_MIN, SCORE_OVERFLOW_MAX));
  bool game_over = king_is_dead(score_forward_2);

  // check
  board_t null_move_board = copy_board(board);
  null_move_board.last_player_is_white = !board->last_player_is_white;
  minimax_score_t score_forward_null =
      alphabeta(&null_move_board, 1, SCORE_OVERFLOW_MIN, SCORE_OVERFLOW_MAX);
  bool in_check = king_is_dead(score_forward_null);

  if (game_over) {
    return in_check ? MINIMAX_CHECKMATE : MINIMAX_DRAW;
  }
  if (in_check)
    return MINIMAX_CHECK;

  return MINIMAX_NORMAL;
}

static inline minimax_score_t rate_move(const board_t *board, board_move_t move,
                                        minimax_score_t alpha,
                                        minimax_score_t beta) {
  board_t new_board = copy_board(board);
  board_apply_move(&new_board, move);
  return alphabeta(&new_board, MINIMAX_DEPTH - 1, alpha, beta);
}

board_move_t minimax_get_best_move(const board_t *board) {
  const bool maximizing = !board->last_player_is_white;

  board_move_list_t move_list;
  board_get_possible_moves(board, &move_list);

  minimax_score_t alpha = SCORE_OVERFLOW_MIN;
  minimax_score_t beta = SCORE_OVERFLOW_MAX;

  // find best move
  int best_move_index = -1;
  minimax_score_t best_move_value =
      maximizing ? SCORE_OVERFLOW_MIN : SCORE_OVERFLOW_MAX;

  for (int i = 0; i < move_list.length; i++) {
    minimax_score_t new_value =
        rate_move(board, move_list.moves[i], alpha, beta);
    /* accept/reject new_value */
    if (maximizing) {
      if (new_value > best_move_value) {
        best_move_index = i;
        best_move_value = new_value;
        alpha = best_move_value;
      }
    } else {
      if (new_value < best_move_value) {
        best_move_index = i;
        best_move_value = new_value;
        beta = best_move_value;
      }
    }
    /* are we done yet? */
    if (beta <= alpha)
      break;
  }
  return move_list.moves[best_move_index];
}

static void minimax_remove_illegal_moves(const board_t *board,
                                         board_move_list_t *move_list) {
  int i = 0;
  while (i < move_list->length) {
    board_t new_board = copy_board(board);
    board_move_t move = move_list->moves[i];
    board_apply_move(&new_board, move);

    /* prevent moving into check */
    minimax_score_t score_forward_1 =
        (alphabeta(&new_board, 1, SCORE_OVERFLOW_MIN, SCORE_OVERFLOW_MAX));
    bool in_check = king_is_dead(score_forward_1);
    if (in_check) {
      int last_i = move_list->length - 1;
      /* decrease size to remove illegal move */
      move_list->length--;
      if (i < last_i) {
        /* replace move with (possibly) valid move from end */
        move_list->moves[i] = move_list->moves[last_i];
      } else {
        /* no moves left to evaluate */
        return;
      }
    } else {
      /* move is legal; evaluate next move */
      i++;
    }
  }
}

tinybool minimax_is_game_over(const board_t *board) {
  minimax_state_t state = minimax_get_board_state(board);
  return state == MINIMAX_CHECKMATE || state == MINIMAX_DRAW;
}

board_move_list_t minimax_get_legal_moves(const board_t *board) {
  // board_move_list_t moves = board_get_possible_moves(board);
  board_move_list_t move_list;
  board_get_possible_moves(board, &move_list);
  minimax_remove_illegal_moves(board, &move_list);
  return move_list;
}
