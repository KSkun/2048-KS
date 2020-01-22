#include "k2_ui.h"

GtkWindow *k2_ui_window;
GtkWidget *k2_ui_fixed;
GtkWidget *k2_ui_2048_lable;
GtkWidget *k2_ui_score_title_lable, *k2_ui_score_title_event_box, *k2_ui_score_text_lable, *k2_ui_score_text_event_box;
GtkWidget *k2_ui_best_title_lable, *k2_ui_best_title_event_box, *k2_ui_best_text_lable, *k2_ui_best_text_event_box;

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

	PangoFontDescription *k2_ui_2048_lable_font = pango_font_description_from_string(K2_UI_2048_LABLE_FONT);
	PangoFontDescription *k2_ui_score_title_font = pango_font_description_from_string(K2_UI_SCORE_TITLE_FONT);
	PangoFontDescription *k2_ui_score_text_font = pango_font_description_from_string(K2_UI_SCORE_TEXT_FONT);

	// window
	k2_ui_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(k2_ui_window), k2_to_utf8(K2_UI_TITLE));
	gtk_window_set_resizable(GTK_WINDOW(k2_ui_window), FALSE);
	gtk_widget_modify_bg(k2_ui_window, GTK_STATE_NORMAL, &k2_ui_bg_color);
	g_signal_connect(GTK_WINDOW(k2_ui_window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	// fixed container
	k2_ui_fixed = gtk_fixed_new();
	gtk_widget_set_size_request(k2_ui_fixed, 430, 540);
	gtk_container_add(GTK_CONTAINER(k2_ui_window), k2_ui_fixed);

	// 2048 lable
	k2_ui_2048_lable = gtk_label_new(K2_UI_2048_LABLE_TEXT);
	gtk_widget_modify_font(k2_ui_2048_lable, k2_ui_2048_lable_font);
	gtk_widget_modify_fg(k2_ui_2048_lable, GTK_STATE_NORMAL, &k2_ui_text_color);
	gtk_widget_set_size_request(k2_ui_2048_lable, 170, 60);
	gtk_fixed_put(GTK_FIXED(k2_ui_fixed), k2_ui_2048_lable, 30, 30);

	// score lable
	k2_ui_score_title_lable = gtk_label_new(K2_UI_SCORE_LABLE_TITLE);
	k2_ui_score_title_event_box = gtk_event_box_new();
	gtk_widget_modify_font(k2_ui_score_title_lable, k2_ui_score_title_font);
	gtk_widget_modify_bg(k2_ui_score_title_event_box, GTK_STATE_NORMAL, &k2_ui_score_bg_color);
	gtk_widget_modify_fg(k2_ui_score_title_lable, GTK_STATE_NORMAL, &k2_ui_score_title_color);
	gtk_widget_set_size_request(k2_ui_score_title_lable, 80, 25);
	gtk_container_add(GTK_CONTAINER(k2_ui_score_title_event_box), k2_ui_score_title_lable);
	gtk_fixed_put(GTK_FIXED(k2_ui_fixed), k2_ui_score_title_event_box, 215, 30);

	k2_ui_score_text_lable = gtk_label_new("0");
	k2_ui_score_text_event_box = gtk_event_box_new();
	gtk_widget_modify_font(k2_ui_score_text_lable, k2_ui_score_text_font);
	gtk_widget_modify_bg(k2_ui_score_text_event_box, GTK_STATE_NORMAL, &k2_ui_score_bg_color);
	gtk_widget_modify_fg(k2_ui_score_text_lable, GTK_STATE_NORMAL, &k2_ui_score_text_color);
	gtk_widget_set_size_request(k2_ui_score_text_lable, 80, 35);
	gtk_container_add(GTK_CONTAINER(k2_ui_score_text_event_box), k2_ui_score_text_lable);
	gtk_fixed_put(GTK_FIXED(k2_ui_fixed), k2_ui_score_text_event_box, 215, 55);

	// best lable
	k2_ui_best_title_lable = gtk_label_new(K2_UI_BEST_LABLE_TITLE);
	k2_ui_best_title_event_box = gtk_event_box_new();
	gtk_widget_modify_font(k2_ui_best_title_lable, k2_ui_score_title_font);
	gtk_widget_modify_bg(k2_ui_best_title_event_box, GTK_STATE_NORMAL, &k2_ui_score_bg_color);
	gtk_widget_modify_fg(k2_ui_best_title_lable, GTK_STATE_NORMAL, &k2_ui_score_title_color);
	gtk_widget_set_size_request(k2_ui_best_title_lable, 80, 25);
	gtk_container_add(GTK_CONTAINER(k2_ui_best_title_event_box), k2_ui_best_title_lable);
	gtk_fixed_put(GTK_FIXED(k2_ui_fixed), k2_ui_best_title_event_box, 310, 30);

	k2_ui_best_text_lable = gtk_label_new("0");
	k2_ui_best_text_event_box = gtk_event_box_new();
	gtk_widget_modify_font(k2_ui_best_text_lable, k2_ui_score_text_font);
	gtk_widget_modify_bg(k2_ui_best_text_event_box, GTK_STATE_NORMAL, &k2_ui_score_bg_color);
	gtk_widget_modify_fg(k2_ui_best_text_lable, GTK_STATE_NORMAL, &k2_ui_score_text_color);
	gtk_widget_set_size_request(k2_ui_best_text_lable, 80, 35);
	gtk_container_add(GTK_CONTAINER(k2_ui_best_text_event_box), k2_ui_best_text_lable);
	gtk_fixed_put(GTK_FIXED(k2_ui_fixed), k2_ui_best_text_event_box, 310, 55);

	pango_font_description_free(k2_ui_2048_lable_font);
	pango_font_description_free(k2_ui_score_title_font);
	pango_font_description_free(k2_ui_score_text_font);
}