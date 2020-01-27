#include "k2_game.h"

int k2_game_val[4][4], k2_game_score, k2_best_score;

void k2_game_new(gboolean init) {
	if (k2_game_score > k2_best_score) {
		k2_best_score = k2_game_score;
		gtk_label_set_text(GTK_LABEL(k2_ui_best_text_label), k2_itoa(k2_best_score));
	}
	k2_game_score = 0;
	gtk_label_set_text(GTK_LABEL(k2_ui_score_text_label), k2_itoa(k2_game_score));

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			k2_ui_game_init_label_with_val(&k2_ui_game_label[i][j], &k2_ui_game_event_box[i][j], 0, !init);
			k2_game_val[i][j] = 0;
			gtk_fixed_put(GTK_FIXED(k2_ui_fixed), k2_ui_game_event_box[i][j], 40 + 90 * j, 160 + 90 * i);
		}
	}

	int i1 = k2_rand_int(0, 4), j1 = k2_rand_int(0, 4);
	k2_ui_game_init_label_with_val(&k2_ui_game_label[i1][j1], &k2_ui_game_event_box[i1][j1], 2, TRUE);
	k2_game_val[i1][j1] = 2;
	gtk_fixed_put(GTK_FIXED(k2_ui_fixed), k2_ui_game_event_box[i1][j1], 40 + 90 * j1, 160 + 90 * i1);

	int i2 = k2_rand_int(0, 4), j2 = k2_rand_int(0, 4);
	while (i2 == i1 && j2 == j1) {
		i2 = k2_rand_int(0, 4); j2 = k2_rand_int(0, 4);
	}
	k2_ui_game_init_label_with_val(&k2_ui_game_label[i2][j2], &k2_ui_game_event_box[i2][j2], 2, TRUE);
	k2_game_val[i2][j2] = 2;
	gtk_fixed_put(GTK_FIXED(k2_ui_fixed), k2_ui_game_event_box[i2][j2], 40 + 90 * j2, 160 + 90 * i2);

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			gtk_widget_show_all(k2_ui_game_event_box[i][j]);
		}
	}
}

gboolean k2_game_has_8_and_above() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (k2_game_val[i][j] >= 8) return TRUE;
		}
	}
	return FALSE;
}

int k2_game_count_blank_block(int val[][4]) {
	int cnt = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (val[i][j] == 0) cnt++;
		}
	}
	return cnt;
}

gboolean k2_game_new_block_random() { // returns FALSE if no new block can be placed
	int rand_val = k2_rand_int(0, 10), val = 2;
	if (rand_val >= 6 && k2_game_has_8_and_above()) val = 4;

	int blank_cnt = k2_game_count_blank_block(k2_game_val);
	if (blank_cnt == 0) return FALSE;

	int i, j;
	rand_val = k2_rand_int(0, blank_cnt);
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (k2_game_val[i][j] == 0) {
				if (rand_val == 0) break;
				rand_val--;
			}
		}
		if (j < 4 && rand_val == 0) break;
	}

	k2_ui_game_init_label_with_val(&k2_ui_game_label[i][j], &k2_ui_game_event_box[i][j], val, TRUE);
	k2_game_val[i][j] = val;
	gtk_fixed_put(GTK_FIXED(k2_ui_fixed), k2_ui_game_event_box[i][j], 40 + 90 * j, 160 + 90 * i);
	gtk_widget_show_all(k2_ui_game_event_box[i][j]);
	return TRUE;
}

gboolean k2_game_is_win() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (k2_game_val[i][j] == 4096) return TRUE;
		}
	}
	return FALSE;
}

