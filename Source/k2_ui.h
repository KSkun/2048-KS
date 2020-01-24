#pragma once

#include <gtk/gtk.h>

#include "k2_conf.h"
#include "k2_locale.h"
#include "k2_util.h"

extern GtkWidget *k2_ui_window;
extern GtkWidget *k2_ui_fixed;
extern GtkWidget *k2_ui_2048_label;
extern GtkWidget *k2_ui_score_title_label, *k2_ui_score_title_event_box, *k2_ui_score_text_label, *k2_ui_score_text_event_box;
extern GtkWidget *k2_ui_best_title_label, *k2_ui_best_title_event_box, *k2_ui_best_text_label, *k2_ui_best_text_event_box;
extern GtkWidget *k2_ui_game_bg_label, *k2_ui_game_bg_event_box, *k2_ui_game_labels[4][4], *k2_ui_game_event_box[4][4];

void k2_ui_init();

void k2_ui_game_init_label(GtkWidget **label, GtkWidget **event_box, char *text, char *color_str, gboolean destroy);