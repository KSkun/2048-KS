#pragma once

#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>

#include "k2_conf.h"
#include "k2_locale.h"
#include "k2_util.h"
#include "k2_game.h"

extern GtkWidget *k2_ui_window;
extern GtkWidget *k2_ui_fixed;
extern GtkWidget *k2_ui_2048_label;
extern GtkWidget *k2_ui_score_title_label, *k2_ui_score_title_event_box, *k2_ui_score_text_label, *k2_ui_score_text_event_box;
extern GtkWidget *k2_ui_best_title_label, *k2_ui_best_title_event_box, *k2_ui_best_text_label, *k2_ui_best_text_event_box;
extern GtkWidget *k2_ui_game_bg_label, *k2_ui_game_bg_event_box, *k2_ui_game_label[4][4], *k2_ui_game_event_box[4][4];
extern GtkWidget *k2_ui_author_label;
extern GtkWidget *k2_ui_menu_bar;
extern GtkWidget *k2_ui_game_menu_item, *k2_ui_game_menu, *k2_ui_game_new_menu_item;
extern GtkWidget *k2_ui_help_menu_item, *k2_ui_help_menu, *k2_ui_help_info_menu_item;

void k2_ui_init();

void k2_ui_game_init_label(GtkWidget **label, GtkWidget **event_box, char *text, char *bg_color_str, char *fg_color_str, char *font_str, gboolean destroy);

void k2_ui_game_init_label_with_val(GtkWidget **label, GtkWidget **event_box, int val, gboolean destroy);

void k2_ui_show_win_dialog();

void k2_ui_show_lose_dialog();

void k2_ui_show_info_dialog();

gboolean k2_ui_help_info_menu_item_handler(GtkWidget *widget, gpointer data);

gboolean k2_ui_game_new_menu_item_handler(GtkWidget *widget, gpointer data);

gboolean k2_ui_game_key_press_handler(GtkWidget *widget, GdkEventKey *event, gpointer data);