gboolean k2_game_is_lose() {
	static int val[4][4];
	static gboolean merged[4][4];
	gboolean up_full = FALSE, down_full = FALSE, left_full = FALSE, right_full = FALSE;

	// up
	memcpy(val, k2_game_val, sizeof(val));
	memset(merged, 0, sizeof(merged));
	for (int i = 1; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			gboolean moved = FALSE;
			for (int k = i - 1; k >= 0; k--) {
				if (val[k][j] != 0) {
					if (k + 1 == i && (val[k][j] != val[i][j] || merged[k][j])) {
						moved = TRUE;
						break;
					}
					if (val[k][j] == val[i][j] && !merged[k][j]) {
						val[k][j] += val[i][j];
						merged[k][j] = TRUE;
					} else {
						val[k + 1][j] = val[i][j];
					}
					val[i][j] = 0;
					moved = TRUE;
					break;
				}
			}
			if (!moved) {
				val[0][j] = val[i][j];
				val[i][j] = 0;
			}
		}
	}
	up_full = k2_game_count_blank_block(val) == 0;
	
	// down
	memcpy(val, k2_game_val, sizeof(val));
	memset(merged, 0, sizeof(merged));
	for (int i = 2; i >= 0; i--) {
		for (int j = 0; j < 4; j++) {
			gboolean moved = FALSE;
			for (int k = i + 1; k < 4; k++) {
				if (val[k][j] != 0) {
					if (k - 1 == i && (val[k][j] != val[i][j] || merged[k][j])) {
						moved = TRUE;
						break;
					}
					if (val[k][j] == val[i][j] && !merged[k][j]) {
						val[k][j] += val[i][j];
						merged[k][j] = TRUE;
					} else {
						val[k - 1][j] = val[i][j];
					}
					val[i][j] = 0;
					moved = TRUE;
					break;
				}
			}
			if (!moved) {
				val[3][j] = val[i][j];
				val[i][j] = 0;
			}
		}
	}
	down_full = k2_game_count_blank_block(val) == 0;

	// left
	memcpy(val, k2_game_val, sizeof(val));
	memset(merged, 0, sizeof(merged));
	for (int j = 1; j < 4; j++) {
		for (int i = 0; i < 4; i++) {
			gboolean moved = FALSE;
			for (int k = j - 1; k >= 0; k--) {
				if (val[i][k] != 0) {
					if (k + 1 == j && (val[i][k] != val[i][j] || merged[i][k])) {
						moved = TRUE;
						break;
					}
					if (val[i][k] == val[i][j] && !merged[i][k]) {
						val[i][k] += val[i][j];
						merged[i][k] = TRUE;
					} else {
						val[i][k + 1] = val[i][j];
					}
					val[i][j] = 0;
					moved = TRUE;
					break;
				}
			}
			if (!moved) {
				val[i][0] = val[i][j];
				val[i][j] = 0;
			}
		}
	}
	left_full = k2_game_count_blank_block(val) == 0;

	// right
	memcpy(val, k2_game_val, sizeof(val));
	memset(merged, 0, sizeof(merged));
	for (int j = 2; j >= 0; j--) {
		for (int i = 0; i < 4; i++) {
			gboolean moved = FALSE;
			for (int k = j + 1; k < 4; k++) {
				if (val[i][k] != 0) {
					if (k - 1 == j && (val[i][k] != val[i][j] || merged[i][k])) {
						moved = TRUE;
						break;
					}
					if (val[i][k] == val[i][j] && !merged[i][k]) {
						val[i][k] += val[i][j];
						merged[i][k] = TRUE;
					} else {
						val[i][k - 1] = val[i][j];
					}
					val[i][j] = 0;
					moved = TRUE;
					break;
				}
			}
			if (!moved) {
				val[i][3] = val[i][j];
				val[i][j] = 0;
			}
		}
	}
	right_full = k2_game_count_blank_block(val) == 0;

	return up_full && down_full && left_full && right_full;
}

gboolean k2_game_comp_val(int val1[][4], int val2[][4]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (val1[i][j] != val2[i][j]) return FALSE;
		}
	}
	return TRUE;
}

