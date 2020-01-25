#pragma once

#include "k2_ui.h"

void k2_game_new(gboolean init);

gboolean k2_ui_game_new_menu_item_handler(GtkWidget *widget, gpointer data);

gboolean k2_game_has_8_and_above();

int k2_game_count_blank_block();

gboolean k2_game_new_block_random();

