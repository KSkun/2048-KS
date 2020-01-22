#pragma once

#include <gtk/gtk.h>

#include "k2_conf.h"
#include "k2_locale.h"
#include "k2_util.h"

extern GtkWindow *k2_ui_window;
extern GtkWidget *k2_ui_fixed;
extern GtkWidget *k2_ui_2048_lable;
extern GtkWidget *k2_ui_score_title_lable, *k2_ui_score_title_event_box, *k2_ui_score_text_lable, *k2_ui_score_text_event_box;
extern GtkWidget *k2_ui_best_title_lable, *k2_ui_best_title_event_box, *k2_ui_best_text_lable, *k2_ui_best_text_event_box;

void k2_ui_init();