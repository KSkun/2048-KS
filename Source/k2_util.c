#include "k2_util.h"

gchar *k2_to_utf8(char *str) {
	return g_locale_to_utf8(str, -1, NULL, NULL, NULL);
}

GdkPixbuf *k2_get_pixbuf(const gchar *filename) {
	GdkPixbuf *pixbuf;
	GError *err = NULL;
	pixbuf = gdk_pixbuf_new_from_file(filename, &err);
	if (!pixbuf) {
		fprintf(stderr, "Cannot load image file %s, Error: %s\n", filename, err->message);
		g_error_free(err);
	}
	return pixbuf;
}

int k2_rand_int(int low, int high) { // gen rand int in [low, high)
	return rand() % (high - low) + low;
}