#include <stdbool.h>
#include "board.h"

void async_ai_init();

void async_ai_request_move(const board_t *board);

bool async_ai_move_ready();

board_move_t async_ai_get_move();

void async_ai_main();