gboolean k2_game_do_move(k2_game_direction dir, int *score) {
	*score = 0;
	static int old_val[4][4];
	static gboolean merged[4][4];
	memset(merged, 0, sizeof(merged));
	memcpy(old_val, k2_game_val, sizeof(old_val));
	switch (dir) {
	case K2_DIR_UP:
		for (int i = 1; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				gboolean moved = FALSE;
				for (int k = i - 1; k >= 0; k--) {
					if (k2_game_val[k][j] != 0) {
						if (k + 1 == i && (k2_game_val[k][j] != k2_game_val[i][j] || merged[k][j])) {
							moved = TRUE;
							break;
						}
						if (k2_game_val[k][j] == k2_game_val[i][j] && !merged[k][j]) {
							k2_game_val[k][j] += k2_game_val[i][j];
							*score += k2_game_val[k][j];
							k2_ui_game_init_label_with_val(&k2_ui_game_label[k][j], &k2_ui_game_event_box[k][j], k2_game_val[k][j], TRUE);
							gtk_fixed_put(GTK_FIXED(k2_ui_fixed), k2_ui_game_event_box[k][j], 40 + 90 * j, 160 + 90 * k); 
							gtk_widget_show_all(k2_ui_game_event_box[k][j]);
							merged[k][j] = TRUE;
						} else {
							k2_game_val[k + 1][j] = k2_game_val[i][j];
							k2_ui_game_init_label_with_val(&k2_ui_game_label[k + 1][j], &k2_ui_game_event_box[k + 1][j], k2_game_val[k + 1][j], TRUE);
							gtk_fixed_put(GTK_FIXED(k2_ui_fixed), k2_ui_game_event_box[k + 1][j], 40 + 90 * j, 160 + 90 * (k + 1)); gtk_widget_show_all(k2_ui_game_event_box[k + 1][j]);
							gtk_widget_show_all(k2_ui_game_event_box[k + 1][j]);
						}
						k2_game_val[i][j] = 0;
						k2_ui_game_init_label_with_val(&k2_ui_game_label[i][j], &k2_ui_game_event_box[i][j], k2_game_val[i][j], TRUE);
						gtk_fixed_put(GTK_FIXED(k2_ui_fixed), k2_ui_game_event_box[i][j], 40 + 90 * j, 160 + 90 * i);
						gtk_widget_show_all(k2_ui_game_event_box[i][j]);
						moved = TRUE;
						break;
					}
				}
				if (!moved) {
					k2_game_val[0][j] = k2_game_val[i][j];
					k2_ui_game_init_label_with_val(&k2_ui_game_label[0][j], &k2_ui_game_event_box[0][j], k2_game_val[0][j], TRUE);
					gtk_fixed_put(GTK_FIXED(k2_ui_fixed), k2_ui_game_event_box[0][j], 40 + 90 * j, 160 + 90 * 0);
					gtk_widget_show_all(k2_ui_game_event_box[0][j]);
					k2_game_val[i][j] = 0;
					k2_ui_game_init_label_with_val(&k2_ui_game_label[i][j], &k2_ui_game_event_box[i][j], k2_game_val[i][j], TRUE);
					gtk_fixed_put(GTK_FIXED(k2_ui_fixed), k2_ui_game_event_box[i][j], 40 + 90 * j, 160 + 90 * i);
					gtk_widget_show_all(k2_ui_game_event_box[i][j]);
				}
			}
		}
		break;
	case K2_DIR_DOWN:
		for (int i = 2; i >= 0; i--) {
			for (int j = 0; j < 4; j++) {
				gboolean moved = FALSE;
				for (int k = i + 1; k < 4; k++) {
					if (k2_game_val[k][j] != 0) {
						if (k - 1 == i && (k2_game_val[k][j] != k2_game_val[i][j] || merged[k][j])) {
							moved = TRUE;
							break;
						}
						if (k2_game_val[k][j] == k2_game_val[i][j] && !merged[k][j]) {
							k2_game_val[k][j] += k2_game_val[i][j];
							*score += k2_game_val[k][j];
							k2_ui_game_init_label_with_val(&k2_ui_game_label[k][j], &k2_ui_game_event_box[k][j], k2_game_val[k][j], TRUE);
							gtk_fixed_put(GTK_FIXED(k2_ui_fixed), k2_ui_game_event_box[k][j], 40 + 90 * j, 160 + 90 * k);
							gtk_widget_show_all(k2_ui_game_event_box[k][j]);
							merged[k][j] = TRUE;
						} else {
							k2_game_val[k - 1][j] = k2_game_val[i][j];
							k2_ui_game_init_label_with_val(&k2_ui_game_label[k - 1][j], &k2_ui_game_event_box[k - 1][j], k2_game_val[k - 1][j], TRUE);
							gtk_fixed_put(GTK_FIXED(k2_ui_fixed), k2_ui_game_event_box[k - 1][j], 40 + 90 * j, 160 + 90 * (k - 1));
							gtk_widget_show_all(k2_ui_game_event_box[k - 1][j]);
						}
						k2_game_val[i][j] = 0;
						k2_ui_game_init_label_with_val(&k2_ui_game_label[i][j], &k2_ui_game_event_box[i][j], k2_game_val[i][j], TRUE);
						gtk_fixed_put(GTK_FIXED(k2_ui_fixed), k2_ui_game_event_box[i][j], 40 + 90 * j, 160 + 90 * i);
						gtk_widget_show_all(k2_ui_game_event_box[i][j]);
						moved = TRUE;
						break;
					}
				}
				if (!moved) {
					k2_game_val[3][j] = k2_game_val[i][j];
					k2_ui_game_init_label_with_val(&k2_ui_game_label[3][j], &k2_ui_game_event_box[3][j], k2_game_val[3][j], TRUE);
					gtk_fixed_put(GTK_FIXED(k2_ui_fixed), k2_ui_game_event_box[3][j], 40 + 90 * j, 160 + 90 * 3);
					gtk_widget_show_all(k2_ui_game_event_box[3][j]);
					k2_game_val[i][j] = 0;
					k2_ui_game_init_label_with_val(&k2_ui_game_label[i][j], &k2_ui_game_event_box[i][j], k2_game_val[i][j], TRUE);
					gtk_fixed_put(GTK_FIXED(k2_ui_fixed), k2_ui_game_event_box[i][j], 40 + 90 * j, 160 + 90 * i);
					gtk_widget_show_all(k2_ui_game_event_box[i][j]);
				}
			}
		}
		break;
	case K2_DIR_LEFT:
		for (int j = 1; j < 4; j++) {
			for (int i = 0; i < 4; i++) {
				gboolean moved = FALSE;
				for (int k = j - 1; k >= 0; k--) {
					if (k2_game_val[i][k] != 0) {
						if (k + 1 == j && (k2_game_val[i][k] != k2_game_val[i][j] || merged[i][k])) {
							moved = TRUE;
							break;
						}
						if (k2_game_val[i][k] == k2_game_val[i][j] && !merged[i][k]) {
							k2_game_val[i][k] += k2_game_val[i][j];
							*score += k2_game_val[i][k];
							k2_ui_game_init_label_with_val(&k2_ui_game_label[i][k], &k2_ui_game_event_box[i][k], k2_game_val[i][k], TRUE);
							gtk_fixed_put(GTK_FIXED(k2_ui_fixed), k2_ui_game_event_box[i][k], 40 + 90 * k, 160 + 90 * i);
							gtk_widget_show_all(k2_ui_game_event_box[i][k]);
							merged[i][k] = TRUE;
						} else {
							k2_game_val[i][k + 1] = k2_game_val[i][j];
							k2_ui_game_init_label_with_val(&k2_ui_game_label[i][k + 1], &k2_ui_game_event_box[i][k + 1], k2_game_val[i][k + 1], TRUE);
							gtk_fixed_put(GTK_FIXED(k2_ui_fixed), k2_ui_game_event_box[i][k + 1], 40 + 90 * (k + 1), 160 + 90 * i);
							gtk_widget_show_all(k2_ui_game_event_box[i][k + 1]);
						}
						k2_game_val[i][j] = 0;
						k2_ui_game_init_label_with_val(&k2_ui_game_label[i][j], &k2_ui_game_event_box[i][j], k2_game_val[i][j], TRUE);
						gtk_fixed_put(GTK_FIXED(k2_ui_fixed), k2_ui_game_event_box[i][j], 40 + 90 * j, 160 + 90 * i);
						gtk_widget_show_all(k2_ui_game_event_box[i][j]);
						moved = TRUE;
						break;
					}
				}
				if (!moved) {
					k2_game_val[i][0] = k2_game_val[i][j];
					k2_ui_game_init_label_with_val(&k2_ui_game_label[i][0], &k2_ui_game_event_box[i][0], k2_game_val[i][0], TRUE);
					gtk_fixed_put(GTK_FIXED(k2_ui_fixed), k2_ui_game_event_box[i][0], 40 + 90 * 0, 160 + 90 * i);
					gtk_widget_show_all(k2_ui_game_event_box[i][0]);
					k2_game_val[i][j] = 0;
					k2_ui_game_init_label_with_val(&k2_ui_game_label[i][j], &k2_ui_game_event_box[i][j], k2_game_val[i][j], TRUE);
					gtk_fixed_put(GTK_FIXED(k2_ui_fixed), k2_ui_game_event_box[i][j], 40 + 90 * j, 160 + 90 * i);
					gtk_widget_show_all(k2_ui_game_event_box[i][j]);
				}
			}
		}
		break;
	case K2_DIR_RIGHT:
		for (int j = 2; j >= 0; j--) {
			for (int i = 0; i < 4; i++) {
				gboolean moved = FALSE;
				for (int k = j + 1; k < 4; k++) {
					if (k2_game_val[i][k] != 0) {
						if (k - 1 == j && (k2_game_val[i][k] != k2_game_val[i][j] || merged[i][k])) {
							moved = TRUE;
							break;
						}
						if (k2_game_val[i][k] == k2_game_val[i][j] && !merged[i][k]) {
							k2_game_val[i][k] += k2_game_val[i][j];
							*score += k2_game_val[i][k];
							k2_ui_game_init_label_with_val(&k2_ui_game_label[i][k], &k2_ui_game_event_box[i][k], k2_game_val[i][k], TRUE);
							gtk_fixed_put(GTK_FIXED(k2_ui_fixed), k2_ui_game_event_box[i][k], 40 + 90 * k, 160 + 90 * i);
							gtk_widget_show_all(k2_ui_game_event_box[i][k]);
							merged[i][k] = TRUE;
						} else {
							k2_game_val[i][k - 1] = k2_game_val[i][j];
							k2_ui_game_init_label_with_val(&k2_ui_game_label[i][k - 1], &k2_ui_game_event_box[i][k - 1], k2_game_val[i][k - 1], TRUE);
							gtk_fixed_put(GTK_FIXED(k2_ui_fixed), k2_ui_game_event_box[i][k - 1], 40 + 90 * (k - 1), 160 + 90 * i);
							gtk_widget_show_all(k2_ui_game_event_box[i][k - 1]);
						}
						k2_game_val[i][j] = 0;
						k2_ui_game_init_label_with_val(&k2_ui_game_label[i][j], &k2_ui_game_event_box[i][j], k2_game_val[i][j], TRUE);
						gtk_fixed_put(GTK_FIXED(k2_ui_fixed), k2_ui_game_event_box[i][j], 40 + 90 * j, 160 + 90 * i);
						gtk_widget_show_all(k2_ui_game_event_box[i][j]);
						moved = TRUE;
						break;
					}
				}
				if (!moved) {
					k2_game_val[i][3] = k2_game_val[i][j];
					k2_ui_game_init_label_with_val(&k2_ui_game_label[i][3], &k2_ui_game_event_box[i][3], k2_game_val[i][3], TRUE);
					gtk_fixed_put(GTK_FIXED(k2_ui_fixed), k2_ui_game_event_box[i][3], 40 + 90 * 3, 160 + 90 * i);
					gtk_widget_show_all(k2_ui_game_event_box[i][3]);
					k2_game_val[i][j] = 0;
					k2_ui_game_init_label_with_val(&k2_ui_game_label[i][j], &k2_ui_game_event_box[i][j], k2_game_val[i][j], TRUE);
					gtk_fixed_put(GTK_FIXED(k2_ui_fixed), k2_ui_game_event_box[i][j], 40 + 90 * j, 160 + 90 * i);
					gtk_widget_show_all(k2_ui_game_event_box[i][j]);
				}
			}
		}
		break;
	default:
		fprintf(stderr, "2048-KS Error: k2_game_do_move: invalid direction value %d\n", dir);
		break;
	}
	return !k2_game_comp_val(k2_game_val, old_val);
}
