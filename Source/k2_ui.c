#include "k2_ui.h"

GtkWidget *k2_ui_window;
GtkWidget *k2_ui_fixed;
GtkWidget *k2_ui_2048_label;
GtkWidget *k2_ui_score_title_label, *k2_ui_score_title_event_box, *k2_ui_score_text_label, *k2_ui_score_text_event_box;
GtkWidget *k2_ui_best_title_label, *k2_ui_best_title_event_box, *k2_ui_best_text_label, *k2_ui_best_text_event_box;
GtkWidget *k2_ui_game_bg_label, *k2_ui_game_bg_event_box, *k2_ui_game_labels[4][4], *k2_ui_game_event_box[4][4];
GtkWidget *k2_ui_author_label;

void k2_ui_init() {
	GdkColor k2_ui_bg_color;
	gdk_color_parse(K2_UI_BG_COLOR, &k2_ui_bg_color);
	GdkColor k2_ui_text_color;
	gdk_color_parse(K2_UI_TEXT_COLOR, &k2_ui_text_color);
	GdkColor k2_ui_score_bg_color;
	gdk_color_parse(K2_UI_SCORE_BG_COLOR, &k2_ui_score_bg_color);
	GdkColor k2_ui_score_title_color;
	gdk_color_parse(K2_UI_SCORE_TITLE_COLOR, &k2_ui_score_title_color);
	GdkColor k2_ui_score_text_color;
	gdk_color_parse(K2_UI_SCORE_TEXT_COLOR, &k2_ui_score_text_color);
	GdkColor k2_ui_game_bg_color;
	gdk_color_parse(K2_UI_GAME_BG_COLOR, &k2_ui_game_bg_color);

	PangoFontDescription *k2_ui_2048_label_font = pango_font_description_from_string(K2_UI_2048_LABEL_FONT);
	PangoFontDescription *k2_ui_score_title_font = pango_font_description_from_string(K2_UI_SCORE_TITLE_FONT);
	PangoFontDescription *k2_ui_score_text_font = pango_font_description_from_string(K2_UI_SCORE_TEXT_FONT);

	// window
	k2_ui_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(k2_ui_window), k2_to_utf8(K2_UI_TITLE));
	gtk_window_set_resizable(GTK_WINDOW(k2_ui_window), FALSE);
	gtk_widget_modify_bg(k2_ui_window, GTK_STATE_NORMAL, &k2_ui_bg_color);
	gtk_window_set_icon(GTK_WINDOW(k2_ui_window), k2_get_pixbuf(K2_UI_ICON_FILE));
	g_signal_connect(GTK_WINDOW(k2_ui_window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	// fixed container
	k2_ui_fixed = gtk_fixed_new();
	gtk_widget_set_size_request(k2_ui_fixed, 430, 540);
	gtk_container_add(GTK_CONTAINER(k2_ui_window), k2_ui_fixed);

	// 2048 label
	k2_ui_2048_label = gtk_label_new(K2_UI_2048_LABEL_TEXT);
	gtk_widget_modify_font(k2_ui_2048_label, k2_ui_2048_label_font);
	gtk_widget_modify_fg(k2_ui_2048_label, GTK_STATE_NORMAL, &k2_ui_text_color);
	gtk_widget_set_size_request(k2_ui_2048_label, 170, 60);
	gtk_fixed_put(GTK_FIXED(k2_ui_fixed), k2_ui_2048_label, 30, 30);

	// score label
	k2_ui_score_title_label = gtk_label_new(K2_UI_SCORE_LABEL_TITLE);
	k2_ui_score_title_event_box = gtk_event_box_new();
	gtk_widget_modify_font(k2_ui_score_title_label, k2_ui_score_title_font);
	gtk_widget_modify_bg(k2_ui_score_title_event_box, GTK_STATE_NORMAL, &k2_ui_score_bg_color);
	gtk_widget_modify_fg(k2_ui_score_title_label, GTK_STATE_NORMAL, &k2_ui_score_title_color);
	gtk_widget_set_size_request(k2_ui_score_title_label, 80, 25);
	gtk_container_add(GTK_CONTAINER(k2_ui_score_title_event_box), k2_ui_score_title_label);
	gtk_fixed_put(GTK_FIXED(k2_ui_fixed), k2_ui_score_title_event_box, 215, 30);

	k2_ui_score_text_label = gtk_label_new("0");
	k2_ui_score_text_event_box = gtk_event_box_new();
	gtk_widget_modify_font(k2_ui_score_text_label, k2_ui_score_text_font);
	gtk_widget_modify_bg(k2_ui_score_text_event_box, GTK_STATE_NORMAL, &k2_ui_score_bg_color);
	gtk_widget_modify_fg(k2_ui_score_text_label, GTK_STATE_NORMAL, &k2_ui_score_text_color);
	gtk_widget_set_size_request(k2_ui_score_text_label, 80, 35);
	gtk_container_add(GTK_CONTAINER(k2_ui_score_text_event_box), k2_ui_score_text_label);
	gtk_fixed_put(GTK_FIXED(k2_ui_fixed), k2_ui_score_text_event_box, 215, 55);

	// best label
	k2_ui_best_title_label = gtk_label_new(K2_UI_BEST_LABEL_TITLE);
	k2_ui_best_title_event_box = gtk_event_box_new();
	gtk_widget_modify_font(k2_ui_best_title_label, k2_ui_score_title_font);
	gtk_widget_modify_bg(k2_ui_best_title_event_box, GTK_STATE_NORMAL, &k2_ui_score_bg_color);
	gtk_widget_modify_fg(k2_ui_best_title_label, GTK_STATE_NORMAL, &k2_ui_score_title_color);
	gtk_widget_set_size_request(k2_ui_best_title_label, 80, 25);
	gtk_container_add(GTK_CONTAINER(k2_ui_best_title_event_box), k2_ui_best_title_label);
	gtk_fixed_put(GTK_FIXED(k2_ui_fixed), k2_ui_best_title_event_box, 310, 30);

	k2_ui_best_text_label = gtk_label_new("0");
	k2_ui_best_text_event_box = gtk_event_box_new();
	gtk_widget_modify_font(k2_ui_best_text_label, k2_ui_score_text_font);
	gtk_widget_modify_bg(k2_ui_best_text_event_box, GTK_STATE_NORMAL, &k2_ui_score_bg_color);
	gtk_widget_modify_fg(k2_ui_best_text_label, GTK_STATE_NORMAL, &k2_ui_score_text_color);
	gtk_widget_set_size_request(k2_ui_best_text_label, 80, 35);
	gtk_container_add(GTK_CONTAINER(k2_ui_best_text_event_box), k2_ui_best_text_label);
	gtk_fixed_put(GTK_FIXED(k2_ui_fixed), k2_ui_best_text_event_box, 310, 55);

	// game
	k2_ui_game_bg_label = gtk_label_new("");
	k2_ui_game_bg_event_box = gtk_event_box_new();
	gtk_widget_modify_bg(k2_ui_game_bg_event_box, GTK_STATE_NORMAL, &k2_ui_game_bg_color);
	gtk_widget_set_size_request(k2_ui_game_bg_label, 370, 370);
	gtk_container_add(GTK_CONTAINER(k2_ui_game_bg_event_box), k2_ui_game_bg_label);
	gtk_fixed_put(GTK_FIXED(k2_ui_fixed), k2_ui_game_bg_event_box, 30, 120);

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			k2_ui_game_init_label(&k2_ui_game_labels[i][j], &k2_ui_game_event_box[i][j], "", K2_UI_GAME_BLANK_COLOR, FALSE);
			gtk_fixed_put(GTK_FIXED(k2_ui_fixed), k2_ui_game_event_box[i][j], 40 + 90 * i, 130 + 90 * j);
		}
	}

	// author
	k2_ui_author_label = gtk_label_new(K2_UI_AUTHOR_LABEL_TEXT);
	gtk_widget_modify_fg(k2_ui_author_label, GTK_STATE_NORMAL, &k2_ui_text_color);
	gtk_widget_set_size_request(k2_ui_author_label, 370, 30);
	gtk_fixed_put(GTK_FIXED(k2_ui_fixed), k2_ui_author_label, 30, 500);

	pango_font_description_free(k2_ui_2048_label_font);
	pango_font_description_free(k2_ui_score_title_font);
	pango_font_description_free(k2_ui_score_text_font);
}

void k2_ui_game_init_label(GtkWidget **label, GtkWidget **event_box, char *text, char *color_str, gboolean destroy) {
	if (destroy) {
		gtk_widget_destroy(*label);
		gtk_widget_destroy(*event_box);
	}
	*label = gtk_label_new(text);
	*event_box = gtk_event_box_new();
	gtk_widget_set_size_request(*label, 80, 80);
	GdkColor color;
	gdk_color_parse(color_str, &color);
	gtk_widget_modify_bg(*event_box, GTK_STATE_NORMAL, &color);
	gtk_container_add(GTK_CONTAINER(*event_box), *label);
}