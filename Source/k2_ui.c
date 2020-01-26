#include "k2_ui.h"

GtkWidget *k2_ui_window;
GtkWidget *k2_ui_fixed;
GtkWidget *k2_ui_2048_label;
GtkWidget *k2_ui_score_title_label, *k2_ui_score_title_event_box, *k2_ui_score_text_label, *k2_ui_score_text_event_box;
GtkWidget *k2_ui_best_title_label, *k2_ui_best_title_event_box, *k2_ui_best_text_label, *k2_ui_best_text_event_box;
GtkWidget *k2_ui_game_bg_label, *k2_ui_game_bg_event_box, *k2_ui_game_label[4][4], *k2_ui_game_event_box[4][4];
int k2_ui_game_val[4][4];
GtkWidget *k2_ui_author_label;
GtkWidget *k2_ui_menu_bar, *k2_ui_game_menu_item, *k2_ui_game_menu, *k2_ui_game_new_menu_item;

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
	g_signal_connect(k2_ui_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(k2_ui_window, "key-press-event", G_CALLBACK(k2_ui_game_key_press_handler), NULL);

	// fixed container
	k2_ui_fixed = gtk_fixed_new();
	gtk_widget_set_size_request(k2_ui_fixed, 430, 570);
	gtk_container_add(GTK_CONTAINER(k2_ui_window), k2_ui_fixed);

	// menu
	k2_ui_menu_bar = gtk_menu_bar_new();
	gtk_widget_set_size_request(k2_ui_menu_bar, 430, 30);
	gtk_fixed_put(GTK_FIXED(k2_ui_fixed), k2_ui_menu_bar, 0, 0);

	k2_ui_game_menu_item = gtk_menu_item_new_with_label(k2_to_utf8(K2_UI_GAME_MENU_ITEM_TEXT));
	gtk_menu_bar_append(GTK_MENU_BAR(k2_ui_menu_bar), k2_ui_game_menu_item);

	k2_ui_game_menu = gtk_menu_new();
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(k2_ui_game_menu_item), k2_ui_game_menu);

	k2_ui_game_new_menu_item = gtk_menu_item_new_with_label(k2_to_utf8(K2_UI_GAME_NEW_MENU_ITEM_TEXT));
	g_signal_connect(k2_ui_game_new_menu_item, "activate", G_CALLBACK(k2_ui_game_new_menu_item_handler), NULL);
	gtk_menu_append(GTK_MENU(k2_ui_game_menu), k2_ui_game_new_menu_item);

	// 2048 label
	k2_ui_2048_label = gtk_label_new(K2_UI_2048_LABEL_TEXT);
	gtk_widget_modify_font(k2_ui_2048_label, k2_ui_2048_label_font);
	gtk_widget_modify_fg(k2_ui_2048_label, GTK_STATE_NORMAL, &k2_ui_text_color);
	gtk_widget_set_size_request(k2_ui_2048_label, 170, 60);
	gtk_fixed_put(GTK_FIXED(k2_ui_fixed), k2_ui_2048_label, 30, 60);

	// score label
	k2_ui_score_title_label = gtk_label_new(K2_UI_SCORE_LABEL_TITLE);
	k2_ui_score_title_event_box = gtk_event_box_new();
	gtk_widget_modify_font(k2_ui_score_title_label, k2_ui_score_title_font);
	gtk_widget_modify_bg(k2_ui_score_title_event_box, GTK_STATE_NORMAL, &k2_ui_score_bg_color);
	gtk_widget_modify_fg(k2_ui_score_title_label, GTK_STATE_NORMAL, &k2_ui_score_title_color);
	gtk_widget_set_size_request(k2_ui_score_title_label, 80, 25);
	gtk_container_add(GTK_CONTAINER(k2_ui_score_title_event_box), k2_ui_score_title_label);
	gtk_fixed_put(GTK_FIXED(k2_ui_fixed), k2_ui_score_title_event_box, 215, 60);

	k2_ui_score_text_label = gtk_label_new("0");
	k2_ui_score_text_event_box = gtk_event_box_new();
	gtk_widget_modify_font(k2_ui_score_text_label, k2_ui_score_text_font);
	gtk_widget_modify_bg(k2_ui_score_text_event_box, GTK_STATE_NORMAL, &k2_ui_score_bg_color);
	gtk_widget_modify_fg(k2_ui_score_text_label, GTK_STATE_NORMAL, &k2_ui_score_text_color);
	gtk_widget_set_size_request(k2_ui_score_text_label, 80, 35);
	gtk_container_add(GTK_CONTAINER(k2_ui_score_text_event_box), k2_ui_score_text_label);
	gtk_fixed_put(GTK_FIXED(k2_ui_fixed), k2_ui_score_text_event_box, 215, 85);

	// best label
	k2_ui_best_title_label = gtk_label_new(K2_UI_BEST_LABEL_TITLE);
	k2_ui_best_title_event_box = gtk_event_box_new();
	gtk_widget_modify_font(k2_ui_best_title_label, k2_ui_score_title_font);
	gtk_widget_modify_bg(k2_ui_best_title_event_box, GTK_STATE_NORMAL, &k2_ui_score_bg_color);
	gtk_widget_modify_fg(k2_ui_best_title_label, GTK_STATE_NORMAL, &k2_ui_score_title_color);
	gtk_widget_set_size_request(k2_ui_best_title_label, 80, 25);
	gtk_container_add(GTK_CONTAINER(k2_ui_best_title_event_box), k2_ui_best_title_label);
	gtk_fixed_put(GTK_FIXED(k2_ui_fixed), k2_ui_best_title_event_box, 310, 60);

	k2_ui_best_text_label = gtk_label_new("0");
	k2_ui_best_text_event_box = gtk_event_box_new();
	gtk_widget_modify_font(k2_ui_best_text_label, k2_ui_score_text_font);
	gtk_widget_modify_bg(k2_ui_best_text_event_box, GTK_STATE_NORMAL, &k2_ui_score_bg_color);
	gtk_widget_modify_fg(k2_ui_best_text_label, GTK_STATE_NORMAL, &k2_ui_score_text_color);
	gtk_widget_set_size_request(k2_ui_best_text_label, 80, 35);
	gtk_container_add(GTK_CONTAINER(k2_ui_best_text_event_box), k2_ui_best_text_label);
	gtk_fixed_put(GTK_FIXED(k2_ui_fixed), k2_ui_best_text_event_box, 310, 85);

	// game
	k2_ui_game_bg_label = gtk_label_new("");
	k2_ui_game_bg_event_box = gtk_event_box_new();
	gtk_widget_modify_bg(k2_ui_game_bg_event_box, GTK_STATE_NORMAL, &k2_ui_game_bg_color);
	gtk_widget_set_size_request(k2_ui_game_bg_label, 370, 370);
	gtk_container_add(GTK_CONTAINER(k2_ui_game_bg_event_box), k2_ui_game_bg_label);
	gtk_fixed_put(GTK_FIXED(k2_ui_fixed), k2_ui_game_bg_event_box, 30, 150);

	k2_game_new(TRUE);

	// author
	k2_ui_author_label = gtk_label_new(K2_UI_AUTHOR_LABEL_TEXT);
	gtk_widget_modify_fg(k2_ui_author_label, GTK_STATE_NORMAL, &k2_ui_text_color);
	gtk_widget_set_size_request(k2_ui_author_label, 370, 30);
	gtk_fixed_put(GTK_FIXED(k2_ui_fixed), k2_ui_author_label, 30, 530);

	pango_font_description_free(k2_ui_2048_label_font);
	pango_font_description_free(k2_ui_score_title_font);
	pango_font_description_free(k2_ui_score_text_font);
}

