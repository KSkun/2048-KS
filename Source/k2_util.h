#pragma once

#include <time.h>
#include <stdlib.h>
#include <gtk/gtk.h>

gchar *k2_to_utf8(char *str);

GdkPixbuf *k2_get_pixbuf(const gchar *filename);

int k2_rand_int(int low, int high);