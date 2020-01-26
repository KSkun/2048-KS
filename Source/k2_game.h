#pragma once

#include <string.h>

#include "k2_ui.h"

enum k2_game_direction_enum {
	K2_DIR_UP, K2_DIR_DOWN, K2_DIR_LEFT, K2_DIR_RIGHT
};

typedef enum k2_game_direction_enum k2_game_direction;

void k2_game_new(gboolean init);

gboolean k2_game_has_8_and_above();

int k2_game_count_blank_block(int val[][4]);

gboolean k2_game_new_block_random();

gboolean k2_game_is_lost();

gboolean k2_game_do_move(k2_game_direction dir);