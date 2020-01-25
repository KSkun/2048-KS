#include "k2_game.h"

void k2_game_new(gboolean init) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			k2_ui_game_init_label(&k2_ui_game_label[i][j], &k2_ui_game_event_box[i][j], "", K2_UI_GAME_BLANK_COLOR, K2_UI_GAME_2_COLOR, K2_UI_GAME_FONT_1, !init);
			k2_ui_game_val[i][j] = 0;
			gtk_fixed_put(GTK_FIXED(k2_ui_fixed), k2_ui_game_event_box[i][j], 40 + 90 * i, 160 + 90 * j);
		}
	}

	int i1 = k2_rand_int(0, 4), j1 = k2_rand_int(0, 4);
	k2_ui_game_init_label(&k2_ui_game_label[i1][j1], &k2_ui_game_event_box[i1][j1], "2", K2_UI_GAME_2_COLOR, K2_UI_TEXT_COLOR, K2_UI_GAME_FONT_1, TRUE);
	k2_ui_game_val[i1][j1] = 2;
	gtk_fixed_put(GTK_FIXED(k2_ui_fixed), k2_ui_game_event_box[i1][j1], 40 + 90 * i1, 160 + 90 * j1);

	int i2 = k2_rand_int(0, 4), j2 = k2_rand_int(0, 4);
	while (i2 == i1 && j2 == j1) {
		i2 = k2_rand_int(0, 4); j2 = k2_rand_int(0, 4);
	}
	k2_ui_game_init_label(&k2_ui_game_label[i2][j2], &k2_ui_game_event_box[i2][j2], "2", K2_UI_GAME_2_COLOR, K2_UI_TEXT_COLOR, K2_UI_GAME_FONT_1, TRUE);
	k2_ui_game_val[i2][j2] = 2;
	gtk_fixed_put(GTK_FIXED(k2_ui_fixed), k2_ui_game_event_box[i2][j2], 40 + 90 * i2, 160 + 90 * j2);

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			gtk_widget_show_all(k2_ui_game_event_box[i][j]);
		}
	}
}

gboolean k2_ui_game_new_menu_item_handler(GtkWidget *widget, gpointer data) {
	k2_game_new(FALSE);
	return TRUE;
}

gboolean k2_game_has_8_and_above() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (k2_ui_game_val[i][j] >= 8) return TRUE;
		}
	}
	return FALSE;
}

int k2_game_count_blank_block() {
	int cnt = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (k2_ui_game_val[i][j] == 0) cnt++;
		}
	}
	return cnt;
}

gboolean k2_game_new_block_random() { // returns FALSE if no new block can be placed
	int rand_val = k2_rand_int(0, 10), val = 2;
	if (rand_val >= 6 && k2_game_has_8_and_above()) val = 4;

	int blank_cnt = k2_game_count_blank_block();
	if (blank_cnt == 0) return FALSE;

	int i, j;
	rand_val = k2_rand_int(0, blank_cnt);
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (k2_ui_game_val[i][j] == 0) {
				if (blank_cnt == 0) break;
				blank_cnt--;
			}
		}
		if (blank_cnt == 0) break;
	}

	if (val == 2) {
		k2_ui_game_init_label(&k2_ui_game_label[i][j], &k2_ui_game_event_box[i][j], "2", K2_UI_GAME_2_COLOR, K2_UI_TEXT_COLOR, K2_UI_GAME_FONT_1, TRUE);
		gtk_widget_show_all(k2_ui_game_event_box[i][j]);
	} else {
		k2_ui_game_init_label(&k2_ui_game_label[i][j], &k2_ui_game_event_box[i][j], "4", K2_UI_GAME_4_COLOR, K2_UI_TEXT_COLOR, K2_UI_GAME_FONT_1, TRUE);
		gtk_widget_show_all(k2_ui_game_event_box[i][j]);
	}
	return TRUE;
}