void k2_ui_game_init_label(GtkWidget **label, GtkWidget **event_box, char *text, char *bg_color_str, char *fg_color_str, char *font_str, gboolean destroy) {
	if (destroy) {
		gtk_widget_destroy(*label);
		gtk_widget_destroy(*event_box);
	}
	*label = gtk_label_new(text);
	*event_box = gtk_event_box_new();
	gtk_widget_set_size_request(*label, 80, 80);
	GdkColor bg_color, fg_color;
	gdk_color_parse(bg_color_str, &bg_color);
	gdk_color_parse(fg_color_str, &fg_color);
	gtk_widget_modify_bg(*event_box, GTK_STATE_NORMAL, &bg_color);
	gtk_widget_modify_fg(*label, GTK_STATE_NORMAL, &fg_color);
	PangoFontDescription *font = pango_font_description_from_string(font_str);
	gtk_widget_modify_font(*label, font);
	pango_font_description_free(font);
	gtk_container_add(GTK_CONTAINER(*event_box), *label);
}

void k2_ui_game_init_label_with_val(GtkWidget **label, GtkWidget **event_box, int val, gboolean destroy) {
	switch (val) {
	case 0:
		k2_ui_game_init_label(label, event_box, "", K2_UI_GAME_BLANK_COLOR, K2_UI_TEXT_COLOR, K2_UI_GAME_FONT_1, destroy);
		break;
	case 2:
		k2_ui_game_init_label(label, event_box, "2", K2_UI_GAME_2_COLOR, K2_UI_TEXT_COLOR, K2_UI_GAME_FONT_1, destroy);
		break;
	case 4:
		k2_ui_game_init_label(label, event_box, "4", K2_UI_GAME_4_COLOR, K2_UI_TEXT_COLOR, K2_UI_GAME_FONT_1, destroy);
		break;
	case 8:
		k2_ui_game_init_label(label, event_box, "8", K2_UI_GAME_8_COLOR, K2_UI_GAME_TEXT_WHITE_COLOR, K2_UI_GAME_FONT_1, destroy);
		break;
	case 16:
		k2_ui_game_init_label(label, event_box, "16", K2_UI_GAME_16_COLOR, K2_UI_GAME_TEXT_WHITE_COLOR, K2_UI_GAME_FONT_2, destroy);
		break;
	case 32:
		k2_ui_game_init_label(label, event_box, "32", K2_UI_GAME_32_COLOR, K2_UI_GAME_TEXT_WHITE_COLOR, K2_UI_GAME_FONT_2, destroy);
		break;
	case 64:
		k2_ui_game_init_label(label, event_box, "64", K2_UI_GAME_64_COLOR, K2_UI_GAME_TEXT_WHITE_COLOR, K2_UI_GAME_FONT_2, destroy);
		break;
	case 128:
		k2_ui_game_init_label(label, event_box, "128", K2_UI_GAME_128_COLOR, K2_UI_GAME_TEXT_WHITE_COLOR, K2_UI_GAME_FONT_3, destroy);
		break;
	case 256:
		k2_ui_game_init_label(label, event_box, "256", K2_UI_GAME_256_COLOR, K2_UI_GAME_TEXT_WHITE_COLOR, K2_UI_GAME_FONT_3, destroy);
		break;
	case 512:
		k2_ui_game_init_label(label, event_box, "512", K2_UI_GAME_512_COLOR, K2_UI_GAME_TEXT_WHITE_COLOR, K2_UI_GAME_FONT_3, destroy);
		break;
	case 1024:
		k2_ui_game_init_label(label, event_box, "1024", K2_UI_GAME_1024_COLOR, K2_UI_GAME_TEXT_WHITE_COLOR, K2_UI_GAME_FONT_4, destroy);
		break;
	case 2048:
		k2_ui_game_init_label(label, event_box, "2048", K2_UI_GAME_2048_COLOR, K2_UI_GAME_TEXT_WHITE_COLOR, K2_UI_GAME_FONT_4, destroy);
		break;
	case 4096:
		k2_ui_game_init_label(label, event_box, "4096", K2_UI_GAME_4096_COLOR, K2_UI_GAME_TEXT_WHITE_COLOR, K2_UI_GAME_FONT_4, destroy);
		break;
	default:
		fprintf(stderr, "2048-KS Error: k2_ui_game_init_label_with_val: invalid val value %d\n", val);
		break;
	}
}

gboolean k2_ui_game_new_menu_item_handler(GtkWidget *widget, gpointer data) {
	k2_game_new(FALSE);
	return TRUE;
}

gboolean k2_ui_game_key_press_handler(GtkWidget *widget, GdkEventKey *event, gpointer data) {
	switch (event->keyval) {
	case GDK_Up:
		k2_game_do_move(K2_DIR_UP);
		break;
	case GDK_Down:
		k2_game_do_move(K2_DIR_DOWN);
		break;
	case GDK_Left:
		k2_game_do_move(K2_DIR_LEFT);
		break;
	case GDK_Right:
		k2_game_do_move(K2_DIR_RIGHT);
		break;
	default:
		return FALSE;
	}
	if (k2_game_is_lost()) {
		// TODO lost ui
	}
	k2_game_new_block_random();
	return TRUE;
}
